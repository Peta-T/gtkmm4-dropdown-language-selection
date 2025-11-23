#pragma once

#include <gtkmm.h>
#include <yaml-cpp/yaml.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <glibmm/ustring.h>
#include <filesystem>

// Required headers for specific widget types
#include <gtkmm/colorbutton.h>
#include <gtkmm/fontbutton.h>
#include "languageselector.h"

// --- YAML-CPP Specialization ---
// GTKmm uses Glib::ustring (UTF-8) for text, but yaml-cpp uses std::string.
// This specialization teaches yaml-cpp how to automatically convert between them.
namespace YAML {
template<>
struct convert<Glib::ustring> {
    static Node encode(const Glib::ustring& rhs) {
        return Node(rhs.raw());
    }
    static bool decode(const Node& node, Glib::ustring& rhs) {
        if (!node.IsScalar()) return false;
        rhs = node.as<std::string>();
        return true;
    }
};
}

// ==========================================
//      Serialization Interface
// ==========================================

/**
 * @brief Interface ensuring that any widget implementing it can be saved/loaded.
 * * This allows the ConfigManager to treat all widgets (Entry, Switch, ColorButton)
 * uniformly without knowing their specific types (Polymorphism).
 */
class ISerializable {
public:
    /**
     * @param yamlKey The unique key used in the config.yaml file (e.g., "app_width").
     */
    explicit ISerializable(const std::string& yamlKey) : m_yamlKey(yamlKey) {}
    virtual ~ISerializable() = default;

    // Pure virtual methods that must be implemented by specific widgets
    virtual void save(YAML::Node& parentNode) const = 0;
    virtual void load(const YAML::Node& parentNode) = 0;

protected:
    std::string m_yamlKey;
};

// ==========================================
//      Configuration Manager
// ==========================================

/**
 * @brief Manages a collection of widgets and handles file I/O.
 * * It acts as a central registry. When you ask it to save, it iterates over
 * all registered widgets and asks them to write their state to the YAML node.
 */
class ConfigManager {
public:
    /**
     * @brief Registers a widget to be managed.
     * The manager stores a pointer to the interface, not the concrete object.
     */
    void registerWidget(ISerializable* widget) {
        m_widgets.push_back(widget);
    }

    /**
     * @brief Serializes all registered widgets to a file.
     */
    void saveToFile(const std::string& filename) const {
        YAML::Node rootNode;
        // Iterate through all widgets and let them save their own data
        for (const auto& widget : m_widgets) {
            widget->save(rootNode);
        }
        std::ofstream fout(filename);
        fout << rootNode;
    }

    /**
     * @brief Loads configuration from a file.
     * If the file doesn't exist, it logs a message and keeps default values.
     */
    void loadFromFile(const std::string& filename) {
        if (!std::filesystem::exists(filename)) {
            std::cout << "Config file '" << filename << "' not found. Using default values." << std::endl;
            return;
        }
        try {
            YAML::Node rootNode = YAML::LoadFile(filename);
            // Iterate through all widgets and let them find their key in the loaded node
            for (auto& widget : m_widgets) {
                widget->load(rootNode);
            }
        } catch (const YAML::Exception& e) {
            std::cerr << "Error reading config file: " << e.what() << std::endl;
        }
    }

private:
    std::vector<ISerializable*> m_widgets;
};

// ==========================================
//      STANDARD COMPOSITE WIDGETS
// ==========================================
// These classes combine a Gtk::Label and a specific input widget (Entry, Switch, etc.)
// into a single Gtk::Box. This encapsulates layout logic within the class.

/**
 * @brief A text input field with a label.
 */
class GtkEntryYaml : public Gtk::Box, public ISerializable {
    Gtk::Label m_label;
    Gtk::Entry m_entry;
public:
    GtkEntryYaml(const std::string& labelText, const std::string& yamlKey)
        : Gtk::Box(Gtk::Orientation::HORIZONTAL, 10), ISerializable(yamlKey), m_label(labelText)
    {
        // Layout setup: Label on the left, Entry expands to fill space
        m_label.set_hexpand(true);
        m_label.set_xalign(0.0); // Align text to the left
        append(m_label);
        append(m_entry);
    }

