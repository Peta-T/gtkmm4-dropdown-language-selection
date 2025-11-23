#pragma once

#include <string>
#include <sigc++/sigc++.h>
#include <sigc++/signal_base.h>
#include <gtkmm.h>

namespace LanguageSelectorInternal
{
    class ModelColumns : public Glib::Object
    {
    public:
        Glib::ustring m_title;
        Glib::ustring m_icon;
        Glib::ustring m_description;

        static Glib::RefPtr<ModelColumns> create(const Glib::ustring& title,
            const Glib::ustring& icon, const Glib::ustring& description)
        {
            return Glib::make_refptr_for_instance<ModelColumns>(
                new ModelColumns(title, icon, description));
        }

    protected:
        ModelColumns(const Glib::ustring& title, const Glib::ustring& icon,
            const Glib::ustring& description)
            : m_title(title), m_icon(icon), m_description(description)
        {}
    };

    using LangListStore = Gio::ListStore<ModelColumns>;
    using LangListStoreRef = Glib::RefPtr<LangListStore>;
}

class LanguageSelector : public Gtk::Box
{
public:
    using type_signal_language_changed = sigc::signal<void(const std::string&)>;

    LanguageSelector(const std::string& initial_locale = "C.UTF-8");
    ~LanguageSelector() override;

    type_signal_language_changed signal_language_changed() const;

    std::string get_selected_locale() const;
    void set_selected_locale(const std::string& locale);

protected:
    // Factory methods for the ListView
    void on_setup_list_item(const Glib::RefPtr<Gtk::ListItem>& list_item);
    void on_bind_list_item(const Glib::RefPtr<Gtk::ListItem>& list_item);
    void on_unbind_list_item(const Glib::RefPtr<Gtk::ListItem>& list_item);

    // Helper method to update the appearance of the main button
    void update_button_content(const Glib::RefPtr<LanguageSelectorInternal::ModelColumns>& col);

    void create_model();
    void liststore_add_item(const Glib::ustring& title, const Glib::ustring& icon,
        const Glib::ustring& description);

    // Variable to store the actually confirmed locale
    std::string m_ConfirmedLocale;

    // Internal signal notifying rows to redraw checkmarks
    sigc::signal<void()> m_signal_refresh_ui;

    // --- New components replacing Gtk::DropDown ---
    Gtk::Button m_Button;                 // Main button
    Gtk::Popover m_Popover;               // Popup window
    Gtk::ScrolledWindow m_ScrolledWindow; // Scroller inside the popover
    Gtk::ListView m_ListView;             // The actual list view

    // Selection model (SingleSelection wraps ListStore and handles the "selected row")
    Glib::RefPtr<Gtk::SingleSelection> m_SelectionModel;

    LanguageSelectorInternal::LangListStoreRef m_ListStore;
    type_signal_language_changed m_signal_language_changed;

    // Widgets inside the main button (so we can modify them dynamically)
    Gtk::Image m_ButtonImage;
    Gtk::Label m_ButtonLabel;
};
