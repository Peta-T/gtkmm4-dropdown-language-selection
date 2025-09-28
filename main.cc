//build: g++ -std=c++17 main.cc languageselector.cc resources.c -o app $(pkg-config --cflags --libs gtkmm-4.0)
// build resource: glib-compile-resources --generate-source ./resource.xml
#include <gtkmm.h>
#include <iostream>
#include "languageselector.h"

// Třída hlavního okna s použitím LanguageSelectoru
class MyWindow : public Gtk::Window
{
public:
    MyWindow()
    {
        set_title("Language Selector Example");
        set_default_size(400, 200);

        // 1. Vytvoření instance LanguageSelectoru.
        m_lang_selector = Gtk::make_managed<LanguageSelector>("cs_CZ.UTF-8");

        // 2. Připojení na signál, který vrátí vybraný locale řetězec.
        m_lang_selector->signal_language_changed().connect(
            sigc::mem_fun(*this, &MyWindow::on_language_changed));

        // Nastavení GUI
        m_label = Gtk::make_managed<Gtk::Label>("Current Locale: " + m_lang_selector->get_selected_locale());
        m_label->set_margin_top(15);
        m_label->set_margin_bottom(15);
        m_label->set_margin_start(15);
        m_label->set_margin_end(15);

        m_Box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 10);
        m_Box->set_margin(10);

        m_Box->append(*m_lang_selector);
        m_Box->append(*m_label);

        set_child(*m_Box);
    }

protected:
    void on_language_changed(const std::string& new_locale)
    {
        // Obsluha signálu z LanguageSelectoru
        std::cout << "MAIN PROGRAM: New locale received: " << new_locale << std::endl;
        m_label->set_text("Current Locale: " + new_locale);

        // Zde můžete provést logiku programu pro změnu jazyka
        // Např. setlocale(LC_ALL, new_locale.c_str());
    }

private:
    LanguageSelector* m_lang_selector = nullptr;
    Gtk::Label* m_label = nullptr;
    Gtk::Box* m_Box = nullptr;
};

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create("org.gtkmm.languageselector");

    // Potřebné pro načítání SVG obrázků z GTK resources
    // Pokud použijete resources.c, je potřeba zaregistrovat resource bundle
    // g_resources_register(GET_RESOURCE(resources));

    return app->make_window_and_run<MyWindow>(argc, argv);
}