    // Proxy methods to allow main.cc to interact with the internal widget
    void set_text(const Glib::ustring& text) { m_entry.set_text(text); }
    Glib::ustring get_text() const { return m_entry.get_text(); }

    // Serialization logic
    void save(YAML::Node& parentNode) const override { parentNode[m_yamlKey] = m_entry.get_text(); }
    void load(const YAML::Node& parentNode) override {
        if (parentNode[m_yamlKey]) m_entry.set_text(parentNode[m_yamlKey].as<std::string>());
    }
};

/**
 * @brief A checkbox.
 * Note: Gtk::CheckButton already has a built-in label, so we inherit directly
 * from it instead of wrapping it in a Box.
 */
class GtkCheckButtonYaml : public Gtk::CheckButton, public ISerializable {
public:
    GtkCheckButtonYaml(const std::string& label, const std::string& yamlKey)
        : Gtk::CheckButton(label), ISerializable(yamlKey) {}

    void save(YAML::Node& parentNode) const override { parentNode[m_yamlKey] = this->get_active(); }
    void load(const YAML::Node& parentNode) override {
        if (parentNode[m_yamlKey]) this->set_active(parentNode[m_yamlKey].as<bool>());
    }
};

/**
 * @brief An ON/OFF switch with a label.
 */
class GtkSwitchYaml : public Gtk::Box, public ISerializable {
    Gtk::Label m_label;
    Gtk::Switch m_switch;
public:
    GtkSwitchYaml(const std::string& labelText, const std::string& yamlKey)
        : Gtk::Box(Gtk::Orientation::HORIZONTAL, 10), ISerializable(yamlKey), m_label(labelText)
    {
        m_label.set_hexpand(true);
        m_label.set_xalign(0.0);
        m_switch.set_valign(Gtk::Align::CENTER); // Vertically center the switch
        append(m_label);
        append(m_switch);
    }

    bool get_active() const { return m_switch.get_active(); }

    void save(YAML::Node& parentNode) const override { parentNode[m_yamlKey] = m_switch.get_active(); }
    void load(const YAML::Node& parentNode) override {
        if (parentNode[m_yamlKey]) m_switch.set_active(parentNode[m_yamlKey].as<bool>());
    }
};

/**
 * @brief A numeric spinner with a label.
 * Requires an 'Adjustment' object to define min/max/step values.
 */
class GtkSpinButtonYaml : public Gtk::Box, public ISerializable {
    Gtk::Label m_label;
    Gtk::SpinButton m_spin;
public:
    GtkSpinButtonYaml(const std::string& labelText, const Glib::RefPtr<Gtk::Adjustment>& adj, const std::string& yamlKey)
        : Gtk::Box(Gtk::Orientation::HORIZONTAL, 10), ISerializable(yamlKey), m_label(labelText), m_spin(adj)
    {
        m_spin.set_digits(2); // Default to 2 decimal places
        m_label.set_hexpand(true);
        m_label.set_xalign(0.0);
        append(m_label);
        append(m_spin);
    }

    double get_value() const { return m_spin.get_value(); }

    void save(YAML::Node& parentNode) const override { parentNode[m_yamlKey] = m_spin.get_value(); }
    void load(const YAML::Node& parentNode) override {
        if (parentNode[m_yamlKey]) m_spin.set_value(parentNode[m_yamlKey].as<double>());
    }
};

/**
 * @brief A dropdown list (ComboBox) with a label.
 */
class GtkComboBoxTextYaml : public Gtk::Box, public ISerializable {
    Gtk::Label m_label;
    Gtk::ComboBoxText m_combo;
public:
    GtkComboBoxTextYaml(const std::string& labelText, const std::string& yamlKey)
        : Gtk::Box(Gtk::Orientation::HORIZONTAL, 10), ISerializable(yamlKey), m_label(labelText)
    {
        m_label.set_hexpand(true);
        m_label.set_xalign(0.0);
        append(m_label);
        append(m_combo);
    }

