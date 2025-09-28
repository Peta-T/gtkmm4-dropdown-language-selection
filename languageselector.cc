// there are used svg images of flags with names by ISO 3166-1-alpha-2 code from this source:
// https://github.com/lipis/flag-icons/tree/main/flags/4x3 included into resources.c file
// many thanks to autor

#include "languageselector.h"
#include <iostream>

using namespace LanguageSelectorInternal;

LanguageSelector::LanguageSelector(const std::string& initial_locale)
    : Gtk::Box(Gtk::Orientation::HORIZONTAL)
{
    auto factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(
        sigc::mem_fun(*this, &LanguageSelector::on_setup_selected_item));
    factory->signal_bind().connect(
        sigc::mem_fun(*this, &LanguageSelector::on_bind_selected_item));
    m_DropDown.set_factory(factory);

    factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(
        sigc::mem_fun(*this, &LanguageSelector::on_setup_list_item));
    factory->signal_bind().connect(
        sigc::mem_fun(*this, &LanguageSelector::on_bind_list_item));
    factory->signal_unbind().connect(
        sigc::mem_fun(*this, &LanguageSelector::on_unbind_list_item));
    m_DropDown.set_list_factory(factory);

    create_model();
    m_DropDown.set_model(m_ListStore);

    int initial_index = 0;
    for (size_t i = 0; i < m_ListStore->get_n_items(); ++i)
    {
        if (m_ListStore->get_item(i)->m_description == initial_locale)
        {
            initial_index = i;
            break;
        }
    }
    m_DropDown.set_selected(initial_index);

    m_DropDown.property_selected().signal_changed().connect(
        sigc::mem_fun(*this, &LanguageSelector::on_dropdown_changed));

    append(m_DropDown);
}

std::string LanguageSelector::get_selected_locale() const
{
    const auto selected = m_DropDown.get_selected();
    if (selected >= m_ListStore->get_n_items())
        return "";

    return m_ListStore->get_item(selected)->m_description.raw();
}

LanguageSelector::type_signal_language_changed LanguageSelector::signal_language_changed() const
{
    return m_signal_language_changed;
}

void LanguageSelector::on_dropdown_changed()
{
    const auto selected_locale = get_selected_locale();
    std::cout << "LanguageSelector: New locale selected: " << selected_locale << std::endl;

    m_signal_language_changed.emit(selected_locale);
}

void LanguageSelector::liststore_add_item(const Glib::ustring& title,
    const Glib::ustring& icon, const Glib::ustring& description)
{
    m_ListStore->append(ModelColumns::create(title, icon, description));
}

void LanguageSelector::on_setup_selected_item(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
    auto box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 10);
    box->append(*Gtk::make_managed<Gtk::Image>());
    box->set_baseline_position(Gtk::BaselinePosition::CENTER);
    box->append(*Gtk::make_managed<Gtk::Label>());
    list_item->set_child(*box);
}

void LanguageSelector::on_bind_selected_item(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
    auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
    if (!col) return;
    auto box = dynamic_cast<Gtk::Box*>(list_item->get_child());
    if (!box) return;
    auto image = dynamic_cast<Gtk::Image*>(box->get_first_child());
    if (!image) return;
    image->set_from_resource(col->m_icon);
    image->set_pixel_size(150);

    auto label = dynamic_cast<Gtk::Label*>(image->get_next_sibling());
    if (!label) return;
    label->set_text(col->m_title);
}

void LanguageSelector::on_setup_list_item(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
    auto hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 10);
    auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 2);

    hbox->append(*Gtk::make_managed<Gtk::Image>());
    hbox->append(*vbox);
    auto title = Gtk::make_managed<Gtk::Label>();
    title->set_xalign(0.0);
    vbox->set_baseline_position(Gtk::BaselinePosition::CENTER);
    vbox->append(*title);
    auto description = Gtk::make_managed<Gtk::Label>();
    description->set_xalign(0.0);
    description->add_css_class("dim-label");
    vbox->append(*description);
    auto checkmark = Gtk::make_managed<Gtk::Image>();
    checkmark->set_from_icon_name("object-select-symbolic");

    checkmark->set_visible(false);
    hbox->append(*checkmark);

    list_item->set_child(*hbox);
}

