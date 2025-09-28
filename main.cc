// build app: g++ -std=c++17 main.cc languageselector.cc ./images/resources.c -o app $(pkg-config --cflags --libs gtkmm-4.0)
// if you need chage resource images:
// download flag images from: https://github.com/lipis/flag-icons/tree/main/flags/4x3
// and https://upload.wikimedia.org/wikipedia/commons/f/ff/Flag_of_Serbia.svg  to ./images folder
// build resource: glib-compile-resources --generate-source ./resources.xml


#include <gtkmm.h>
#include <iostream>
#include "languageselector.h"

class MyWindow : public Gtk::Window
{
public:
    MyWindow()
    {
        set_title("Language Selector Example");
        set_default_size(400, 200);

        m_lang_selector = Gtk::make_managed<LanguageSelector>("cs_CZ.UTF-8");

        m_lang_selector->signal_language_changed().connect(
            sigc::mem_fun(*this, &MyWindow::on_language_changed));

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
        std::cout << "MAIN PROGRAM: New locale received: " << new_locale << std::endl;
        m_label->set_text("Current Locale: " + new_locale);
    }

private:
    LanguageSelector* m_lang_selector = nullptr;
    Gtk::Label* m_label = nullptr;
    Gtk::Box* m_Box = nullptr;
};

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create("org.gtkmm.languageselector");

    return app->make_window_and_run<MyWindow>(argc, argv);
}
