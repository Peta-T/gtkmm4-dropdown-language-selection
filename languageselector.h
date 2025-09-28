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
    ~LanguageSelector() override = default;

    type_signal_language_changed signal_language_changed() const;

    std::string get_selected_locale() const;

protected:
    void on_setup_selected_item(const Glib::RefPtr<Gtk::ListItem>& list_item);
    void on_bind_selected_item(const Glib::RefPtr<Gtk::ListItem>& list_item);
    void on_setup_list_item(const Glib::RefPtr<Gtk::ListItem>& list_item);
    void on_bind_list_item(const Glib::RefPtr<Gtk::ListItem>& list_item);
    void on_unbind_list_item(const Glib::RefPtr<Gtk::ListItem>& list_item);
    void on_selected_item_changed(const Glib::RefPtr<Gtk::ListItem>& list_item);

    void on_dropdown_changed();

    void create_model();
    void liststore_add_item(const Glib::ustring& title, const Glib::ustring& icon,
        const Glib::ustring& description);

    Gtk::DropDown m_DropDown;
    LanguageSelectorInternal::LangListStoreRef m_ListStore;

    type_signal_language_changed m_signal_language_changed;
};
