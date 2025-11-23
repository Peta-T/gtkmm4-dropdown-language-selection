// build app: g++ -std=c++17 main.cc languageselector.cc ./images/resources.c -o app $(pkg-config --cflags --libs gtkmm-4.0 yaml-cpp)
// if you will need chage resource images:
// download flag images from: https://github.com/lipis/flag-icons/tree/main/flags/4x3
// and https://upload.wikimedia.org/wikipedia/commons/f/ff/Flag_of_Serbia.svg  to ./images folder
// build resource: glib-compile-resources --generate-source ./resources.xml

#include <gtkmm.h>
#include <iostream>
#include <memory> // For std::shared_ptr

// Include our custom configuration system
#include "yamlconfig.h"

// External function to get the GResource for the application (for the SVG icon).
extern GResource *resources_get_resource(void);

// =========================================================================
// Main Application Window
// =========================================================================
class MyWindow : public Gtk::Window
{
public:
    MyWindow();
    ~MyWindow() override;

protected:
    // --- Signal Handlers ---
    // The handler for opening the settings dialog
    void on_button_settings_clicked();

    // --- Widgets ---
    Gtk::Box m_VBox;           // Main vertical layout
    Gtk::Box m_ToolbarBox;     // Horizontal toolbar container

    // Toolbar Buttons
    Gtk::Button m_ButtonSettings; // Settings button (The only button left)

    Gtk::Label m_Label;        // Status label
};

// =========================================================================
// Implementation
// =========================================================================

MyWindow::MyWindow()
    : m_VBox(Gtk::Orientation::VERTICAL),
      m_ToolbarBox(Gtk::Orientation::HORIZONTAL),
      m_Label("Click the settings button.")
{
    // 1. Window Setup
    set_title("Application with Settings");
    set_default_size(600, 400);
    set_child(m_VBox);

    // 2. Toolbar Setup
    // We add a CSS class to the box to give it a 'toolbar' style
    m_ToolbarBox.add_css_class("toolbar");

    // --- Settings Button ---
    // Uses the standard system icon for preferences/settings
    m_ButtonSettings.set_icon_name("emblem-system");
    m_ButtonSettings.set_tooltip_text("Configuration / Settings");
    m_ButtonSettings.set_has_frame(false);

    // Connect the settings button
    m_ButtonSettings.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_button_settings_clicked));

    // Add button to toolbar
    m_ToolbarBox.append(m_ButtonSettings);

    // 3. Final Layout
    m_VBox.append(m_ToolbarBox);

    // Add a separator below the toolbar
    m_VBox.append(*Gtk::make_managed<Gtk::Separator>(Gtk::Orientation::HORIZONTAL));

    m_VBox.append(m_Label);

    m_Label.set_vexpand(true);
    m_Label.set_halign(Gtk::Align::CENTER);
    m_Label.set_valign(Gtk::Align::CENTER);
}

MyWindow::~MyWindow() {}