    // Proxy methods to populate the combo box
    void append_text(const Glib::ustring& text) { m_combo.append(text); }
    void set_active_text(const Glib::ustring& text) { m_combo.set_active_text(text); }
    Glib::ustring get_active_text() const { return m_combo.get_active_text(); }

    void save(YAML::Node& parentNode) const override { parentNode[m_yamlKey] = m_combo.get_active_text(); }
    void load(const YAML::Node& parentNode) override {
        if (parentNode[m_yamlKey]) m_combo.set_active_text(parentNode[m_yamlKey].as<std::string>());
    }
};

// ==========================================
//      ADVANCED WIDGETS
// ==========================================

/**
 * @brief A color picker button with a label.
 * Saves the color as a string (e.g., "rgba(255,0,0,1)").
 */
class GtkColorYaml : public Gtk::Box, public ISerializable {
    Gtk::Label m_label;
    Gtk::ColorButton m_colorButton;
public:
    GtkColorYaml(const std::string& labelText, const std::string& yamlKey)
        : Gtk::Box(Gtk::Orientation::HORIZONTAL, 10), ISerializable(yamlKey), m_label(labelText)
    {
        m_label.set_hexpand(true);
        m_label.set_xalign(0.0);
        append(m_label);
        append(m_colorButton);
    }

    void save(YAML::Node& parentNode) const override {
        // Convert internal Gdk::RGBA to string representation
        parentNode[m_yamlKey] = m_colorButton.get_rgba().to_string();
    }
    void load(const YAML::Node& parentNode) override {
        if (parentNode[m_yamlKey]) {
            Gdk::RGBA color;
            try {
                // Parse the string back to a color object
                // Note: In GTK4mm, we use color.set(), not color.parse()
                color.set(parentNode[m_yamlKey].as<std::string>());
                m_colorButton.set_rgba(color);
            } catch (...) {
                std::cerr << "Warning: Failed to parse color for key " << m_yamlKey << "\n";
            }
        }
    }
};

/**
 * @brief A font picker button with a label.
 * Saves the font description as a string (e.g., "Sans 12").
 */
class GtkFontYaml : public Gtk::Box, public ISerializable {
    Gtk::Label m_label;
    Gtk::FontButton m_fontButton;
public:
    GtkFontYaml(const std::string& labelText, const std::string& yamlKey)
        : Gtk::Box(Gtk::Orientation::HORIZONTAL, 10), ISerializable(yamlKey), m_label(labelText)
    {
        m_label.set_hexpand(true);
        m_label.set_xalign(0.0);

        // Configure font button to show font name and size
        m_fontButton.set_use_font(true);
        m_fontButton.set_use_size(true);

        append(m_label);
        append(m_fontButton);
    }

    void save(YAML::Node& parentNode) const override {
        parentNode[m_yamlKey] = m_fontButton.get_font();
    }
    void load(const YAML::Node& parentNode) override {
        if (parentNode[m_yamlKey]) {
            m_fontButton.set_font(parentNode[m_yamlKey].as<std::string>());
        }
    }
};

/**
 * @brief Wrapper for the custom LanguageSelector widget.
 * Allows saving the selected locale (e.g., "cs_CZ.UTF-8") to YAML.
 */
class GtkLanguageYaml : public Gtk::Box, public ISerializable {
    Gtk::Label m_label;
    LanguageSelector m_selector; // The custom complex widget
public:
    GtkLanguageYaml(const std::string& labelText, const std::string& defaultLocale, const std::string& yamlKey)
        : Gtk::Box(Gtk::Orientation::HORIZONTAL, 10),
          ISerializable(yamlKey),
          m_label(labelText),
          m_selector(defaultLocale)
    {
        m_label.set_hexpand(true);
        m_label.set_xalign(0.0);
        append(m_label);
        append(m_selector);
    }

    void save(YAML::Node& parentNode) const override {
        // Get the locale string from the selector
        parentNode[m_yamlKey] = m_selector.get_selected_locale();
    }
    void load(const YAML::Node& parentNode) override {
        if (parentNode[m_yamlKey]) {
            // Set the dropdown to match the string loaded from file
            m_selector.set_selected_locale(parentNode[m_yamlKey].as<std::string>());
        }
    }
};
