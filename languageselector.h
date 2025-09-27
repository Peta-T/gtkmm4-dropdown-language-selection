#pragma once

#include <string> // Nejprve plná definice std::string

// Zůstáváme u explicitních include, aby se zaručila plná definice
// sigc::signal předtím, než ji použije gtkmm.
#include <sigc++/sigc++.h>
#include <sigc++/signal_base.h>

#include <gtkmm.h> // Gtkmm až nakonec

// Převezměte třídy ModelColumns a LangListStore, aby zůstaly
// interní záležitostí LanguageSelectoru.
namespace LanguageSelectorInternal
{
    // A Gio::ListStore item.
    class ModelColumns : public Glib::Object
    {
    public:
        Glib::ustring m_title; // Název jazyka/regionu v místním jazyce + anglický název
        Glib::ustring m_icon;  // Cesta k SVG ikoně (např. "/toolbar/cz.svg")
        Glib::ustring m_description; // Kód Locale (např. "cs_CZ.UTF-8")

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
    }; // ModelColumns

    using LangListStore = Gio::ListStore<ModelColumns>;
    using LangListStoreRef = Glib::RefPtr<LangListStore>;
}


/**
 * @brief Uživatelský objekt (widget) pro výběr locale (jazyka/regionu) pomocí Gtk::DropDown.
 *
 * Vysílá signál s vybraným řetězcem locale (např. "cs_CZ.UTF-8") při změně.
 */
class LanguageSelector : public Gtk::Box
{
public:
    /**
     * @brief Definice typu signálu (dle doporučené syntaxe sigc++).
     */
    using type_signal_language_changed = sigc::signal<void(const std::string&)>;

    /**
     * @brief Konstruktor.
     * @param initial_locale Volitelný počáteční kód locale, který má být vybrán.
     */
    LanguageSelector(const std::string& initial_locale = "C.UTF-8");
    ~LanguageSelector() override = default;

    /**
     * @brief Přístup k signálu vyslanému při změně výběru.
     * Signál vrací vybraný řetězec locale.
     */
    type_signal_language_changed signal_language_changed() const;

    /**
     * @brief Získá aktuálně vybraný řetězec locale.
     */
    std::string get_selected_locale() const;

protected:
    // Signal handlers pro Gtk::DropDown továrny
    void on_setup_selected_item(const Glib::RefPtr<Gtk::ListItem>& list_item);
    void on_bind_selected_item(const Glib::RefPtr<Gtk::ListItem>& list_item);
    void on_setup_list_item(const Glib::RefPtr<Gtk::ListItem>& list_item);
    void on_bind_list_item(const Glib::RefPtr<Gtk::ListItem>& list_item);
    void on_unbind_list_item(const Glib::RefPtr<Gtk::ListItem>& list_item);
    void on_selected_item_changed(const Glib::RefPtr<Gtk::ListItem>& list_item);

    // Handler pro změnu výběru v DropDown
    void on_dropdown_changed();

    // Vnitřní metody
    void create_model();
    void liststore_add_item(const Glib::ustring& title, const Glib::ustring& icon,
        const Glib::ustring& description);

    // Komponenty
    Gtk::DropDown m_DropDown;
    LanguageSelectorInternal::LangListStoreRef m_ListStore;

    // Signál
    type_signal_language_changed m_signal_language_changed;
};