// =========================================================================
// SETTINGS DIALOG LOGIC
// =========================================================================
void MyWindow::on_button_settings_clicked()
{
    // 1. Create a Transient Window (Dialog)
    auto settingsWindow = new Gtk::Window();
    settingsWindow->set_title("Settings");
    settingsWindow->set_transient_for(*this); // Keeps it on top of the main window
    settingsWindow->set_modal(true);          // Blocks interaction with main window
    settingsWindow->set_default_size(600, 675);
    settingsWindow->set_hide_on_close(false); // Destroy when closed

    // 2. Setup ConfigManager
    // We use shared_ptr so the manager lives as long as the dialog exists.
    auto configManager = std::make_shared<ConfigManager>();

    // 3. Layout Containers
    auto scrolled = Gtk::make_managed<Gtk::ScrolledWindow>();
    settingsWindow->set_child(*scrolled);

    auto box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 15);
    box->set_margin(30);
    scrolled->set_child(*box);

    // 4. Create Configuration Widgets
    // Note: We use Gtk::make_managed. The 'box' will own them visually.

    // -- Basic Settings --
    auto nameEntry = Gtk::make_managed<GtkEntryYaml>("Username:", "user_name");

    auto roleCombo = Gtk::make_managed<GtkComboBoxTextYaml>("User Role:", "user_role");
    roleCombo->append_text("Admin");
    roleCombo->append_text("User");
    roleCombo->append_text("Guest");

    auto activeCheck = Gtk::make_managed<GtkCheckButtonYaml>("Enable Auto-Updates", "auto_update");

    // -- Behavior --
    auto autoSaveSwitch = Gtk::make_managed<GtkSwitchYaml>("Auto-Save Enabled:", "auto_save");

    auto adj = Gtk::Adjustment::create(10.0, 1.0, 120.0, 1.0, 5.0);
    auto timeoutSpin = Gtk::make_managed<GtkSpinButtonYaml>("Session Timeout (min):", adj, "session_timeout");

    // -- Visuals & Language --
    auto themeColor = Gtk::make_managed<GtkColorYaml>("Theme Color:", "theme_color");
    auto appFont = Gtk::make_managed<GtkFontYaml>("Interface Font:", "app_font");
    auto langSelector = Gtk::make_managed<GtkLanguageYaml>("Language:", "cs_CZ.UTF-8", "locale");

    // 5. Register with Manager
    configManager->registerWidget(nameEntry);
    configManager->registerWidget(roleCombo);
    configManager->registerWidget(activeCheck);
    configManager->registerWidget(autoSaveSwitch);
    configManager->registerWidget(timeoutSpin);
    configManager->registerWidget(themeColor);
    configManager->registerWidget(appFont);
    configManager->registerWidget(langSelector);

    // 6. Load Current Values
    configManager->loadFromFile("config.yaml");

    // 7. Add to Layout
    // Using 'true' for mnemonics is correct here if you don't use HTML tags
    box->append(*Gtk::make_managed<Gtk::Label>("User Profile", true));
    box->append(*nameEntry);
    box->append(*roleCombo);
    box->append(*activeCheck);

    box->append(*Gtk::make_managed<Gtk::Separator>(Gtk::Orientation::HORIZONTAL));

    box->append(*Gtk::make_managed<Gtk::Label>("System", true));
    box->append(*autoSaveSwitch);
    box->append(*timeoutSpin);

    box->append(*Gtk::make_managed<Gtk::Separator>(Gtk::Orientation::HORIZONTAL));

    box->append(*Gtk::make_managed<Gtk::Label>("Appearance", true));
    box->append(*themeColor);
    box->append(*appFont);
    box->append(*langSelector);

    box->append(*Gtk::make_managed<Gtk::Separator>(Gtk::Orientation::HORIZONTAL));

    // 8. Save Button
    auto saveBtn = Gtk::make_managed<Gtk::Button>("Save Configuration");
    saveBtn->add_css_class("suggested-action");

    // Connect Save Signal
    saveBtn->signal_clicked().connect([configManager, settingsWindow, this]() {
        configManager->saveToFile("config.yaml");
        std::cout << "Configuration saved from dialog." << std::endl;
        m_Label.set_text("Configuration updated and saved.");
        settingsWindow->close();
    });

    // Push button to the bottom
    auto spacer = Gtk::make_managed<Gtk::Box>();
    spacer->set_vexpand(true);
    box->append(*spacer);
    box->append(*saveBtn);

    // 9. Show the Dialog
    settingsWindow->present();

    // Ensure the window is deleted when closed to free memory
    settingsWindow->signal_close_request().connect([settingsWindow]() {
        delete settingsWindow;
        return true;
    }, false);
}

// =========================================================================
// Main Entry Point
// =========================================================================
int main(int argc, char* argv[])
{
    // Register the resources (compiled via glib-compile-resources)
    g_resources_register(resources_get_resource());

    auto app = Gtk::Application::create("org.gtkmm.example.ToolbarAndConfig", Gio::Application::Flags::NONE);
    return app->make_window_and_run<MyWindow>(argc, argv);
}