void LanguageSelector::on_bind_list_item(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
    auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
    if (!col) return;
    auto hbox = dynamic_cast<Gtk::Box*>(list_item->get_child());
    if (!hbox) return;
    auto image = dynamic_cast<Gtk::Image*>(hbox->get_first_child());
    if (!image) return;
    image->set_pixel_size(120);
    image->set_from_resource(col->m_icon);

    auto vbox = dynamic_cast<Gtk::Box*>(image->get_next_sibling());
    if (!vbox) return;
    auto title = dynamic_cast<Gtk::Label*>(vbox->get_first_child());
    if (!title) return;
    title->set_text(col->m_title);
    auto description = dynamic_cast<Gtk::Label*>(title->get_next_sibling());
    if (!description) return;
    description->set_text(col->m_description);

    auto connection = m_DropDown.property_selected_item().signal_changed().connect(
        sigc::bind(sigc::mem_fun(*this, &LanguageSelector::on_selected_item_changed),
            list_item));
    list_item->set_data("connection", new sigc::connection(connection),
        Glib::destroy_notify_delete<sigc::connection>);
    on_selected_item_changed(list_item);
}

void LanguageSelector::on_unbind_list_item(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
    if (auto connection = static_cast<sigc::connection*>(list_item->get_data("connection")))
    {
        connection->disconnect();
        list_item->set_data("connection", nullptr);
    }
}

void LanguageSelector::on_selected_item_changed(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
    auto hbox = dynamic_cast<Gtk::Box*>(list_item->get_child());
    if (!hbox) return;
    auto checkmark = dynamic_cast<Gtk::Image*>(hbox->get_last_child());
    if (!checkmark) return;
    checkmark->set_visible(m_DropDown.get_selected_item() == list_item->get_item());
}

void LanguageSelector::create_model()
{
    m_ListStore = LangListStore::create();
    liststore_add_item("\x43 / C locale", "/images/zz.svg", "C.UTF-8");
    liststore_add_item("\x51\x61\x66\x61\x72 / Afar, Djibouti", "/images/dj.svg", "aa_DJ.UTF-8");
    liststore_add_item("\x41\x66\x72\x69\x6b\x61\x61\x6e\x73 / Afrikaans, South Africa", "/images/za.svg", "af_ZA.UTF-8");
    liststore_add_item("\x41\x72\x61\x67\x6f\x6e\xe9\x73 / Aragonese, Spain", "/images/es.svg", "an_ES.UTF-8");
    liststore_add_item("\x61\x6c\x61\x72\x61\x62\x69\x79\x61 / Arabic, United Arab Emirates", "/images/ae.svg", "ar_AE.UTF-8");
    liststore_add_item("\x61\x6c\x61\x72\x61\x62\x69\x79\x61 / Arabic, Bahrain", "/images/bh.svg", "ar_BH.UTF-8");
    liststore_add_item("\x61\x6c\x61\x72\x61\x62\x69\x79\x61 / Arabic, Algeria", "/images/dz.svg", "ar_DZ.UTF-8");
    liststore_add_item("\x61\x6c\x61\x72\x61\x62\x69\x79\x61 / Arabic, Egypt", "/images/eg.svg", "ar_EG.UTF-8");
    liststore_add_item("\x61\x6c\x61\x72\x61\x62\x69\x79\x61 / Arabic, Iraq", "/images/iq.svg", "ar_IQ.UTF-8");
    liststore_add_item("\x61\x6c\x61\x72\x61\x62\x69\x79\x61 / Arabic, Jordan", "/images/jo.svg", "ar_JO.UTF-8");
    liststore_add_item("\x61\x6c\x61\x72\x61\x62\x69\x79\x61 / Arabic, Kuwait", "/images/kw.svg", "ar_KW.UTF-8");
    liststore_add_item("\x61\x6c\x61\x72\x61\x62\x69\x79\x61 / Arabic, Lebanon", "/images/lb.svg", "ar_LB.UTF-8");
    liststore_add_item("\x61\x6c\x61\x72\x61\x62\x69\x79\x61 / Arabic, Libya", "/images/ly.svg", "ar_LY.UTF-8");
    liststore_add_item("\x61\x6c\x61\x72\x61\x62\x69\x79\x61 / Arabic, Morocco", "/images/ma.svg", "ar_MA.UTF-8");
    liststore_add_item("\x61\x6c\x61\x72\x61\x62\x69\x79\x61 / Arabic, Oman", "/images/om.svg", "ar_OM.UTF-8");
    liststore_add_item("\x61\x6c\x61\x72\x61\x62\x69\x79\x61 / Arabic, Qatar", "/images/qa.svg", "ar_QA.UTF-8");
    liststore_add_item("\x61\x6c\x61\x72\x61\x62\x69\x79\x61 / Arabic, Saudi Arabia", "/images/sa.svg", "ar_SA.UTF-8");
    liststore_add_item("\x61\x6c\x61\x72\x61\x62\x69\x79\x61 / Arabic, Sudan", "/images/sd.svg", "ar_SD.UTF-8");
    liststore_add_item("\x61\x6c\x61\x72\x61\x62\x69\x79\x61 / Arabic, Syria", "/images/sy.svg", "ar_SY.UTF-8");
    liststore_add_item("\x61\x6c\x61\x72\x61\x62\x69\x79\x61 / Arabic, Tunisia", "/images/tn.svg", "ar_TN.UTF-8");
    liststore_add_item("\x61\x6c\x61\x72\x61\x62\x69\x79\x61 / Arabic, Yemen", "/images/ye.svg", "ar_YE.UTF-8");
    liststore_add_item("\x41\x73\x74\x75\x72\x69\x61\x6e\x75 / Asturian, Spain", "/images/es.svg", "ast_ES.UTF-8");
    liststore_add_item("\x41\x71\x62\x65\x6c\x60\x61\x72\x75\x73\x6b\x61\x72\x61\x73 / Belarusian, Belarus", "/images/by.svg", "be_BY.UTF-8");
    liststore_add_item("\x41\x72\x61\x62\x73\x6b\x69 / Bulgarian, Bulgaria", "/images/bg.svg", "bg_BG.UTF-8");
    liststore_add_item("\x62\x68\x62\x5f\x49\x4e / Bhili, India", "/images/in.svg", "bhb_IN.UTF-8");
    liststore_add_item("\x42\x72\x65\x7a\x68\x6f\x6e\x65\x67 / Breton, France", "/images/fr.svg", "br_FR.UTF-8");
    liststore_add_item("\x42\x6f\x73\x61\x6e\x73\x6b\x69 / Bosnian, Bosnia and Herzegovina", "/images/ba.svg", "bs_BA.UTF-8");
    liststore_add_item("\x43\x61\x74\x61\x6c\xe0 / Catalan, Andorra", "/images/ad.svg", "ca_AD.UTF-8");
    liststore_add_item("\x43\x61\x74\x61\x6c\xe0 / Catalan, Spain", "/images/es.svg", "ca_ES.UTF-8");
    liststore_add_item("\x43\x61\x74\x61\x6c\xe0 / Catalan, France", "/images/fr.svg", "ca_FR.UTF-8");
    liststore_add_item("\x43\x61\x74\x61\x6c\xe0 / Catalan, Italy", "/images/it.svg", "ca_IT.UTF-8");
    liststore_add_item("\x43\x65\xc5\xa1\x74\x69\x6e\x61 / Czech, Czech Republic", "/images/cz.svg", "cs_CZ.UTF-8");
    liststore_add_item("\x43\x79\x6d\x72\x61\x65\x67 / Welsh, United Kingdom", "/images/gb.svg", "cy_GB.UTF-8");
    liststore_add_item("\x44\x61\x6e\x73\x6b / Danish, Denmark", "/images/dk.svg", "da_DK.UTF-8");
    liststore_add_item("\x44\x65\x75\x74\x73\x63\x68 / German, Austria", "/images/at.svg", "de_AT.UTF-8");
    liststore_add_item("\x44\x65\x75\x74\x73\x63\x68 / German, Belgium", "/images/be.svg", "de_BE.UTF-8");
    liststore_add_item("\x44\x65\x75\x74\x73\x63\x68 / German, Switzerland", "/images/ch.svg", "de_CH.UTF-8");
    liststore_add_item("\x44\x65\x75\x74\x73\x63\x68 / German, Germany", "/images/de.svg", "de_DE.UTF-8");
    liststore_add_item("\x44\x65\x75\x74\x73\x63\x68 / German, Italy", "/images/it.svg", "de_IT.UTF-8");
    liststore_add_item("\x44\x65\x75\x74\x73\x63\x68 / German, Liechtenstein", "/images/li.svg", "de_LI.UTF-8");
    liststore_add_item("\x44\x65\x75\x74\x73\x63\x68 / German, Luxembourg", "/images/lu.svg", "de_LU.UTF-8");
    liststore_add_item("\xce\x95\xce\xbb\xce\xbb\xce\xb7\xce\xbd\xce\xb9\xce\xba\xce\xac / Greek, Cyprus", "/images/cy.svg", "el_CY.UTF-8");
    liststore_add_item("\xce\x95\xce\xbb\xce\xbb\xce\xb7\xce\xbd\xce\xb9\xce\xba\xce\xac / Greek, Greece", "/images/gr.svg", "el_GR.UTF-8");
    liststore_add_item("\x45\x6e\x67\x6c\x69\x73\x68 / English, Australia", "/images/au.svg", "en_AU.UTF-8");
    liststore_add_item("\x45\x6e\x67\x6c\x69\x73\x68 / English, Botswana", "/images/bw.svg", "en_BW.UTF-8");
    liststore_add_item("\x45\x6e\x67\x6c\x69\x73\x68 / English, Canada", "/images/ca.svg", "en_CA.UTF-8");
    liststore_add_item("\x45\x6e\x67\x6c\x69\x73\x68 / English, Denmark", "/images/dk.svg", "en_DK.UTF-8");
    liststore_add_item("\x45\x6e\x67\x6c\x69\x73\x68 / English, United Kingdom", "/images/gb.svg", "en_GB.UTF-8");
    liststore_add_item("\x45\x6e\x67\x6c\x69\x73\x68 / English, Hong Kong", "/images/hk.svg", "en_HK.UTF-8");
    liststore_add_item("\x45\x6e\x67\x6c\x69\x73\x68 / English, Ireland", "/images/ie.svg", "en_IE.UTF-8");
    liststore_add_item("\x45\x6e\x67\x6c\x69\x73\x68 / English, India", "/images/in.svg", "en_IN.UTF-8");
    liststore_add_item("\x45\x6e\x67\x6c\x69\x73\x68 / English, New Zealand", "/images/nz.svg", "en_NZ.UTF-8");
    liststore_add_item("\x45\x6e\x67\x6c\x69\x73\x68 / English, Philippines", "/images/ph.svg", "en_PH.UTF-8");
    liststore_add_item("\x45\x6e\x67\x6c\x69\x73\x68 / English, Sweden", "/images/se.svg", "en_SE.UTF-8");
    liststore_add_item("\x45\x6e\x67\x6c\x69\x73\x68 / English, Seychelles", "/images/sc.svg", "en_SC.UTF-8");
    liststore_add_item("\x45\x6e\x67\x6c\x69\x73\x68 / English, Singapore", "/images/sg.svg", "en_SG.UTF-8");
    liststore_add_item("\x45\x6e\x67\x6c\x69\x73\x68 / English, United States", "/images/us.svg", "en_US.UTF-8");
    liststore_add_item("\x45\x6e\x67\x6c\x69\x73\x68 / English, South Africa", "/images/za.svg", "en_ZA.UTF-8");
    liststore_add_item("\x45\x6e\x67\x6c\x69\x73\x68 / English, Zimbabwe", "/images/zw.svg", "en_ZW.UTF-8");
    liststore_add_item("\x45\x73\x70\x61\xc3\xb1\x6f\x6c / Spanish, Argentina", "/images/ar.svg", "es_AR.UTF-8");
    liststore_add_item("\x45\x73\x70\x61\xc3\xb1\x6f\x6c / Spanish, Bolivia", "/images/bo.svg", "es_BO.UTF-8");
    liststore_add_item("\x45\x73\x70\x61\xc3\xb1\x6f\x6c / Spanish, Chile", "/images/cl.svg", "es_CL.UTF-8");
    liststore_add_item("\x45\x73\x70\x61\xc3\xb1\x6f\x6c / Spanish, Colombia", "/images/co.svg", "es_CO.UTF-8");
    liststore_add_item("\x45\x73\x70\x61\xc3\xb1\x6f\x6c / Spanish, Costa Rica", "/images/cr.svg", "es_CR.UTF-8");
    liststore_add_item("\x45\x73\x70\x61\xc3\xb1\x6f\x6c / Spanish, Dominican Republic", "/images/do.svg", "es_DO.UTF-8");
    liststore_add_item("\x45\x73\x70\x61\xc3\xb1\x6f\x6c / Spanish, Ecuador", "/images/ec.svg", "es_EC.UTF-8");
    liststore_add_item("\x45\x73\x70\x61\xc3\xb1\x6f\x6c / Spanish, Spain", "/images/es.svg", "es_ES.UTF-8");
    liststore_add_item("\x45\x73\x70\x61\xc3\xb1\x6f\x6c / Spanish, Guatemala", "/images/gt.svg", "es_GT.UTF-8");
    liststore_add_item("\x45\x73\x70\x61\xc3\xb1\x6f\x6c / Spanish, Honduras", "/images/hn.svg", "es_HN.UTF-8");
    liststore_add_item("\x45\x73\x70\x61\xc3\xb1\x6f\x6c / Spanish, Mexico", "/images/mx.svg", "es_MX.UTF-8");
    liststore_add_item("\x45\x73\x70\x61\xc3\xb1\x6f\x6c / Spanish, Nicaragua", "/images/ni.svg", "es_NI.UTF-8");
    liststore_add_item("\x45\x73\x70\x61\xc3\xb1\x6f\x6c / Spanish, Panama", "/images/pa.svg", "es_PA.UTF-8");
    liststore_add_item("\x45\x73\x70\x61\xc3\xb1\x6f\x6c / Spanish, Peru", "/images/pe.svg", "es_PE.UTF-8");
    liststore_add_item("\x45\x73\x70\x61\xc3\xb1\x6f\x6c / Spanish, Puerto Rico", "/images/pr.svg", "es_PR.UTF-8");
    liststore_add_item("\x45\x73\x70\x61\xc3\xb1\x6f\x6c / Spanish, Paraguay", "/images/py.svg", "es_PY.UTF-8");
    liststore_add_item("\x45\x73\x70\x61\xc3\xb1\x6f\x6c / Spanish, El Salvador", "/images/sv.svg", "es_SV.UTF-8");
    liststore_add_item("\x45\x73\x70\x61\xc3\xb1\x6f\x6c / Spanish, United States", "/images/us.svg", "es_US.UTF-8");
    liststore_add_item("\x45\x73\x70\x61\xc3\xb1\x6f\x6c / Spanish, Uruguay", "/images/uy.svg", "es_UY.UTF-8");
    liststore_add_item("\x45\x73\x70\x61\xc3\xb1\x6f\x6c / Spanish, Venezuela", "/images/ve.svg", "es_VE.UTF-8");
    liststore_add_item("\x45\x65\x73\x74\x69 / Estonian, Estonia", "/images/ee.svg", "et_EE.UTF-8");
    liststore_add_item("\x45\x75\x73\x6b\x61\x72\x61 / Basque, Spain", "/images/es.svg", "eu_ES.UTF-8");
    liststore_add_item("\x45\x75\x73\x6b\x61\x72\x61 / Basque, France", "/images/fr.svg", "eu_FR.UTF-8");
    liststore_add_item("\x46\x69\x6c\x69\x70\x69\x6e\x6f / Filipino, Philippines", "/images/ph.svg", "fil_PH.UTF-8");
    liststore_add_item("\x53\x75\x6f\x6d\x69 / Finnish, Finland", "/images/fi.svg", "fi_FI.UTF-8");
    liststore_add_item("\x46\xc3\xb8\x72\x6f\x79\x73\x6b / Faroese, Faroe Islands", "/images/fo.svg", "fo_FO.UTF-8");
    liststore_add_item("\x46\x72\x61\x6e\xc3\xa7\x61\x69\x73 / French, Belgium", "/images/be.svg", "fr_BE.UTF-8");
    liststore_add_item("\x46\x72\x61\x6e\xc3\xa7\x61\x69\x73 / French, Canada", "/images/ca.svg", "fr_CA.UTF-8");
    liststore_add_item("\x46\x72\x61\x6e\xc3\xa7\x61\x69\x73 / French, Switzerland", "/images/ch.svg", "fr_CH.UTF-8");
    liststore_add_item("\x46\x72\x61\x6e\xc3\xa7\x61\x69\x73 / French, France", "/images/fr.svg", "fr_FR.UTF-8");
    liststore_add_item("\x46\x72\x61\x6e\xc3\xa7\x61\x69\x73 / French, Luxembourg", "/images/lu.svg", "fr_LU.UTF-8");
    liststore_add_item("\x47\x61\x65\x69\x6c\x67\x65 / Irish, Ireland", "/images/ie.svg", "ga_IE.UTF-8");
    liststore_add_item("\x47\xc3\xa0\x69\x64\x68\x6c\x69\x67 / Scottish Gaelic, United Kingdom", "/images/gb.svg", "gd_GB.UTF-8");
    liststore_add_item("\x47\x61\x6c\x65\x67\x6f / Galician, Spain", "/images/es.svg", "gl_ES.UTF-8");
    liststore_add_item("\xe0\xaa\x97\xe0\xac\x95\xe0\xab\x81\xe0\xaa\xb0\xe0\xaa\xbe\xe0\xaa\xa4\xe0\xab\x80 / Gujarati, India", "/images/in.svg", "gu_IN.UTF-8");
    liststore_add_item("\x47\x61\x65\x6c\x67\x61 / Manx, United Kingdom", "/images/gb.svg", "gv_GB.UTF-8");
    liststore_add_item("\xd7\x82\xd7\x91\xd7\xa8\xd7\x99\xd7\xaa / Hebrew, Israel", "/images/il.svg", "he_IL.UTF-8");
    liststore_add_item("\xe0\xa4\xb9\xe0\xa4\xbf\xe0\xa4\xa8\xe0\xa5\x8d\xe0\xa4\xa6\xe0\xa5\x80 / Hindi, India", "/images/in.svg", "hi_IN.UTF-8");
    liststore_add_item("\x48\x72\x76\x61\x74\x73\x6b\x69 / Croatian, Croatia", "/images/hr.svg", "hr_HR.UTF-8");
    liststore_add_item("\x48\x6f\x72\x6e\x6f\xc5\xa1\x65\x72\x62\x6a\x61\x6e\x73\x6b\x61 / Upper Sorbian, Germany", "/images/de.svg", "hsb_DE.UTF-8");
    liststore_add_item("\x4d\x61\x67\x79\x61\x72 / Hungarian, Hungary", "/images/hu.svg", "hu_HU.UTF-8");
    liststore_add_item("\x42\x61\x68\x61\x73\x61\x20\x49\x6e\x64\x6f\x6e\x65\x73\x69\x61 / Indonesian, Indonesia", "/images/id.svg", "id_ID.UTF-8");
    liststore_add_item("\xcd\x73\x6c\x65\x6e\x73\x6b\x61 / Icelandic, Iceland", "/images/is.svg", "is_IS.UTF-8");
    liststore_add_item("\x49\x74\x61\x6c\x69\x61\x6e\x6f / Italian, Switzerland", "/images/ch.svg", "it_CH.UTF-8");
    liststore_add_item("\x49\x74\x61\x6c\x69\x61\x6e\x6f / Italian, Italy", "/images/it.svg", "it_IT.UTF-8");
    liststore_add_item("\x6e\x69\x68\x6f\x6e\x67\x6f / Japanese, Japan", "/images/jp.svg", "ja_JP.UTF-8");
    liststore_add_item("\xe1\x83\x99\xe1\x83\x90\xe1\x83\xa0\xe1\x83\x97\xe1\x83\xa3\xe1\x83\xda\xe1\x83\x98 / Georgian, Georgia", "/images/ge.svg", "ka_GE.UTF-8");
    liststore_add_item("\x9a\xd0\xb0\xd0\xb7\xd0\xb0\xd2\x9b / Kazakh, Kazakhstan", "/images/kz.svg", "kk_KZ.UTF-8");
    liststore_add_item("\x4b\x61\x6c\x61\x61\x6c\x6c\x69\x73\x75\x74 / Greenlandic, Greenland", "/images/gl.svg", "kl_GL.UTF-8");
    liststore_add_item("\xe1\x9e\x97\xe1\x9e\xb6\xe1\x9e\x9f\xe1\x9e\xb6 / Khmer, Cambodia", "/images/kh.svg", "km_KH.UTF-8");
    liststore_add_item("\xe0\xbf\x95\xe0\xbe\xae\xe0\xbe\xae\xe0\xbf\x86 / Kannada, India", "/images/in.svg", "kn_IN.UTF-8");
    liststore_add_item("\xed\x95\x9c\xea\xb5\xad\xec\x96\xb4 / Korean, South Korea", "/images/kr.svg", "ko_KR.UTF-8");
    liststore_add_item("\x4b\xc3\xbc\x72\x64\xce\xae / Kurdish, Turkey", "/images/tr.svg", "ku_TR.UTF-8");
    liststore_add_item("\x43\x65\x72\x6e\x65\x77\x65\x6b / Cornish, United Kingdom", "/images/gb.svg", "kw_GB.UTF-8");
    liststore_add_item("\x4c\x75\x67\x61\x6e\x64\x61 / Ganda, Uganda", "/images/ug.svg", "lg_UG.UTF-8");
    liststore_add_item("\xe0\xba\xa3\xe0\xba\xa7 / Lao, Laos", "/images/la.svg", "lo_LA.UTF-8");
    liststore_add_item("\x4c\x69\x65\x74\x75\x76\x69\x73 / Lithuanian, Lithuania", "/images/lt.svg", "lt_LT.UTF-8");
    liststore_add_item("\x4c\x61\x74\x67\x61\x6c\x69\xc5\xa1\x6b\x61 / Latgalian, Latvia", "/images/lv.svg", "ltg_LV.UTF-8");
    liststore_add_item("\x4c\x61\x74\x76\x69\x65\xc5\xa1\x75 / Latvian, Latvia", "/images/lv.svg", "lv_LV.UTF-8");
    liststore_add_item("\x4d\x61\x6c\x67\x61\xc5\xa1\x61 / Malagasy, Madagascar", "/images/mg.svg", "mg_MG.UTF-8");
    liststore_add_item("\x4d\xc4\x81\x6f\x72\x69 / Maori, New Zealand", "/images/nz.svg", "mi_NZ.UTF-8");
    liststore_add_item("\x4d\x61\x6b\x65\x64\x6f\x6e\x73\x6b\x68\x69 / Macedonian, North Macedonia", "/images/mk.svg", "mk_MK.UTF-8");
    liststore_add_item("\xe0\xb4\xae\xe0\xb4\xb2\xe0\xb4\xaf\xe0\xb4\xbe\xe0\xb4\xb3\xe0\xb4\x82 / Malayalam, India", "/images/in.svg", "ml_IN.UTF-8");
    liststore_add_item("\x4d\x6f\x6e\x67\x6f\x6c / Mongolian, Mongolia", "/images/mn.svg", "mn_MN.UTF-8");
    liststore_add_item("\x42\x61\x68\x61\x73\x61\x20\x4d\x65\x6c\x61\x79\x73\x69\x61 / Malay, Malaysia", "/images/my.svg", "ms_MY.UTF-8");
    liststore_add_item("\x4d\x61\x6c\x74\x69 / Maltese, Malta", "/images/mt.svg", "mt_MT.UTF-8");
    liststore_add_item("\x4e\x6f\x72\x73\x6b\x20\x62\x6f\x6b\x6d\xc3\xa5\x6c / Norwegian Bokmål, Norway", "/images/no.svg", "nb_NO.UTF-8");
    liststore_add_item("\x4e\x65\x64\x65\x72\x6c\x61\x6e\x64\x73 / Dutch, Belgium", "/images/be.svg", "nl_BE.UTF-8");
    liststore_add_item("\x4e\x65\x64\x65\x72\x6c\x61\x6e\x64\x73 / Dutch, Netherlands", "/images/nl.svg", "nl_NL.UTF-8");
    liststore_add_item("\x4e\x6f\x72\x73\x6b\x20\x6e\x79\x6e\x6f\x72\x73\x6b / Norwegian Nynorsk, Norway", "/images/no.svg", "nn_NO.UTF-8");
    liststore_add_item("\x4e\x6f\x72\x73\x6b / Norwegian, Norway (Generic)", "/images/no.svg", "no_NO.UTF-8");
    liststore_add_item("\x4f\x63\x63\x69\x74\x61\x6e / Occitan, France", "/images/fr.svg", "oc_FR.UTF-8");
    liststore_add_item("\x4f\x72\x6f\x6d\x6f\x20\x67\x65\x73 / Oromo, Kenya", "/images/ke.svg", "om_KE.UTF-8");
    liststore_add_item("\x50\x6f\x6c\x73\x6b\x69 / Polish, Poland", "/images/pl.svg", "pl_PL.UTF-8");
    liststore_add_item("\x50\x6f\x72\x74\x75\x67\x75\xc3\xaa\x73 / Portuguese, Brazil", "/images/br.svg", "pt_BR.UTF-8");
    liststore_add_item("\x50\x6f\x72\x74\x75\x67\x75\xc3\xaa\x73 / Portuguese, Portugal", "/images/pt.svg", "pt_PT.UTF-8");
    liststore_add_item("\x52\x6f\x6d\xc3\xa2\x6e\xc4\x83 / Romanian, Romania", "/images/ro.svg", "ro_RO.UTF-8");
    liststore_add_item("\xd0\x91\xd1\x83\xd1\x81\xd1\x81\xd0\xba\xd0\xb8\xd0\xb9 / Russian, Russia", "/images/ru.svg", "ru_RU.UTF-8");
    liststore_add_item("\xd0\x91\xd1\x83\xd1\x81\xd1\x81\xd0\xba\xd0\xb8\xd0\xb9 / Russian, Ukraine", "/images/ua.svg", "ru_UA.UTF-8");
    liststore_add_item("\x53\x6c\x6f\x76\x65\x6e\xc4\x8d\x69\x6e\x61 / Slovak, Slovakia", "/images/sk.svg", "sk_SK.UTF-8");
    liststore_add_item("\x53\x6c\x6f\x76\x65\x6e\xc5\xa1\xc4\x8d\x69\x6e\x61 / Slovenian, Slovenia", "/images/si.svg", "sl_SI.UTF-8");
    liststore_add_item("\x53\x6f\x6f\x6d\x61\x61\x6c\x69 / Somali, Djibouti", "/images/dj.svg", "so_DJ.UTF-8");
    liststore_add_item("\x53\x6f\x6f\x6d\x61\x61\x6c\x69 / Somali, Kenya", "/images/ke.svg", "so_KE.UTF-8");
    liststore_add_item("\x53\x6f\x6f\x6d\x61\x61\x6c\x69 / Somali, Somalia", "/images/so.svg", "so_SO.UTF-8");
    liststore_add_item("\x53\x68\x71\x69\x70 / Albanian, Albania", "/images/al.svg", "sq_AL.UTF-8");
    liststore_add_item("\xd0\xa1\xd1\x80\xd0\xbf\xd1\x81\xd0\xba\xd0\xb8 / Serbian, Serbia and Montenegro (Deprecated)", "/images/cs.svg", "sr_CS.UTF-8");
    liststore_add_item("\x53\x65\x73\x6f\x74\x68\x6f / Southern Sotho, South Africa", "/images/za.svg", "st_ZA.UTF-8");
    liststore_add_item("\x53\x76\x65\x6e\x73\x6b\x61 / Swedish, Finland", "/images/fi.svg", "sv_FI.UTF-8");
    liststore_add_item("\x53\x76\x65\x6e\x73\x6b\x61 / Swedish, Sweden", "/images/se.svg", "sv_SE.UTF-8");
    liststore_add_item("\xe0\xae\xa4\xe0\xae\xae\xe0\xae\xbf\xe0\xae\xb4\xe0\xaf\x8d / Tamil, India", "/images/in.svg", "ta_IN.UTF-8");
    liststore_add_item("\x54\x75\x6c\x75 / Tulu, India", "/images/in.svg", "tcy_IN.UTF-8");
    liststore_add_item("\xd0\xa2\xd0\xbe\xd2\xb7\xd0\xb8\xd0\xba\xc3\xbd / Tajik, Tajikistan", "/images/tj.svg", "tg_TJ.UTF-8");
    liststore_add_item("\xe0\xb8\xa0\xe0\xb8\xb2\xe0\xb8\xa9\xe0\xb8\xb2\xe0\xb9\x84\xe0\xb8\x97\xe0\xb8\xa2 / Thai, Thailand", "/images/th.svg", "th_TH.UTF-8");
    liststore_add_item("\x54\x61\x67\x61\x6c\x6f\x67 / Tagalog, Philippines", "/images/ph.svg", "tl_PH.UTF-8");
    liststore_add_item("\x54\xc3\xbc\x72\x6b\xc3\xa7\x65 / Turkish, Cyprus", "/images/cy.svg", "tr_CY.UTF-8");
    liststore_add_item("\x54\xc3\xbc\x72\x6b\xc3\xa7\x65 / Turkish, Turkey", "/images/tr.svg", "tr_TR.UTF-8");
    liststore_add_item("\xd0\xa3\xd0\xba\xd1\x80\xd0\xb0\xd1\x97\xd0\xbd\xd1\x81\xd1\x8c\xd0\xba\xd0\xb0 / Ukrainian, Ukraine", "/images/ua.svg", "uk_UA.UTF-8");
    liststore_add_item("\x4f\x27\x7a\x62\x65\x6b\x63\x68\x61 / Uzbek, Uzbekistan", "/images/uz.svg", "uz_UZ.UTF-8");
    liststore_add_item("\x54\x69\xe1\xba\xbf\x6e\x67\x20\x56\x69\xe1\xbb\x87\x74 / Vietnamese, Vietnam", "/images/vn.svg", "vi_VN.UTF-8");
    liststore_add_item("\x57\x61\x6c\x6f\x6e / Walloon, Belgium", "/images/be.svg", "wa_BE.UTF-8");
    liststore_add_item("\x49\x73\x69\x58\x68\x6f\x73\x61 / Xhosa, South Africa", "/images/za.svg", "xh_ZA.UTF-8");
    liststore_add_item("\x49\x64\x69\x73\x68 / Yiddish, United States", "/images/us.svg", "yi_US.UTF-8");
    liststore_add_item("\x53\x69\x6d\x70\x6c\x69\x66\x69\x65\x64\x20\x43\x68\x69\x6e\x65\x73\x65 / Simplified Chinese, China", "/images/cn.svg", "zh_CN.UTF-8");
    liststore_add_item("\x43\x61\x6e\x74\x6f\x6e\x65\x73\x65 / Cantonese, Hong Kong", "/images/hk.svg", "zh_HK.UTF-8");
    liststore_add_item("\x53\x69\x6d\x70\x6c\x69\x66\x69\x65\x64\x20\x43\x68\x69\x6e\x65\x73\x65 / Simplified Chinese, Singapore", "/images/sg.svg", "zh_SG.UTF-8");
    liststore_add_item("\x54\x72\x61\x64\x69\x74\x69\x6f\x6e\x61\x6c\x20\x43\x68\x69\x6e\x65\x73\x65 / Traditional Chinese, Taiwan", "/images/tw.svg", "zh_TW.UTF-8");
    liststore_add_item("\x49\x73\x69\x5a\x75\x6c\x75 / Zulu, South Africa", "/images/za.svg", "zu_ZA.UTF-8");
}
