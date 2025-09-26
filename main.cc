//Build: g++ -std=c++17 main.cc resources.c -o app $(pkg-config --cflags --libs gtkmm-4.0)
#include <gtkmm.h>
#include <iostream>

#include <gtkmm/application.h>
//#include "resources.c"

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  ~ExampleWindow() override;

protected:
  // Signal handlers:
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

  // A Gio::ListStore item.
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
  }; // ModelColumns

  // Child widget:
  Gtk::DropDown m_DropDown;

  Glib::RefPtr<Gio::ListStore<ModelColumns>> m_ListStore;
};


ExampleWindow::ExampleWindow()
{
  set_title("DropDown example");

  // Add the DropDown to the window.
  set_child(m_DropDown);

  // Factory for presenting the selected item.
  auto factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_setup_selected_item));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_bind_selected_item));
  m_DropDown.set_factory(factory);

  // Factory for presenting the items in the dropdown list.
  factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_setup_list_item));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_bind_list_item));
  factory->signal_unbind().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_unbind_list_item));
  m_DropDown.set_list_factory(factory);

  // Create the model and fill it.
  create_model();
  m_DropDown.set_model(m_ListStore);
  m_DropDown.set_selected(0);

  // Connect signal handler:
  m_DropDown.property_selected().signal_changed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_dropdown_changed));
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_dropdown_changed()
{
  const auto selected = m_DropDown.get_selected();
  std::cout << "DropDown changed: Row=" << selected
    << ", Title=" << m_ListStore->get_item(selected)->m_title << ", LANG=" << m_ListStore->get_item(selected)->m_description<< std::endl;
}

void ExampleWindow::create_model()
{
  m_ListStore = Gio::ListStore<ModelColumns>::create();
// C.UTF-8
    liststore_add_item("Default C (English)",				                                                                        "", "C.UTF-8");// 
// aa_DJ.UTF-8 Afar, Ethiopia
    liststore_add_item("\x51\x61\x66\x61\x72\x20\x61\x66 / Afar, Ethiopia", "", "aa_DJ.UTF-8");//
// af_ZA.UTF-8
    liststore_add_item("\x41\x66\x72\x69\x6b\x61\x61\x6e\x73 / Afrikaans, South Africa"                                                       ,"/toolbar/za.svg", "af_ZA.UTF-8");// 	Afrikaans_South Africa.1252 	WINDOWS-1252
// an_ES.UTF-8
    liststore_add_item("\x41\x72\x61\x67\x6f\x6e\xc3\xa9\x73 / Aragonese, Spain", "", "an_ES.UTF-8");//
// ar_AE.UTF-8
    liststore_add_item("\xd8\xa7\xd9\x8e\xd9\x84\xd9\x92\xd8\xb9\xd9\x8e\xd8\xb1\xd9\x8e\xd8\xa8\xd9\x90\xd9\x8a\xd9\x8e\xd9\x91\xd8\xa9\xd9\x8f\x20\x28\x61\x6c\x2d\xca\xbf\x61\x72\x61\x62\x69\x79\x79\x61\x68\x29\x20 / Arabic, United Arab Emirates", "", "ar_AE.UTF-8");//
// ar_BH.UTF-8
    liststore_add_item("Arabic, Bahrain", "", "ar_BH.UTF-8");//
// ar_DZ.UTF-8
    liststore_add_item("Arabic, Algeria", "", "ar_DZ.UTF-8");//
// ar_EG.UTF-8
    liststore_add_item("Arabic, Egypt", "", "ar_EG.UTF-8");//
// ar_IQ.UTF-8
    liststore_add_item("Arabic, Iraq", "", "ar_IQ.UTF-8");//
// ar_JO.UTF-8
    liststore_add_item("Arabic, Jordan", "", "ar_JO.UTF-8");//
// ar_KW.UTF-8
    liststore_add_item("Arabic, Kuwait", "", "ar_KW.UTF-8");//
// ar_LB.UTF-8
    liststore_add_item("Arabic, Lebanon", "", "ar_LB.UTF-8");//
// ar_LY.UTF-8
    liststore_add_item("Arabic, Libya", "", "ar_LY.UTF-8");//
// ar_MA.UTF-8
    liststore_add_item("Arabic, Morocco", "", "ar_MA.UTF-8");//
// ar_OM.UTF-8
    liststore_add_item("Arabic, Oman", "", "ar_OM.UTF-8");//
// ar_QA.UTF-8
    liststore_add_item("Arabic, Qatar", "", "ar_QA.UTF-8");//
// ar_SA.UTF-8
  liststore_add_item("\xd8\xa7\xd9\x84\xd8\xb9\xd8\xb1\xd8\xa8\xd9\x8a\xd8\xa9  /  Arabic, Saudi Arabia",                               "/toolbar/sa.svg", "ar_SA.UTF-8");// 	Arabic_Saudi Arabia.1256 	WINDOWS-1256
// ar_SD.UTF-8
    liststore_add_item("Arabic, Sudan", "", "ar_SD.UTF-8");//
// ar_SY.UTF-8
    liststore_add_item("Arabic, Syrian", "", "ar_SY.UTF-8");//
// ar_TN.UTF-8
    liststore_add_item("Arabic, Tunisia", "", "ar_TN.UTF-8");//
// ar_YE.UTF-8
    liststore_add_item("Arabic, Yemen", "", "ar_YE.UTF-8");//
// ast_ES.UTF-8
    liststore_add_item("Asturian (Spain)", "", "ast_ES.UTF-8");//
// be_BY.UTF-8
  liststore_add_item("\xd0\xb1\xd0\xb5\xd0\xbb\xd0\xb0\xd1\x80\xd1\x83\xd1\x81\xd0\xba\xd0\xb0\xd1\x8f / Belarusian",     "/toolbar/by.svg", "be_BY.UTF-8");// 	Belarusian_Belarus.1251 	WINDOWS-1251
// bg_BG.UTF-8
  liststore_add_item("\xd0\xb1\xd1\x8a\xd0\xbb\xd0\xb3\xd0\xb0\xd1\x80\xd1\x81\xd0\xba\xd0\xb8 / Bulgarian",		       "/toolbar/bg.svg", "bg_BG.UTF-8");// 	Bulgarian_Bulgaria.1251 	WINDOWS-1251
// bhb_IN.UTF-8
    liststore_add_item("Bhili, India", "", "bhb_IN.UTF-8");//
// br_FR.UTF-8
    liststore_add_item("\x42\x72\x65\x7a\x68\x6f\x6e\x65\x67 / Breton, France", "", "br_FR.UTF-8");//
// bs_BA.UTF-8
liststore_add_item("\xd0\xb1\xd0\xbe\xd1\x81\xd0\xb0\xd0\xbd\xd1\x81\xd0\xba\xd0\xb8 / Bosnian",					       "/toolbar/bs.svg", "bs_BA.UTF-8");// 	Bosnian (Latin) 	WINDOWS-1250
// ca_AD.UTF-8
    liststore_add_item("\x43\x61\x74\x61\x6c\xc3\xa0 / Catalan, Andorra", "", "ca_AD.UTF-8");//
// ca_ES.UTF-8
  liststore_add_item("\x63\x61\x74\x61\x6c\xc3\xa0 / Catalan, Spain",					                                        "/toolbar/es.svg", "ca_ES.UTF-8");// 	Catalan_Spain.1252 	WINDOWS-1252
// ca_FR.UTF-8
    liststore_add_item("Catalan, France", "", "ca_FR.UTF-8");//
// ca_IT.UTF-8
    liststore_add_item("Catalan, Italy", "", "ca_IT.UTF-8");//
// cs_CZ.UTF-8
  liststore_add_item("\xc4\x8d\x65\xc5\xa1\x74\x69\x6e\x61 / Czech",					                                     "/toolbar/cz.svg", "cs_CZ.UTF-8");// 	Czech_Czech Republic.1250 	WINDOWS-1250
// cy_GB.UTF-8
    liststore_add_item("Cymraeg / Welsh, United Kingdom", "", "cy_GB.UTF-8");//
// da_DK.UTF-8
  liststore_add_item("\x64\x61\x6e\x73\x6b / Danish",					                                                     "/toolbar/dk.svg", "da_DK.UTF-8");// 	Danish_Denmark.1252 	WINDOWS-1252
// de_AT.UTF-8
  liststore_add_item("German, Austria",					                                      "/toolbar/at.svg","de_AT.UTF-8");//
// de_BE.UTF-8
    liststore_add_item("German, Belgium", "", "de_BE.UTF-8");//
// de_CH.UTF-8
    liststore_add_item("German, Switzerland", "", "de_CH.UTF-8");//
// de_DE.UTF-8
  liststore_add_item("\x44\x65\x75\x74\x73\x63\x68 / German, Germany",					                                              "/toolbar/de.svg","de_DE.UTF-8");// 	German_Germany.1252 	WINDOWS-1252
// de_IT.UTF-8
    liststore_add_item("German, Italy", "", "de_IT.UTF-8");//
// de_LI.UTF-8
    liststore_add_item("German, Liechtenstein", "", "de_LI.UTF-8");//
// de_LU.UTF-8
    liststore_add_item("German, Luxembourg", "", "de_LU.UTF-8");//
// el_CY.UTF-8
    liststore_add_item("Greek, Cyprus", "", "el_CY.UTF-8");//
// el_GR.UTF-8
  liststore_add_item("\xce\x95\xce\xbb\xce\xbb\xce\xb7\xce\xbd\xce\xb9\xce\xba\xce\xac / Greek",					        "/toolbar/gr.svg", "el_GR.UTF-8");// 	Greek_Greece.1253 	WINDOWS-1253
// en_AU.UTF-8
  liststore_add_item("English, Australia",					                                                 "/toolbar/au.svg", "en_AU.UTF-8"   );//     English_Australia.1252 	-empty string-
// en_BW.UTF-8
    liststore_add_item("English, Botswana", "", "en_BW.UTF-8");//
// en_CA.UTF-8
    liststore_add_item("English, Canada", "", "en_CA.UTF-8");//
// en_DK.UTF-8
    liststore_add_item("English, Denmark", "", "en_DK.UTF-8");//
// en_GB.UTF-8
    liststore_add_item("English, United Kingdom",					                                                 "/toolbar/gb.svg", "en_GB.UTF-8");//     English_ GB
// en_HK.UTF-8
    liststore_add_item("English, Hong Kong", "", "en_HK.UTF-8");//
// en_IE.UTF-8
    liststore_add_item("English, Ireland", "", "en_IE.UTF-8");//
// en_NZ.UTF-8
    liststore_add_item("English, New Zealand", "", "en_NZ.UTF-8");//
// en_PH.UTF-8
    liststore_add_item("English, Philippines", "", "en_PH.UTF-8");//
// en_SC.UTF-8
    liststore_add_item("English, Seychelles", "", "en_SC.UTF-8");//
// en_SG.UTF-8
    liststore_add_item("English, Singapore", "", "en_SG.UTF-8");//
// en_US.UTF-8
    liststore_add_item("English, United States",				                                                     "/toolbar/us.svg", "en_US.UTF-8"    );//     used-parent en_utf8 used- 	-parent en_utf8
// en_ZA.UTF-8
    liststore_add_item("English, South Africa", "", "en_ZA.UTF-8");//
// en_ZW.UTF-8
    liststore_add_item("English, Zimbabwe", "", "en_ZW.UTF-8");//
// es_AR.UTF-8
    liststore_add_item("Spanish, Argentina", "", "es_AR.UTF-8");//
// es_BO.UTF-8
    liststore_add_item("Spanish, Bolivia", "", "es_BO.UTF-8");//
// es_CL.UTF-8
    liststore_add_item("Spanish, Chile", "", "es_CL.UTF-8");//
// es_CO.UTF-8
    liststore_add_item("Spanish, Colombia", "", "es_CO.UTF-8");//
// es_CR.UTF-8
    liststore_add_item("Spanish, Costa Rica", "", "es_CR.UTF-8");//
// es_DO.UTF-8
    liststore_add_item("Spanish, Dominican Republic", "", "es_DO.UTF-8");//
// es_EC.UTF-8
    liststore_add_item("Spanish, Ecuador", "", "es_EC.UTF-8");//
// es_ES.UTF-8
  liststore_add_item("\x65\x73\x70\x61\xc3\xb1\x6f\x6c / Spanish, Spain",	                                        "/toolbar/es.svg", "es_ES.UTF-8");// 	Spanish_Spain.1252 	WINDOWS-1252
// es_GT.UTF-8
    liststore_add_item("Spanish, Guatemala", "", "es_GT.UTF-8");//
// es_HN.UTF-8
    liststore_add_item("Spanish, Heard Island and McDonald Islands", "", "es_HN.UTF-8");//
// es_MX.UTF-8
    liststore_add_item("Spanish, Mexico", "", "es_MX.UTF-8");//
// es_NI.UTF-8
    liststore_add_item("Spanish, Nicaragua", "", "es_NI.UTF-8");//
// es_PA.UTF-8
    liststore_add_item("Spanish, Panama", "", "es_PA.UTF-8");//
// es_PE.UTF-8
    liststore_add_item("Spanish, Peru", "", "es_PE.UTF-8");//
// es_PR.UTF-8
    liststore_add_item("Spanish, Puerto Rico", "", "es_PR.UTF-8");//
// es_PY.UTF-8
    liststore_add_item("Spanish, Paraguay", "", "es_PY.UTF-8");//
// es_SV.UTF-8
    liststore_add_item("Spanish, El Salvador", "", "es_SV.UTF-8");//
// es_US.UTF-8
    liststore_add_item("Spanish, United States of America", "", "es_US.UTF-8");//
// es_UY.UTF-8
    liststore_add_item("Spanish, Uruguay", "", "es_UY.UTF-8");//
// es_VE.UTF-8
    liststore_add_item("Spanish, ", "", "es_VE.UTF-8");//
// et_EE.UTF-8
  liststore_add_item("\x65\x65\x73\x74\x69 / Estonian, Estonia",					                                                 "/toolbar/ee.svg", "et_EE.UTF-8");// 	Estonian_Estonia.1257 	WINDOWS-1257
// eu_ES.UTF-8
  liststore_add_item("\x65\x75\x73\x6b\x61\x72\x61 / Basque, Spain",					                                            "/toolbar/es.svg", "eu_ES.UTF-8");// 	Basque_Spain.1252 	WINDOWS-1252
// eu_FR.UTF-8
  liststore_add_item("\xd9\x81\xd8\xa7\xd8\xb1\xd8\xb3\xd9\x89 / Farsi, France",					                                "/toolbar/ir.svg", "fa_IR.UTF-8");// 	Farsi_Iran.1256 	WINDOWS-1256
// fil_PH.UTF-8
  liststore_add_item("\x46\x69\x6c\x69\x70\x69\x6e\x6f / Filipino, Philippines",					                                    "/toolbar/ph.svg", "fil_PH.UTF-8");// 	Filipino_Philippines.1252 	WINDOWS-1252
// fi_FI.UTF-8
  liststore_add_item("\x73\x75\x6f\x6d\x69 / Finnish",					                                                "/toolbar/fi.svg", "fi_FI.UTF-8");// 	Finnish_Finland.1252 	WINDOWS-1252
// fo_FO.UTF-8
    liststore_add_item("\x46\xc3\xb8\x72\x6f\x79\x73\x6b\x74 / Faroese, Faroe Islands", "", "fo_FO.UTF-8");//
// fr_BE.UTF-8
    liststore_add_item("French, Belgium", "", "fr_BE.UTF-8");//
// fr_CA.UTF-8
    liststore_add_item("French, Canada", "", "fr_CA.UTF-8");//
// fr_CH.UTF-8
    liststore_add_item("French, Switzerland", "", "fr_CH.UTF-8");//
// fr_FR.UTF-8
  liststore_add_item("\x66\x72\x61\x6e\xc3\xa7\x61\x69\x73 / French",					                                    "/toolbar/fr.svg", "fr_FR.UTF-8");// 	French_France.1252 	WINDOWS-1252
// fr_LU.UTF-8
    liststore_add_item("French, Luxembourg", "", "fr_LU.UTF-8");//
// ga_IE.UTF-8
  liststore_add_item("\x47\xc3\xa0\x69\x64\x68\x6c\x69\x67 / Gaelic, Ireland",					                                    "/toolbar/ga.svg", "ga_IE.UTF-8"   );// 	Gaelic; Scottish Gaelic 	WINDOWS-1252
// gd_GB.UTF-8
    liststore_add_item("Gaelic, United Kingdom", "", "gd_GB.UTF-8");//
// gl_ES.UTF-8
  liststore_add_item("\x67\x61\x6c\x65\x67\x6f / Galician",					                                            "/toolbar/gl.svg", "gl_ES.UTF-8");// 	Galician_Spain.1252 	WINDOWS-1252
// gu_IN.UTF-8
  liststore_add_item("\xe0\xaa\x97\xe0\xab\x81\xe0\xaa\x9c\xe0\xaa\xb0\xe0\xaa\xbe\xe0\xaa\xa4\xe0\xab\x80 / Gujarati",		"/toolbar/gu.svg", "gu_IN.UTF-8"   );// 	Gujarati_India.0
// gv_GB.UTF-8
    liststore_add_item("Manx, United Kingdom", "", "gv_GB.UTF-8");//
// he_IL.UTF-8
  liststore_add_item("\xd7\xa2\xd7\x91\xd7\xa8\xd7\x99\xd7\xaa / Hebrew, Israel",					                                "/toolbar/il.svg", "he_IL.utf8" );// 	Hebrew_Israel.1255 	WINDOWS-1255
// hi_IN.UTF-8
  liststore_add_item("\xe0\xa4\xb9\xe0\xa4\xbf\xe0\xa4\x82\xe0\xa4\xa6\xe0\xa5\x80 / Hindi, India",					            "/toolbar/in.svg", "hi_IN.UTF-8");// 	Hindi.65001 	-empty string-
// hr_HR.UTF-8
  liststore_add_item("\x68\x72\x76\x61\x74\x73\x6b\x69 / Croatian, Croatia",					                                    "/toolbar/hr.svg", "hr_HR.UTF-8");// 	Croatian_Croatia.1250 	WINDOWS-1250
// hsb_DE.UTF-8
    liststore_add_item("Upper Sorbian, Germany", "", "hsb_DE.UTF-8");//
// hu_HU.UTF-8
  liststore_add_item("\x6d\x61\x67\x79\x61\x72 / Hungarian, Hungary",				                                                 "/toolbar/hu.svg", "hu_HU.UTF-8"   );// 	Hungarian_Hungary.1250 	WINDOWS-1250
// id_ID.UTF-8
  liststore_add_item("\x42\x61\x68\x61\x73\x61\x20\x49\x6e\x64\x6f\x6e\x65\x73\x69\x61 / Indonesian, Indonesia",				        "/toolbar/id.svg", "id_ID.UTF-8");// 	Indonesian_indonesia.1252 	WINDOWS-1252
// is_IS.UTF-8
  liststore_add_item("\xc3\xad\x73\x6c\x65\x6e\x73\x6b\x61 / Icelandic, Iceland",				                                     "/toolbar/is.svg", "is_IS.UTF-8");// 	Icelandic_Iceland.1252 	WINDOWS-1252
// it_CH.UTF-8
    liststore_add_item("Italian, Switzerland", "", "it_CH.UTF-8");//
// it_IT.UTF-8
  liststore_add_item("\x69\x74\x61\x6c\x69\x61\x6e\x6f / Italian, Italy",					                                     "/toolbar/it.svg", "it_IT.UTF-8");// 	Italian_Italy.1252 	WINDOWS-1252
// ja_JP.UTF-8
  liststore_add_item("\xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e / Japanese, Japan",					                                "/toolbar/jp.svg", "ja_JP.UTF-8");// 	Japanese_Japan.932 	CP932
// ka_GE.UTF-8
  liststore_add_item("\xe1\x83\xa5\xe1\x83\x90\xe1\x83\xa0\xe1\x83\x97\xe1\x83\xa3\xe1\x83\x9a\xe1\x83\x98 / Georgian, Georgia",		"/toolbar/ge.svg", "ka_GE.UTF-8");// 	Georgian_Georgia.65001 	-empty string-
// kk_KZ.UTF-8
    liststore_add_item("\xd2\x9a\xd0\xb0\xd0\xb7\xd0\xb0\xd2\x9b\xd1\x88\xd0\xb0\x3b\x20\x51\x61\x7a\x61\x71\xc5\x9f\x61 / Kazakh, Kazakhstan", "", "kk_KZ.UTF-8");//
// kl_GL.UTF-8
    liststore_add_item("Kalaallisut, Greenland", "", "kl_GL.UTF-8");//
// km_KH.UTF-8
  liststore_add_item("\xe1\x9e\x81\xe1\x9f\x92\xe1\x9e\x98\xe1\x9f\x82\xe1\x9e\x9a / Khmer, Cambodia",					            "/toolbar/kh.svg", "km_KH.UTF-8");// 	Khmer.65001 	-empty string-
// kn_IN.UTF-8
  liststore_add_item("\xe0\xb2\x95\xe0\xb2\xa8\xe0\xb3\x8d\xe0\xb2\xa8\xe0\xb2\xa1 / Kannada, India",					            "/toolbar/kan.svg", "kn_IN.UTF-8");// 	Kannada.65001 	-empty string-
// ko_KR.UTF-8
  liststore_add_item("\xed\x95\x9c\xea\xb5\xad\xec\x96\xb4 / Korean, Korea",					                                     "/toolbar/kr.svg", "ko_KR.UTF-8");// 	Korean_Korea.949 	EUC-KR
// ku_TR.UTF-8
    liststore_add_item("Kurdish, Turkey", "", "ku_TR.UTF-8");//
// kw_GB.UTF-8
    liststore_add_item("Cornish, United Kingdom", "", "kw_GB.UTF-8");//
// lg_UG.UTF-8
    liststore_add_item("Galician, Uganda", "", "lg_UG.UTF-8");//
// lo_LA.UTF-8
  liststore_add_item("\xe0\xba\xa5\xe0\xba\xb2\xe0\xba\xa7 / Lao",						                                 "/toolbar/la.svg", "lo_LA.UTF-8");// 	Lao_Laos.UTF-8 	WINDOWS-1257
// lt_LT.UTF-8
  liststore_add_item("\x6c\x69\x65\x74\x75\x76\x69\xc5\xb3 / Lithuanian",				                                     "/toolbar/lt.svg", "lt_LT.UTF-8");// 	Lithuanian_Lithuania.1257 	WINDOWS-1257
// ltg_LV.UTF-8
    liststore_add_item("", "", "ltg_LV.UTF-8");//
// lv_LV.UTF-8
  liststore_add_item("\x6c\x61\x74\x76\x69\x65\xc5\xa1\x75 / Latvian",					                                "/toolbar/lv.svg", "lv_LV.UTF-8"  );// 	Latvian_Latvia.1257 	WINDOWS-1257
// mg_MG.UTF-8
    liststore_add_item("", "", "mg_MG.UTF-8");//
// mi_NZ.UTF-8
  liststore_add_item("\x52\x65\x6f\x20\x4d\xc4\x81\x6f\x72\x69 / Maori",		                                            "/toolbar/nz.svg", "mi_NZ.UTF-8");// 	Maori.1252 	WINDOWS-1252
// mk_MK.UTF-8
    liststore_add_item("", "", "mk_MK.UTF-8");//
// ml_IN.UTF-8
  liststore_add_item("\xe0\xb4\xae\xe0\xb4\xb2\xe0\xb4\xaf\xe0\xb4\xbe\xe0\xb4\xb3\xe0\xb4\x82 / Malayalam",				"/toolbar/in.svg", "ml_IN.UTF-8");//    	Malayalam_India.x-iscii-ma 	x-iscii-ma
// mn_MN.UTF-8  
  liststore_add_item("\xd0\x9c\xd0\xbe\xd0\xbd\xd0\xb3\xd0\xbe\xd0\xbb\x20\xd1\x85\xd1\x8d\xd0\xbb\x2f\xe1\xa0\xae\xe1\xa0\xa4\xe1\xa0\xa8\xe1\xa0\xad\xe1\xa0\xad\xe1\xa0\xa4\xe1\xa0\xaf\x20\xe1\xa0\xac\xe1\xa0\xa1\xe1\xa0\xaf\xe1\xa0\xa1 / Mongolian",				"/toolbar/mn.svg", "mn_MN.UTF-8"   );// 	Cyrillic_Mongolian.1251
// ms_MY.UTF-8
  liststore_add_item("\x42\x61\x68\x61\x73\x61\x20\x4d\x61\x6c\x61\x79\x73\x69\x61 / Malaysian",				            "/toolbar/my.svg", "ms_MY.UTF-8");// 	Malay_malaysia.1252 	WINDOWS-1252
// mt_MT.UTF-8
    liststore_add_item("", "", "mt_MT.UTF-8");//
// nb_NO.UTF-8
    liststore_add_item("", "", "nb_NO.UTF-8");//
// nl_BE.UTF-8
    liststore_add_item("", "", "nl_BE.UTF-8");//
// nl_NL.UTF-8
  liststore_add_item("\x4e\x65\x64\x65\x72\x6c\x61\x6e\x64\x73 / Dutch",					                                 "/toolbar/nl.svg", "nl_NL.UTF-8");// 	Dutch_Netherlands.1252 	WINDOWS-1252
// nn_NO.UTF-8
  liststore_add_item("\x6e\x6f\x72\x73\x6b / Nynorsk",					            "/toolbar/no.svg", "	nn_NO.UTF-8");// 	Norwegian-Nynorsk_Norway.1252 	WINDOWS-1252
// no_NO.UTF-8
  liststore_add_item("\x6e\x6f\x72\x73\x6b / Norwegian",		                                                              "/toolbar/no.svg", "no_NO.UTF-8");// 	-parent no_utf8 used- 	-parent no_utf8 used-
// oc_FR.UTF-8
    liststore_add_item("", "", "oc_FR.UTF-8");//
// om_KE.UTF-8
    liststore_add_item("", "", "om_KE.UTF-8");//
// pl_PL.UTF-8
  liststore_add_item("\x70\x6f\x6c\x73\x6b\x69 / Polish",				                                                    	"/toolbar/pl.svg", "pl.UTF-8"   );// 	Polish_Poland.1250 	WINDOWS-1250
// pt_BR.UTF-8
    liststore_add_item("", "", "pt_BR.UTF-8");//
// pt_PT.UTF-8
  liststore_add_item("\x70\x6f\x72\x74\x75\x67\x75\xc3\xaa\x73 / Portuguese",				                                "/toolbar/pt.svg", "pt_PT.UTF-8");// 	Portuguese_Portugal.1252 	WINDOWS-1252
// ro_RO.UTF-8
  liststore_add_item("\x72\x6f\x6d\xc3\xa2\x6e\xc4\x83 / Romanian",					                                    "/toolbar/ro.svg", "ro_RO.UTF-8");// 	Romanian_Romania.1250 	WINDOWS-1250
// ru_RU.UTF-8
  liststore_add_item("\xd1\x80\xd1\x83\xd1\x81\xd1\x81\xd0\xba\xd0\xb8\xd0\xb9 / Russian",					                "/toolbar/ru.svg", "ru_RU.UTF-8");// 	Russian_Russia.1251 	WINDOWS-1251
// ru_UA.UTF-8
    liststore_add_item("", "", "ru_UA.UTF-8");//
// sk_SK.UTF-8
  liststore_add_item("\x73\x6c\x6f\x76\x65\x6e\xc4\x8d\x69\x6e\x61 / Slovak",					                            "/toolbar/sk.svg", "sk_SK.UTF-8");// 	Slovak_Slovakia.1250 	WINDOWS-1250
// sl_SI.UTF-8
  liststore_add_item("\x73\x6c\x6f\x76\x65\x6e\x73\x6b\x69 / Slovenian",				                                    "/toolbar/si.svg", "sl_SI.UTF-8");// 	Slovenian_Slovenia.1250 	WINDOWS-1250
// so_DJ.UTF-8
    liststore_add_item("", "", "so_DJ.UTF-8");//
// so_KE.UTF-8
    liststore_add_item("", "", "so_KE.UTF-8");//
// so_SO.UTF-8
    liststore_add_item("", "", "so_SO.UTF-8");//
// sq_AL.UTF-8
  liststore_add_item("\x73\x68\x71\x69\x70 / Albanian",					                                                "/toolbar/al.svg", "sq_AL.UTF-8");// 	Albanian_Albania.1250 	WINDOWS-1250
// sr_CS.UTF-8  
  liststore_add_item("\x73\x72\x70\x73\x6b\x69\x2f\xd1\x81\xd1\x80\xd0\xbf\xd1\x81\xd0\xba\xd0\xb8 / Serbian",				"/toolbar/rs.svg", "sr_CS.UTF-8");// 	Bosnian(Cyrillic), Serbian (Cyrillic) 	WINDOWS-1251
// st_ZA.UTF-8
    liststore_add_item("", "", "st_ZA.UTF-8");//
// sv_FI.UTF-8
    liststore_add_item("", "", "sv_FI.UTF-8");//
// sv_SE.UTF-8
  liststore_add_item("\x73\x76\x65\x6e\x73\x6b\x61 / Swedish",					                                        "/toolbar/se.svg", "sv_SE.UTF-8");// 	Swedish_Sweden.1252 	WINDOWS-1252
// ta_IN.UTF-8
  liststore_add_item("\xe0\xae\xa4\xe0\xae\xae\xe0\xae\xbf\xe0\xae\xb4\xe0\xaf\x8d / Tamil",					            "/toolbar/in.svg", "ta_IN.UTF-8");// 	
// tcy_IN.UTF-8
    liststore_add_item("", "", "tcy_IN.UTF-8");//
// tg_TJ.UTF-8
    liststore_add_item("", "", "tg_TJ.UTF-8");//
// th_TH.UTF-8
  liststore_add_item("\xe0\xb9\x84\xe0\xb8\x97\xe0\xb8\xa2 / Thai",						                                 "/toolbar/th.svg", "th_TH.UTF-8");// 	Thai_Thailand.874 	WINDOWS-874
// tl_PH.UTF-8
    liststore_add_item("", "", "tl_PH.UTF-8");//
// tr_CY.UTF-8
    liststore_add_item("", "", "tr_CY.UTF-8");//
// tr_TR.UTF-8
  liststore_add_item("\x54\xc3\xbc\x72\x6b\xc3\xa7\x65 / Turkish",					                                    "/toolbar/tr.svg", "tr_TR.UTF-8");// 	Turkish_Turkey.1254 	WINDOWS-1254
// uk_UA.UTF-8
  liststore_add_item("\xd1\x83\xd0\xba\xd1\x80\xd0\xb0\xd1\x97\xd0\xbd\xd1\x81\xd1\x8c\xd0\xba\xd0\xb0 / Ukrainian",		"/toolbar/ua.svg", "uk_UA.UTF-8");// 	Ukrainian_Ukraine.1251 	WINDOWS-1251
// uz_UZ.UTF-8
    liststore_add_item("", "", "uz_UZ.UTF-8");//
// vi_VN.UTF-8
  liststore_add_item("\x54\x69\xe1\xba\xbf\x6e\x67\x20\x56\x69\xe1\xbb\x87\x74 / Vietnamese",				                "/toolbar/vn.svg", "vi_VN.UTF-8");// 	Vietnamese_Viet Nam.1258 	WINDOWS-1258
// wa_BE.UTF-8
    liststore_add_item("", "", "wa_BE.UTF-8");//
// xh_ZA.UTF-8
    liststore_add_item("", "", "xh_ZA.UTF-8");//
// yi_US.UTF-8
    liststore_add_item("", "", "yi_US.UTF-8");//
// zh_CN.UTF-8
  liststore_add_item("\xe4\xb8\xad\xe6\x96\x87 / Chinese",		                                                         "/toolbar/cn.svg", "zh_CN.UTF-8");// 	Chinese_China.936 	CP936
// zh_HK.UTF-8
    liststore_add_item("", "", "zh_HK.UTF-8");//
// zh_SG.UTF-8
    liststore_add_item("", "", "zh_SG.UTF-8");//
// zh_TW.UTF-8
  liststore_add_item("\xe5\x8f\xb0\xe7\x81\xa3\x20 / Chinese (Taiwan)",	                                                 "/toolbar/tw.svg", "zh_TW.UTF-8");// 	Chinese_Taiwan.950 	CP950
// zu_ZA.UTF-8
}

void ExampleWindow::liststore_add_item(const Glib::ustring& title,
  const Glib::ustring& icon, const Glib::ustring& description)
{
  m_ListStore->append(ModelColumns::create(title, icon, description));
}

void ExampleWindow::on_setup_selected_item(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 10);
  //  auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 2);
     
  box->append(*Gtk::make_managed<Gtk::Image>());
  //box->append(*vbox); 
  box->set_baseline_position(Gtk::BaselinePosition::CENTER);
  box->append(*Gtk::make_managed<Gtk::Label>());
  list_item->set_child(*box);
}

void ExampleWindow::on_bind_selected_item(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;
  auto box = dynamic_cast<Gtk::Box*>(list_item->get_child());
  if (!box)
    return;
  auto image = dynamic_cast<Gtk::Image*>(box->get_first_child());
  if (!image)
    return;
  image->set(col->m_icon);
 // image->set_icon_size( Gtk::IconSize::LARGE 	);
  image->set_pixel_size(150);


  
  auto label = dynamic_cast<Gtk::Label*>(image->get_next_sibling());
  if (!label)
    return;
  label->set_text(col->m_title);
  
}

void ExampleWindow::on_setup_list_item(const Glib::RefPtr<Gtk::ListItem>& list_item)
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

void ExampleWindow::on_bind_list_item(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;
  auto hbox = dynamic_cast<Gtk::Box*>(list_item->get_child());
  if (!hbox)
    return;
  auto image = dynamic_cast<Gtk::Image*>(hbox->get_first_child());
  if (!image)
    return;
  //image->set_from_icon_name(col->m_icon);
   /// image->set(col->m_icon);
   // image->set_icon_size(Gtk::IconSize::LARGE);
      image->set_pixel_size(120);
    image->set(col->m_icon);
    //    image->set("./toolbar/af.svg");
  auto vbox = dynamic_cast<Gtk::Box*>(image->get_next_sibling());
  if (!vbox)
    return;
  auto title = dynamic_cast<Gtk::Label*>(vbox->get_first_child());
  if (!title)
    return;
  title->set_text(col->m_title);
  auto description = dynamic_cast<Gtk::Label*>(title->get_next_sibling());
  if (!description)
    return;
  description->set_text(col->m_description);

  auto connection = m_DropDown.property_selected_item().signal_changed().connect(
    sigc::bind(sigc::mem_fun(*this, &ExampleWindow::on_selected_item_changed),
    list_item));
  list_item->set_data("connection", new sigc::connection(connection),
    Glib::destroy_notify_delete<sigc::connection>);
  on_selected_item_changed(list_item);
}

void ExampleWindow::on_unbind_list_item(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  if (auto connection = static_cast<sigc::connection*>(list_item->get_data("connection")))
  {
    connection->disconnect();
    list_item->set_data("connection", nullptr);
  }
}

void ExampleWindow::on_selected_item_changed(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto hbox = dynamic_cast<Gtk::Box*>(list_item->get_child());
  if (!hbox)
    return;
  auto checkmark = dynamic_cast<Gtk::Image*>(hbox->get_last_child());
  if (!checkmark)
    return;
  checkmark->set_visible(m_DropDown.get_selected_item() == list_item->get_item());
}


int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create("org.gtkmm.example");

  // Shows the window and returns when it is closed.
  return app->make_window_and_run<ExampleWindow>(argc, argv);
}

/*  
af_utf8 	Afrikaans 	af_ZA.UTF-8 	Afrikaans_South Africa.1252 	WINDOWS-1252
sq_utf8 	Albanian 	sq_AL.UTF-8 	Albanian_Albania.1250 	WINDOWS-1250
ar_utf8 	Arabic 	ar_SA.UTF-8 	Arabic_Saudi Arabia.1256 	WINDOWS-1256
eu_utf8 	Basque 	eu_ES.UTF-8 	Basque_Spain.1252 	WINDOWS-1252
be_utf8 	Belarusian 	be_BY.UTF-8 	Belarusian_Belarus.1251 	WINDOWS-1251
bs_utf8 	Bosnian 	bs_BA.UTF-8 	Bosnian (Latin) 	WINDOWS-1250
bg_utf8 	Bulgarian 	bg_BG.UTF-8 	Bulgarian_Bulgaria.1251 	WINDOWS-1251
ca_utf8 	Catalan 	ca_ES.UTF-8 	Catalan_Spain.1252 	WINDOWS-1252
hr_utf8 	Croatian 	hr_HR.UTF-8 	Croatian_Croatia.1250 	WINDOWS-1250
zh_cn_utf8 	Chinese (Simplified) 	zh_CN.UTF-8 	Chinese_China.936 	CP936
zh_tw_utf8 	Chinese (Traditional) 	zh_TW.UTF-8 	Chinese_Taiwan.950 	CP950
cs_utf8 	Czech 	cs_CZ.UTF-8 	Czech_Czech Republic.1250 	WINDOWS-1250
da_utf8 	Danish 	da_DK.UTF-8 	Danish_Denmark.1252 	WINDOWS-1252
nl_utf8 	Dutch 	nl_NL.UTF-8 	Dutch_Netherlands.1252 	WINDOWS-1252
en_utf8 	English 	en.UTF-8 	English_Australia.1252 	-empty string-
en_us_utf8 	English (US) 	-parent en_utf8 used- 	-parent en_utf8 used- 	-parent en_utf8 used-
et_utf8 	Estonian 	et_EE.UTF-8 	Estonian_Estonia.1257 	WINDOWS-1257
fa_utf8 	Farsi 	fa_IR.UTF-8 	Farsi_Iran.1256 	WINDOWS-1256
fil_utf8 	Filipino 	fil_PH.UTF-8 	Filipino_Philippines.1252 	WINDOWS-1252
fi_utf8 	Finnish 	fi_FI.UTF-8 	Finnish_Finland.1252 	WINDOWS-1252
fr_utf8 	French 	fr_FR.UTF-8 or
fr_CH.UTF-8 or
fr_BE.UTF-8 	French_France.1252 	WINDOWS-1252
fr_ca_utf8 	French (Canada) 	fr_CA.UTF-8 	French_Canada.1252 	-parent fr_utf8 used-
ga_utf8 	Gaelic 	ga.UTF-8 	Gaelic; Scottish Gaelic 	WINDOWS-1252
gl_utf8 	Gallego 	gl_ES.UTF-8 	Galician_Spain.1252 	WINDOWS-1252
ka_utf8 	Georgian 	ka_GE.UTF-8 	Georgian_Georgia.65001 	-empty string-
de_utf8 	German 	de_DE.UTF-8 	German_Germany.1252 	WINDOWS-1252
de_du_utf8 	German (Personal) 	de_DE.UTF-8 	-parent de_utf8 used- 	-parent de_utf8 used-
el_utf8 	Greek 	el_GR.UTF-8 	Greek_Greece.1253 	WINDOWS-1253
gu_utf8 	Gujarati 	gu.UTF-8 	Gujarati_India.0 	
he_utf8 	Hebrew 	he_IL.utf8 	Hebrew_Israel.1255 	WINDOWS-1255
hi_utf8 	Hindi 	hi_IN.UTF-8 	Hindi.65001 	-empty string-
hu_utf8 	Hungarian 	hu.UTF-8 	Hungarian_Hungary.1250 	WINDOWS-1250
is_utf8 	Icelandic 	is_IS.UTF-8 	Icelandic_Iceland.1252 	WINDOWS-1252
id_utf8 	Indonesian 	id_ID.UTF-8 	Indonesian_indonesia.1252 	WINDOWS-1252
it_utf8 	Italian 	it_IT.UTF-8 	Italian_Italy.1252 	WINDOWS-1252
ja_utf8 	Japanese 	ja_JP.UTF-8 	Japanese_Japan.932 	CP932
kn_utf8 	Kannada 	kn_IN.UTF-8 	Kannada.65001 	-empty string-
km_utf8 	Khmer 	km_KH.UTF-8 	Khmer.65001 	-empty string-
ko_utf8 	Korean 	ko_KR.UTF-8 	Korean_Korea.949 	EUC-KR
lo_utf8 	Lao 	lo_LA.UTF-8 	Lao_Laos.UTF-8 	WINDOWS-1257
lt_utf8 	Lithuanian 	lt_LT.UTF-8 	Lithuanian_Lithuania.1257 	WINDOWS-1257
lv_utf8 	Latvian 	lat.UTF-8 	Latvian_Latvia.1257 	WINDOWS-1257
ml_utf8 	Malayalam 	ml_IN.UTF-8 	Malayalam_India.x-iscii-ma 	x-iscii-ma
ms_utf8 	Malaysian 	ms_MY.UTF-8 	Malay_malaysia.1252 	WINDOWS-1252
mi_tn_utf8 	Maori (Ngai Tahu) 	mi_NZ.UTF-8 	Maori.1252 	WINDOWS-1252
mi_wwow_utf8 	Maori (Waikoto Uni) 	mi_NZ.UTF-8 	Maori.1252 	WINDOWS-1252
mn_utf8 	Mongolian 	mn.UTF-8 	Cyrillic_Mongolian.1251 	
no_utf8 	Norwegian 	no_NO.UTF-8 	Norwegian_Norway.1252 	WINDOWS-1252
no_gr_utf8 	Norwegian (Primary) 	no_NO.UTF-8 	-parent no_utf8 used- 	-parent no_utf8 used-
nn_utf8 	Nynorsk 	nn_NO.UTF-8 	Norwegian-Nynorsk_Norway.1252 	WINDOWS-1252
pl_utf8 	Polish 	pl.UTF-8 	Polish_Poland.1250 	WINDOWS-1250
pt_utf8 	Portuguese 	pt_PT.UTF-8 	Portuguese_Portugal.1252 	WINDOWS-1252
pt_br_utf8 	Portuguese (Brazil) 	pt_BR.UTF-8 	Portuguese_Brazil.1252 	WINDOWS-1252
ro_utf8 	Romanian 	ro_RO.UTF-8 	Romanian_Romania.1250 	WINDOWS-1250
ru_utf8 	Russian 	ru_RU.UTF-8 	Russian_Russia.1251 	WINDOWS-1251
sm_utf8 	Samoan 	mi_NZ.UTF-8 	Maori.1252 	WINDOWS-1252
sr_utf8 	Serbian 	sr_CS.UTF-8 	Bosnian(Cyrillic), Serbian (Cyrillic) 	WINDOWS-1251
sk_utf8 	Slovak 	sk_SK.UTF-8 	Slovak_Slovakia.1250 	WINDOWS-1250
sl_utf8 	Slovenian 	sl_SI.UTF-8 	Slovenian_Slovenia.1250 	WINDOWS-1250
so_utf8 	Somali 	so_SO.UTF-8 	not found! 	not found!
es_utf8 	Spanish (International) 	es_ES.UTF-8 	Spanish_Spain.1252 	WINDOWS-1252
sv_utf8 	Swedish 	sv_SE.UTF-8 	Swedish_Sweden.1252 	WINDOWS-1252
tl_utf8 	Tagalog 	tl.UTF-8 	not found! 	not found!
ta_utf8 	Tamil 	ta_IN.UTF-8 	English_Australia.1252 	
th_utf8 	Thai 	th_TH.UTF-8 	Thai_Thailand.874 	WINDOWS-874
to_utf8 	Tongan 	mi_NZ.UTF-8' 	Maori.1252 	WINDOWS-1252
tr_utf8 	Turkish 	tr_TR.UTF-8 	Turkish_Turkey.1254 	WINDOWS-1254
uk_utf8 	Ukrainian 	uk_UA.UTF-8 	Ukrainian_Ukraine.1251 	WINDOWS-1251
vi_utf8 	Vietnamese 	vi_VN.UTF-8 	Vietnamese_Viet Nam.1258 	WINDOWS-1258

C
	
US-ASCII
	
C , POSIX
POSIX
	
US-ASCII
	
C, POSIX
af_ZA.UTF-8
	
UTF-8
	
Afrikaans, South Africa
ar_AE.UTF-8
	
UTF-8
	
Arabic, United Arab Emirates
ar_BH.UTF-8
	
UTF-8
	
Arabic, Bahrain
ar_DZ.UTF-8
	
UTF-8
	
Arabic, Algeria
ar_EG.UTF-8
	
UTF-8
	
Arabic, Egypt
ar_IQ.UTF-8
	
UTF-8
	
Arabic, Iraq
ar_JO.UTF-8
	
UTF-8
	
Arabic, Jordan
ar_KW.UTF-8
	
UTF-8
	
Arabic, Kuwait
ar_LY.UTF-8
	
UTF-8
	
Arabic, Libya
ar_MA.UTF-8
	
UTF-8
	
Arabic, Morocco
ar_OM.UTF-8
	
UTF-8
	
Arabic, Oman
ar_QA.UTF-8
	
UTF-8
	
Arabic, Qatar
ar_SA.UTF-8
	
UTF-8
	
Arabic, Saudi Arabia
ar_TN.UTF-8
	
UTF-8
	
Arabic, Tunisia
ar_YE.UTF-8
	
UTF-8
	
Arabic, Yemen
as_IN.UTF-8
	
UTF-8
	
Assamese, India
az_AZ.UTF-8
	
UTF-8
	
Azerbaijani, Azerbaijan
be_BY.UTF-8
	
UTF-8
	
Belarusian, Belarus
bg_BG.UTF-8
	
UTF-8
	
Bulgarian, Bulgaria
bn_IN.UTF-8
	
UTF-8
	
Bengali, India
bs_BA.UTF-8
	
UTF-8
	
Bosnian, Bosnia and Herzegovina
ca_ES.UTF-8
	
UTF-8
	
Catalan, Spain
cs_CZ.UTF-8
	
UTF-8
	
Czech, Czech Republic
da_DK.UTF-8
	
UTF-8
	
Danish, Denmark
de_AT.UTF-8
	
UTF-8
	
German, Austria
de_BE.UTF-8
	
UTF-8
	
German, Belgium
de_CH.UTF-8
	
UTF-8
	
German, Switzerland
de_DE.UTF-8
	
UTF-8
	
German, Germany
de_LI.UTF-8
	
UTF-8
	
German, Liechtenstein
de_LU.UTF-8
	
UTF-8
	
German, Luxembourg
el_CY.UTF-8
	
UTF-8
	
Greek, Cyprus
el_GR.UTF-8
	
UTF-8
	
Greek, Greece
en_AU.UTF-8
	
UTF-8
	
English, Australia
en_BW.UTF-8
	
UTF-8
	
English, Botswana
en_CA.UTF-8
	
UTF-8
	
English, Canada
en_GB.UTF-8
	
UTF-8
	
English, United Kingdom
en_HK.UTF-8
	
UTF-8
	
English, Hong Kong SAR China
en_IE.UTF-8
	
UTF-8
	
English, Ireland
en_IN.UTF-8
	
UTF-8
	
English, India
en_MT.UTF-8
	
UTF-8
	
English, Malta
en_NZ.UTF-8
	
UTF-8
	
English, New Zealand
en_PH.UTF-8
	
UTF-8
	
English, Philippines
en_SG.UTF-8
	
UTF-8
	
English, Singapore
en_US.UTF-8
	
UTF-8
	
English, U.S.A.
en_ZW.UTF-8
	
UTF-8
	
English, Zimbabwe
es_AR.UTF-8
	
UTF-8
	
Spanish, Argentina
es_BO.UTF-8
	
UTF-8
	
Spanish, Bolivia
es_CL.UTF-8
	
UTF-8
	
Spanish, Chile
es_CO.UTF-8
	
UTF-8
	
Spanish, Colombia
es_CR.UTF-8
	
UTF-8
	
Spanish, Costa Rica
es_DO.UTF-8
	
UTF-8
	
Spanish, Dominican Republic
es_EC.UTF-8
	
UTF-8
	
Spanish, Ecuador
es_ES.UTF-8
	
UTF-8
	
Spanish, Spain
es_GT.UTF-8
	
UTF-8
	
Spanish, Guatemala
es_HN.UTF-8
	
UTF-8
	
Spanish, Honduras
es_MX.UTF-8
	
UTF-8
	
Spanish, Mexico
es_NI.UTF-8
	
UTF-8
	
Spanish, Nicaragua
es_PA.UTF-8
	
UTF-8
	
Spanish, Panama
es_PE.UTF-8
	
UTF-8
	
Spanish, Peru
es_PR.UTF-8
	
UTF-8
	
Spanish, Puerto Rico
es_PY.UTF-8
	
UTF-8
	
Spanish, Paraguay
es_SV.UTF-8
	
UTF-8
	
Spanish, El Salvador
es_US.UTF-8
	
UTF-8
	
Spanish, U.S.A.
es_UY.UTF-8
	
UTF-8
	
Spanish, Uruguay
es_VE.UTF-8
	
UTF-8
	
Spanish, Venezuela
et_EE.UTF-8
	
UTF-8
	
Estonian, Estonia
fi_FI.UTF-8
	
UTF-8
	
Finnish, Finland
fr_BE.UTF-8
	
UTF-8
	
French, Belgium
fr_CA.UTF-8
	
UTF-8
	
French, Canada
fr_CH.UTF-8
	
UTF-8
	
French, Switzerland
fr_FR.UTF-8
	
UTF-8
	
French, France
fr_LU.UTF-8
	
UTF-8
	
French, Luxembourg
gu_IN.UTF-8
	
UTF-8
	
Gujarati, India
he_IL.UTF-8
	
UTF-8
	
Hebrew, Israel
hi_IN.UTF-8
	
UTF-8
	
Hindi, India
hr_HR.UTF-8
	
UTF-8
	
Croatian, Croatia
hu_HU.UTF-8
	
UTF-8
	
Hungarian, Hungary
hy_AM.UTF-8
	
UTF-8
	
Armenian, Armenia
id_ID.UTF-8
	
UTF-8
	
Indonesian, Indonesia
is_IS.UTF-8
	
UTF-8
	
Icelandic, Iceland
it_CH.UTF-8
	
UTF-8
	
Italian, Switzerland
it_IT.UTF-8
	
UTF-8
	
Italian, Italy
ja_JP.UTF-8
	
UTF-8
	
Japanese, Japan
ka_GE.UTF-8
	
UTF-8
	
Georgian, Georgia
kk_KZ.UTF-8
	
UTF-8
	
Kazakh, Kazakhstan
kn_IN.UTF-8
	
UTF-8
	
Kannada, India
ko_KR.UTF-8
	
UTF-8
	
Korean, Korea
ks_IN.UTF-8
	
UTF-8
	
Kashmiri, India
ku_TR.UTF-8
	
UTF-8
	
Kurdish, Turkey
ku_TR.UTF-8@sorani
	
UTF-8
	
Kurdish (Sorani), Turkey
ky_KG.UTF-8
	
UTF-8
	
Kirghiz, Kyrgyzstan
lt_LT.UTF-8
	
UTF-8
	
Lithuanian, Lithuania
lv_LV.UTF-8
	
UTF-8
	
Latvian, Latvia
mk_MK.UTF-8
	
UTF-8
	
Macedonian, Macedonia
ml_IN.UTF-8
	
UTF-8
	
Malayalam, India
mr_IN.UTF-8
	
UTF-8
	
Marathi, India
ms_MY.UTF-8
	
UTF-8
	
Malay, Malaysia
mt_MT.UTF-8
	
UTF-8
	
Maltese, Malta
nb_NO.UTF-8
	
UTF-8
	
Bokmal, Norway
nl_BE.UTF-8
	
UTF-8
	
Dutch, Belgium
nl_NL.UTF-8
	
UTF-8
	
Dutch, Netherlands
nn_NO.UTF-8
	
UTF-8
	
Nynorsk, Norway
or_IN.UTF-8
	
UTF-8
	
Oriya, India
pa_IN.UTF-8
	
UTF-8
	
Punjabi, India
pl_PL.UTF-8
	
UTF-8
	
Polish, Poland
pt_BR.UTF-8
	
UTF-8
	
Portuguese, Brazil
pt_PT.UTF-8
	
UTF-8
	
Portuguese, Portugal
ro_RO.UTF-8
	
UTF-8
	
Romanian, Romania
ru_RU.UTF-8
	
UTF-8
	
Russian, Russia
ru_UA.UTF-8
	
UTF-8
	
Russian, Ukraine
sa_IN.UTF-8
	
UTF-8
	
Sanskrit, India
sk_SK.UTF-8
	
UTF-8
	
Slovak, Slovakia
sl_SI.UTF-8
	
UTF-8
	
Slovenian, Slovenia
sq_AL.UTF-8
	
UTF-8
	
Albanian, Albania
sr_ME.UTF-8
	
UTF-8
	
Serbian, Montenegro
sr_ME.UTF-8@latin
	
UTF-8
	
Serbian, Montenegro (Latin)
sr_RS.UTF-8
	
UTF-8
	
Serbian, Serbia
sr_RS.UTF-8@latin
	
UTF-8
	
Serbian, Serbia (Latin)
sv_SE.UTF-8
	
UTF-8
	
Swedish, Sweden
ta_IN.UTF-8
	
UTF-8
	
Tamil, India
te_IN.UTF-8
	
UTF-8
	
Telugu, India
th_TH.UTF-8
	
UTF-8
	
Thai, Thailand
tr_TR.UTF-8
	
UTF-8
	
Turkish, Turkey
uk_UA.UTF-8
	
UTF-8
	
Ukrainian, Ukraine
vi_VN.UTF-8
	
UTF-8
	
Vietnamese, Vietnam
zh_CN.UTF-8
	
UTF-8
	
Simplified Chinese, China
zh_HK.UTF-8
	
UTF-8
	
Traditional Chinese, Hong Kong SAR China
zh_SG.UTF-8
	
UTF-8
	
Chinese, Singapore
zh_TW.UTF-8
	
UTF-8
	
Traditional Chinese, Taiwan

Table A-2 Additional Locales
Locales
	
Code Set
	
Description
ar_EG.ISO8859-6
	
ISO8859-6
	
Arabic, Egypt
bg_BG.ISO8859-5
	
ISO8859-5
	
Bulgarian, Bulgaria
bs_BA.ISO8859-2
	
ISO8859-2
	
Bosnian, Bosnia and Herzegovina
ca_ES.ISO8859-1
	
ISO8859-1
	
Catalan, Spain
ca_ES.ISO8859-15
	
ISO8859-15
	
Catalan, Spain
cs_CZ.ISO8859-2
	
ISO8859-2
	
Czech, Czech Republic
CZ.UTF-8@euro
	
UTF-8
	
Czech, Czech Republic (Euro)
da_DK.ISO8859-1
	
ISO8859-1
	
Danish, Denmark
da_DK.ISO8859-15
	
ISO8859-15
	
Danish, Denmark
da_DK.ISO8859-15@euro
	
ISO8859-15
	
Danish, Denmark (Euro)
de_AT.ISO8859-1
	
ISO8859-1
	
German, Austria
de_AT.ISO8859-15
	
ISO8859-15
	
German, Austria
de_CH.ISO8859-1
	
ISO8859-1
	
German, Switzerland
de_DE.ISO8859-1
	
ISO8859-1
	
German, Germany
de_DE.ISO8859-15
	
ISO8859-15
	
German, Germany
el_GR.ISO8859-7
	
ISO8859-7
	
Greek, Greece
en_AU.ISO8859-1
	
ISO8859-1
	
English, Australia
en_CA.ISO8859-1
	
ISO8859-1
	
English, Canada
en_GB.ISO8859-1
	
ISO8859-1
	
English, United Kingdom
en_GB.ISO8859-15
	
ISO8859-15
	
English, United Kingdom
en_GB.ISO8859-15@euro
	
ISO8859-15
	
English, United Kingdom (Euro)
en_IE.ISO8859-1
	
ISO8859-1
	
English, Ireland
en_IE.ISO8859-15
	
ISO8859-15
	
English, Ireland
en_NZ.ISO8859-1
	
ISO8859-1
	
English, New Zealand
en_US.ISO8859-1
	
ISO8859-1
	
English, U.S.A.
en_US.ISO8859-15
	
ISO8859-15
	
English, U.S.A.
en_US.ISO8859-15@euro
	
ISO8859-15
	
English, U.S.A. (Euro)
es_AR.ISO8859-1
	
ISO8859-1
	
Spanish, Argentina
es_BO.ISO8859-1
	
ISO8859-1
	
Spanish, Bolivia
es_CL.ISO8859-1
	
ISO8859-1
	
Spanish, Chile
es_CO.ISO8859-1
	
ISO8859-1
	
Spanish, Colombia
es_CR.ISO8859-1
	
ISO8859-1
	
Spanish, Costa Rica
es_EC.ISO8859-1
	
ISO8859-1
	
Spanish, Ecuador
es_ES.ISO8859-1
	
ISO8859-1
	
Spanish, Spain
es_ES.ISO8859-15
	
ISO8859-15
	
Spanish, Spain
es_GT.ISO8859-1
	
ISO8859-1
	
Spanish, Guatemala
es_MX.ISO8859-1
	
ISO8859-1
	
Spanish, Mexico
es_NI.ISO8859-1
	
ISO8859-1
	
Spanish, Nicaragua
es_PA.ISO8859-1
	
ISO8859-1
	
Spanish, Panama
es_PE.ISO8859-1
	
ISO8859-1
	
Spanish, Peru
es_PY.ISO8859-1
	
ISO8859-1
	
Spanish, Paraguay
es_SV.ISO8859-1
	
ISO8859-1
	
Spanish, El Salvador
es_UY.ISO8859-1
	
ISO8859-1
	
Spanish, Uruguay
es_VE.ISO8859-1
	
ISO8859-1
	
Spanish, Venezuela
et_EE.ISO8859-15
	
ISO8859-15
	
Estonian, Estonia
fi_FI.ISO8859-1
	
ISO8859-1
	
Finnish, Finland
fi_FI.ISO8859-15
	
ISO8859-15
	
Finnish, Finland
fr_BE.ISO8859-1
	
ISO8859-1
	
French, Belgium
fr_BE.ISO8859-15
	
ISO8859-15
	
French, Belgium
fr_CA.ISO8859-1
	
ISO8859-1
	
French, Canada
fr_CH.ISO8859-1
	
ISO8859-1
	
French, Switzerland
fr_FR.ISO8859-1
	
ISO8859-1
	
French, France
fr_FR.ISO8859-15
	
ISO8859-15
	
French, France
he_IL.ISO8859-8
	
ISO8859-8
	
Hebrew, Israel
hr_HR.ISO8859-2
	
ISO8859-2
	
Croatian, Croatia
hu_HU.ISO8859-2
	
ISO8859-2
	
Hungarian, Hungary
is_IS.ISO8859-1
	
ISO8859-1
	
Icelandic, Iceland
it_IT.ISO8859-1
	
ISO8859-1
	
Italian, Italy
it_IT.ISO8859-15
	
ISO8859-15
	
Italian, Italy
ja_JP.PCK
	
PCK
	
Japanese, Japan (PC Kanji code, aka. Shift-JIS)
ja_JP.eucJP
	
EUC-JP
	
Japanese EUC environment. Compliant to UI-OSF Japanese Environment Implementation Agreement Version 1.1
ko_KR.EUC
	
KS X 1001
	
Korean, Korea
ko_KR.EUC@dict
	
KS X 1001
	
Korean, Korea (dict)
ko_KR.UTF-8@dict
	
UTF-8
	
Korean, Korea (dict)
lt_LT.ISO8859-13
	
ISO8859-13
	
Lithuanian, Lithuania
lv_LV.ISO8859-13
	
ISO8859-13
	
Latvian, Latvia
mk_MK.ISO8859-5
	
ISO8859-5
	
Macedonian, Macedonia
nb_NO.ISO8859-1
	
ISO8859-1
	
Norwegian Bokmal, Norway
nl_BE.ISO8859-1
	
ISO8859-1
	
Dutch, Belgium
nl_BE.ISO8859-15
	
ISO8859-15
	
Dutch, Belgium
nl_NL.ISO8859-1
	
ISO8859-1
	
Dutch, Netherlands
nl_NL.ISO8859-15
	
ISO8859-15
	
Dutch, Netherlands
nn_NO.ISO8859-1
	
ISO8859-1
	
Norwegian Nynorsk, Norway
pl_PL.ISO8859-2
	
ISO8859-2
	
Polish, Poland
pt_BR.ISO8859-1
	
ISO8859-1
	
Portuguese, Brazil
pt_PT.ISO8859-1
	
ISO8859-1
	
Portuguese, Portugal
pt_PT.ISO8859-15
	
ISO8859-15
	
Portuguese, Portugal
ro_RO.ISO8859-2
	
ISO8859-2
	
Romanian, Romania
ru_RU.ANSI1251
	
ANSI1251
	
Russian, Russia
ru_RU.ISO8859-5
	
ISO8859-5
	
Russian, Russia
ru_RU.KOI8-R
	
KOI8-R
	
Russian, Russia
sk_SK.ISO8859-2
	
ISO8859-2
	
Slovak, Slovakia
sl_SI.ISO8859-2
	
ISO8859-2
	
Slovenian, Slovenia
sq_AL.ISO8859-2
	
ISO8859-2
	
Albanian, Albania
sr_ME.ISO8859-5
	
ISO8859-5
	
Serbian, Montenegro
sv_SE.ISO8859-1
	
ISO8859-1
	
Swedish, Sweden
sv_SE.ISO8859-15
	
ISO8859-15
	
Swedish, Sweden
sv_SE.ISO8859-15@euro
	
ISO8859-15
	
Swedish, Sweden (Euro)
sv_SE.UTF-8@euro
	
UTF-8
	
Swedish, Sweden (Euro)
th_TH.TIS620
	
TIS-620
	
Thai, Thailand
tr_TR.ISO8859-9
	
ISO8859-9
	
Turkish, Turkey
zh_CN.EUC
	
GB2312
	
Simplified Chinese, China
zh_CN.EUC@pinyin
	
GB2312
	
Simplified Chinese, China (pinyin)
zh_CN.EUC@radical
	
GB2312
	
Simplified Chinese, China (radical)
zh_CN.EUC@stroke
	
GB2312
	
Simplified Chinese, China (stroke)
zh_CN.GB18030
	
GB18030
	
Simplified Chinese, China
zh_CN.GB18030@pinyin
	
GB18030
	
Simplified Chinese, China (pinyin)
zh_CN.GB18030@radical
	
GB18030
	
Simplified Chinese, China (radical)
zh_CN.GB18030@stroke
	
GB18030
	
Simplified Chinese, China (stroke)
zh_CN.GBK
	
GBK
	
Simplified Chinese, China
zh_CN.GBK@pinyin
	
GBK
	
Simplified Chinese, China (pinyin)
zh_CN.GBK@radical
	
GBK
	
Simplified Chinese, China (radical)
zh_CN.GBK@stroke
	
GBK
	
Simplified Chinese, China (stroke)
zh_CN.UTF-8@pinyin
	
UTF-8
	
Simplified Chinese, China (pinyin)
zh_CN.UTF-8@radical
	
UTF-8
	
Simplified Chinese, China (radical)
zh_CN.UTF-8@stroke
	
UTF-8
	
Simplified Chinese, China (stroke)
zh_HK.BIG5HK
	
BIG5-HKSCS
	
Traditional Chinese, Hong Kong SAR China
zh_HK.BIG5HK@radical
	
BIG5-HKSCS
	
Traditional Chinese, Hong Kong SAR China (radical)
zh_HK.BIG5HK@stroke
	
BIG5-HKSCS
	
Traditional Chinese, Hong Kong SAR China (stroke)
zh_HK.UTF-8@radical
	
UTF-8
	
Traditional Chinese, Hong Kong SAR China (radical)
zh_HK.UTF-8@stroke
	
UTF-8
	
Traditional Chinese, Hong Kong SAR China (stroke)
zh_TW.BIG5
	
BIG5
	
Traditional Chinese, Taiwan
zh_TW.BIG5@pinyin
	
BIG5
	
Traditional Chinese, Taiwan (pinyin)
zh_TW.BIG5@radical
	
BIG5
	
Traditional Chinese, Taiwan (radical)
zh_TW.BIG5@stroke
	
BIG5
	
Traditional Chinese, Taiwan (stroke)
zh_TW.BIG5@zhuyin
	
BIG5
	
Traditional Chinese, Taiwan (zhuyin)
zh_TW.EUC
	
CNS11643-1992
	
Traditional Chinese, Taiwan
zh_TW.EUC@pinyin
	
CNS11643
	
Traditional Chinese, Taiwan (pinyin)
zh_TW.EUC@radical
	
CNS11643
	
Traditional Chinese, Taiwan (radical)
zh_TW.EUC@stroke
	
CNS11643
	
Traditional Chinese, Taiwan (stroke)
zh_TW.EUC@zhuyin
	
CNS11643
	
Traditional Chinese, Taiwan (zhuyin)
zh_TW.UTF-8@pinyin
	
UTF-8
	
Traditional Chinese, Taiwan (pinyin)
zh_TW.UTF-8@radical
	
UTF-8
	
Traditional Chinese, Taiwan (radical)
zh_TW.UTF-8@stroke
	
UTF-8
	
Traditional Chinese, Taiwan (stroke)
zh_TW.UTF-8@zhuyin
	
UTF-8
	
Traditional Chinese, Taiwan (zhuyin)

var LANGUAGE_BY_LOCALE = {
    af_NA: "Afrikaans (Namibia)",
    af_ZA: "Afrikaans (South Africa)",
    af: "Afrikaans",
    ak_GH: "Akan (Ghana)",
    ak: "Akan",
    sq_AL: "Albanian (Albania)",
    sq: "Albanian",
    am_ET: "Amharic (Ethiopia)",
    am: "Amharic",
    ar_DZ: "Arabic (Algeria)",
    ar_BH: "Arabic (Bahrain)",
    ar_EG: "Arabic (Egypt)",
    ar_IQ: "Arabic (Iraq)",
    ar_JO: "Arabic (Jordan)",
    ar_KW: "Arabic (Kuwait)",
    ar_LB: "Arabic (Lebanon)",
    ar_LY: "Arabic (Libya)",
    ar_MA: "Arabic (Morocco)",
    ar_OM: "Arabic (Oman)",
    ar_QA: "Arabic (Qatar)",
    ar_SA: "Arabic (Saudi Arabia)",
    ar_SD: "Arabic (Sudan)",
    ar_SY: "Arabic (Syria)",
    ar_TN: "Arabic (Tunisia)",
    ar_AE: "Arabic (United Arab Emirates)",
    ar_YE: "Arabic (Yemen)",
    ar: "Arabic",
    hy_AM: "Armenian (Armenia)",
    hy: "Armenian",
    as_IN: "Assamese (India)",
    as: "Assamese",
    asa_TZ: "Asu (Tanzania)",
    asa: "Asu",
    az_Cyrl: "Azerbaijani (Cyrillic)",
    az_Cyrl_AZ: "Azerbaijani (Cyrillic, Azerbaijan)",
    az_Latn: "Azerbaijani (Latin)",
    az_Latn_AZ: "Azerbaijani (Latin, Azerbaijan)",
    az: "Azerbaijani",
    bm_ML: "Bambara (Mali)",
    bm: "Bambara",
    eu_ES: "Basque (Spain)",
    eu: "Basque",
    be_BY: "Belarusian (Belarus)",
    be: "Belarusian",
    bem_ZM: "Bemba (Zambia)",
    bem: "Bemba",
    bez_TZ: "Bena (Tanzania)",
    bez: "Bena",
    bn_BD: "Bengali (Bangladesh)",
    bn_IN: "Bengali (India)",
    bn: "Bengali",
    bs_BA: "Bosnian (Bosnia and Herzegovina)",
    bs: "Bosnian",
    bg_BG: "Bulgarian (Bulgaria)",
    bg: "Bulgarian",
    my_MM: "Burmese (Myanmar [Burma])",
    my: "Burmese",
    yue_Hant_HK: "Cantonese (Traditional, Hong Kong SAR China)",
    ca_ES: "Catalan (Spain)",
    ca: "Catalan",
    tzm_Latn: "Central Morocco Tamazight (Latin)",
    tzm_Latn_MA: "Central Morocco Tamazight (Latin, Morocco)",
    tzm: "Central Morocco Tamazight",
    chr_US: "Cherokee (United States)",
    chr: "Cherokee",
    cgg_UG: "Chiga (Uganda)",
    cgg: "Chiga",
    zh_Hans: "Chinese (Simplified Han)",
    zh_Hans_CN: "Chinese (Simplified Han, China)",
    zh_Hans_HK: "Chinese (Simplified Han, Hong Kong SAR China)",
    zh_Hans_MO: "Chinese (Simplified Han, Macau SAR China)",
    zh_Hans_SG: "Chinese (Simplified Han, Singapore)",
    zh_Hant: "Chinese (Traditional Han)",
    zh_Hant_HK: "Chinese (Traditional Han, Hong Kong SAR China)",
    zh_Hant_MO: "Chinese (Traditional Han, Macau SAR China)",
    zh_Hant_TW: "Chinese (Traditional Han, Taiwan)",
    zh: "Chinese",
    kw_GB: "Cornish (United Kingdom)",
    kw: "Cornish",
    hr_HR: "Croatian (Croatia)",
    hr: "Croatian",
    cs_CZ: "Czech (Czech Republic)",
    cs: "Czech",
    da_DK: "Danish (Denmark)",
    da: "Danish",
    nl_BE: "Dutch (Belgium)",
    nl_NL: "Dutch (Netherlands)",
    nl: "Dutch",
    ebu_KE: "Embu (Kenya)",
    ebu: "Embu",
    en_AS: "English (American Samoa)",
    en_AU: "English (Australia)",
    en_BE: "English (Belgium)",
    en_BZ: "English (Belize)",
    en_BW: "English (Botswana)",
    en_CA: "English (Canada)",
    en_GU: "English (Guam)",
    en_HK: "English (Hong Kong SAR China)",
    en_IN: "English (India)",
    en_IE: "English (Ireland)",
    en_IL: "English (Israel)",
    en_JM: "English (Jamaica)",
    en_MT: "English (Malta)",
    en_MH: "English (Marshall Islands)",
    en_MU: "English (Mauritius)",
    en_NA: "English (Namibia)",
    en_NZ: "English (New Zealand)",
    en_MP: "English (Northern Mariana Islands)",
    en_PK: "English (Pakistan)",
    en_PH: "English (Philippines)",
    en_SG: "English (Singapore)",
    en_ZA: "English (South Africa)",
    en_TT: "English (Trinidad and Tobago)",
    en_UM: "English (U.S. Minor Outlying Islands)",
    en_VI: "English (U.S. Virgin Islands)",
    en_GB: "English (United Kingdom)",
    en_US: "English (United States)",
    en_ZW: "English (Zimbabwe)",
    en: "English",
    eo: "Esperanto",
    et_EE: "Estonian (Estonia)",
    et: "Estonian",
    ee_GH: "Ewe (Ghana)",
    ee_TG: "Ewe (Togo)",
    ee: "Ewe",
    fo_FO: "Faroese (Faroe Islands)",
    fo: "Faroese",
    fil_PH: "Filipino (Philippines)",
    fil: "Filipino",
    fi_FI: "Finnish (Finland)",
    fi: "Finnish",
    fr_BE: "French (Belgium)",
    fr_BJ: "French (Benin)",
    fr_BF: "French (Burkina Faso)",
    fr_BI: "French (Burundi)",
    fr_CM: "French (Cameroon)",
    fr_CA: "French (Canada)",
    fr_CF: "French (Central African Republic)",
    fr_TD: "French (Chad)",
    fr_KM: "French (Comoros)",
    fr_CG: "French (Congo - Brazzaville)",
    fr_CD: "French (Congo - Kinshasa)",
    fr_CI: "French (Côte d’Ivoire)",
    fr_DJ: "French (Djibouti)",
    fr_GQ: "French (Equatorial Guinea)",
    fr_FR: "French (France)",
    fr_GA: "French (Gabon)",
    fr_GP: "French (Guadeloupe)",
    fr_GN: "French (Guinea)",
    fr_LU: "French (Luxembourg)",
    fr_MG: "French (Madagascar)",
    fr_ML: "French (Mali)",
    fr_MQ: "French (Martinique)",
    fr_MC: "French (Monaco)",
    fr_NE: "French (Niger)",
    fr_RW: "French (Rwanda)",
    fr_RE: "French (Réunion)",
    fr_BL: "French (Saint Barthélemy)",
    fr_MF: "French (Saint Martin)",
    fr_SN: "French (Senegal)",
    fr_CH: "French (Switzerland)",
    fr_TG: "French (Togo)",
    fr: "French",
    ff_SN: "Fulah (Senegal)",
    ff: "Fulah",
    gl_ES: "Galician (Spain)",
    gl: "Galician",
    lg_UG: "Ganda (Uganda)",
    lg: "Ganda",
    ka_GE: "Georgian (Georgia)",
    ka: "Georgian",
    de_AT: "German (Austria)",
    de_BE: "German (Belgium)",
    de_DE: "German (Germany)",
    de_LI: "German (Liechtenstein)",
    de_LU: "German (Luxembourg)",
    de_CH: "German (Switzerland)",
    de: "German",
    el_CY: "Greek (Cyprus)",
    el_GR: "Greek (Greece)",
    el: "Greek",
    gu_IN: "Gujarati (India)",
    gu: "Gujarati",
    guz_KE: "Gusii (Kenya)",
    guz: "Gusii",
    ha_Latn: "Hausa (Latin)",
    ha_Latn_GH: "Hausa (Latin, Ghana)",
    ha_Latn_NE: "Hausa (Latin, Niger)",
    ha_Latn_NG: "Hausa (Latin, Nigeria)",
    ha: "Hausa",
    haw_US: "Hawaiian (United States)",
    haw: "Hawaiian",
    he_IL: "Hebrew (Israel)",
    he: "Hebrew",
    hi_IN: "Hindi (India)",
    hi: "Hindi",
    hu_HU: "Hungarian (Hungary)",
    hu: "Hungarian",
    is_IS: "Icelandic (Iceland)",
    is: "Icelandic",
    ig_NG: "Igbo (Nigeria)",
    ig: "Igbo",
    id_ID: "Indonesian (Indonesia)",
    id: "Indonesian",
    ga_IE: "Irish (Ireland)",
    ga: "Irish",
    it_IT: "Italian (Italy)",
    it_CH: "Italian (Switzerland)",
    it: "Italian",
    ja_JP: "Japanese (Japan)",
    ja: "Japanese",
    kea_CV: "Kabuverdianu (Cape Verde)",
    kea: "Kabuverdianu",
    kab_DZ: "Kabyle (Algeria)",
    kab: "Kabyle",
    kl_GL: "Kalaallisut (Greenland)",
    kl: "Kalaallisut",
    kln_KE: "Kalenjin (Kenya)",
    kln: "Kalenjin",
    kam_KE: "Kamba (Kenya)",
    kam: "Kamba",
    kn_IN: "Kannada (India)",
    kn: "Kannada",
    kk_Cyrl: "Kazakh (Cyrillic)",
    kk_Cyrl_KZ: "Kazakh (Cyrillic, Kazakhstan)",
    kk: "Kazakh",
    km_KH: "Khmer (Cambodia)",
    km: "Khmer",
    ki_KE: "Kikuyu (Kenya)",
    ki: "Kikuyu",
    rw_RW: "Kinyarwanda (Rwanda)",
    rw: "Kinyarwanda",
    kok_IN: "Konkani (India)",
    kok: "Konkani",
    ko_KR: "Korean (South Korea)",
    ko: "Korean",
    khq_ML: "Koyra Chiini (Mali)",
    khq: "Koyra Chiini",
    ses_ML: "Koyraboro Senni (Mali)",
    ses: "Koyraboro Senni",
    lag_TZ: "Langi (Tanzania)",
    lag: "Langi",
    lv_LV: "Latvian (Latvia)",
    lv: "Latvian",
    lt_LT: "Lithuanian (Lithuania)",
    lt: "Lithuanian",
    luo_KE: "Luo (Kenya)",
    luo: "Luo",
    luy_KE: "Luyia (Kenya)",
    luy: "Luyia",
    mk_MK: "Macedonian (Macedonia)",
    mk: "Macedonian",
    jmc_TZ: "Machame (Tanzania)",
    jmc: "Machame",
    kde_TZ: "Makonde (Tanzania)",
    kde: "Makonde",
    mg_MG: "Malagasy (Madagascar)",
    mg: "Malagasy",
    ms_BN: "Malay (Brunei)",
    ms_MY: "Malay (Malaysia)",
    ms: "Malay",
    ml_IN: "Malayalam (India)",
    ml: "Malayalam",
    mt_MT: "Maltese (Malta)",
    mt: "Maltese",
    gv_GB: "Manx (United Kingdom)",
    gv: "Manx",
    mr_IN: "Marathi (India)",
    mr: "Marathi",
    mas_KE: "Masai (Kenya)",
    mas_TZ: "Masai (Tanzania)",
    mas: "Masai",
    mer_KE: "Meru (Kenya)",
    mer: "Meru",
    mfe_MU: "Morisyen (Mauritius)",
    mfe: "Morisyen",
    naq_NA: "Nama (Namibia)",
    naq: "Nama",
    ne_IN: "Nepali (India)",
    ne_NP: "Nepali (Nepal)",
    ne: "Nepali",
    nd_ZW: "North Ndebele (Zimbabwe)",
    nd: "North Ndebele",
    nb_NO: "Norwegian Bokmål (Norway)",
    nb: "Norwegian Bokmål",
    nn_NO: "Norwegian Nynorsk (Norway)",
    nn: "Norwegian Nynorsk",
    nyn_UG: "Nyankole (Uganda)",
    nyn: "Nyankole",
    or_IN: "Oriya (India)",
    or: "Oriya",
    om_ET: "Oromo (Ethiopia)",
    om_KE: "Oromo (Kenya)",
    om: "Oromo",
    ps_AF: "Pashto (Afghanistan)",
    ps: "Pashto",
    fa_AF: "Persian (Afghanistan)",
    fa_IR: "Persian (Iran)",
    fa: "Persian",
    pl_PL: "Polish (Poland)",
    pl: "Polish",
    pt_BR: "Portuguese (Brazil)",
    pt_GW: "Portuguese (Guinea-Bissau)",
    pt_MZ: "Portuguese (Mozambique)",
    pt_PT: "Portuguese (Portugal)",
    pt: "Portuguese",
    pa_Arab: "Punjabi (Arabic)",
    pa_Arab_PK: "Punjabi (Arabic, Pakistan)",
    pa_Guru: "Punjabi (Gurmukhi)",
    pa_Guru_IN: "Punjabi (Gurmukhi, India)",
    pa: "Punjabi",
    ro_MD: "Romanian (Moldova)",
    ro_RO: "Romanian (Romania)",
    ro: "Romanian",
    rm_CH: "Romansh (Switzerland)",
    rm: "Romansh",
    rof_TZ: "Rombo (Tanzania)",
    rof: "Rombo",
    ru_MD: "Russian (Moldova)",
    ru_RU: "Russian (Russia)",
    ru_UA: "Russian (Ukraine)",
    ru: "Russian",
    rwk_TZ: "Rwa (Tanzania)",
    rwk: "Rwa",
    saq_KE: "Samburu (Kenya)",
    saq: "Samburu",
    sg_CF: "Sango (Central African Republic)",
    sg: "Sango",
    seh_MZ: "Sena (Mozambique)",
    seh: "Sena",
    sr_Cyrl: "Serbian (Cyrillic)",
    sr_Cyrl_BA: "Serbian (Cyrillic, Bosnia and Herzegovina)",
    sr_Cyrl_ME: "Serbian (Cyrillic, Montenegro)",
    sr_Cyrl_RS: "Serbian (Cyrillic, Serbia)",
    sr_Latn: "Serbian (Latin)",
    sr_Latn_BA: "Serbian (Latin, Bosnia and Herzegovina)",
    sr_Latn_ME: "Serbian (Latin, Montenegro)",
    sr_Latn_RS: "Serbian (Latin, Serbia)",
    sr: "Serbian",
    sn_ZW: "Shona (Zimbabwe)",
    sn: "Shona",
    ii_CN: "Sichuan Yi (China)",
    ii: "Sichuan Yi",
    si_LK: "Sinhala (Sri Lanka)",
    si: "Sinhala",
    sk_SK: "Slovak (Slovakia)",
    sk: "Slovak",
    sl_SI: "Slovenian (Slovenia)",
    sl: "Slovenian",
    xog_UG: "Soga (Uganda)",
    xog: "Soga",
    so_DJ: "Somali (Djibouti)",
    so_ET: "Somali (Ethiopia)",
    so_KE: "Somali (Kenya)",
    so_SO: "Somali (Somalia)",
    so: "Somali",
    es_AR: "Spanish (Argentina)",
    es_BO: "Spanish (Bolivia)",
    es_CL: "Spanish (Chile)",
    es_CO: "Spanish (Colombia)",
    es_CR: "Spanish (Costa Rica)",
    es_DO: "Spanish (Dominican Republic)",
    es_EC: "Spanish (Ecuador)",
    es_SV: "Spanish (El Salvador)",
    es_GQ: "Spanish (Equatorial Guinea)",
    es_GT: "Spanish (Guatemala)",
    es_HN: "Spanish (Honduras)",
    es_419: "Spanish (Latin America)",
    es_MX: "Spanish (Mexico)",
    es_NI: "Spanish (Nicaragua)",
    es_PA: "Spanish (Panama)",
    es_PY: "Spanish (Paraguay)",
    es_PE: "Spanish (Peru)",
    es_PR: "Spanish (Puerto Rico)",
    es_ES: "Spanish (Spain)",
    es_US: "Spanish (United States)",
    es_UY: "Spanish (Uruguay)",
    es_VE: "Spanish (Venezuela)",
    es: "Spanish",
    sw_KE: "Swahili (Kenya)",
    sw_TZ: "Swahili (Tanzania)",
    sw: "Swahili",
    sv_FI: "Swedish (Finland)",
    sv_SE: "Swedish (Sweden)",
    sv: "Swedish",
    gsw_CH: "Swiss German (Switzerland)",
    gsw: "Swiss German",
    shi_Latn: "Tachelhit (Latin)",
    shi_Latn_MA: "Tachelhit (Latin, Morocco)",
    shi_Tfng: "Tachelhit (Tifinagh)",
    shi_Tfng_MA: "Tachelhit (Tifinagh, Morocco)",
    shi: "Tachelhit",
    dav_KE: "Taita (Kenya)",
    dav: "Taita",
    ta_IN: "Tamil (India)",
    ta_LK: "Tamil (Sri Lanka)",
    ta: "Tamil",
    te_IN: "Telugu (India)",
    te: "Telugu",
    teo_KE: "Teso (Kenya)",
    teo_UG: "Teso (Uganda)",
    teo: "Teso",
    th_TH: "Thai (Thailand)",
    th: "Thai",
    bo_CN: "Tibetan (China)",
    bo_IN: "Tibetan (India)",
    bo: "Tibetan",
    ti_ER: "Tigrinya (Eritrea)",
    ti_ET: "Tigrinya (Ethiopia)",
    ti: "Tigrinya",
    to_TO: "Tonga (Tonga)",
    to: "Tonga",
    tr_TR: "Turkish (Turkey)",
    tr: "Turkish",
    uk_UA: "Ukrainian (Ukraine)",
    uk: "Ukrainian",
    ur_IN: "Urdu (India)",
    ur_PK: "Urdu (Pakistan)",
    ur: "Urdu",
    uz_Arab: "Uzbek (Arabic)",
    uz_Arab_AF: "Uzbek (Arabic, Afghanistan)",
    uz_Cyrl: "Uzbek (Cyrillic)",
    uz_Cyrl_UZ: "Uzbek (Cyrillic, Uzbekistan)",
    uz_Latn: "Uzbek (Latin)",
    uz_Latn_UZ: "Uzbek (Latin, Uzbekistan)",
    uz: "Uzbek",
    vi_VN: "Vietnamese (Vietnam)",
    vi: "Vietnamese",
    vun_TZ: "Vunjo (Tanzania)",
    vun: "Vunjo",
    cy_GB: "Welsh (United Kingdom)",
    cy: "Welsh",
    yo_NG: "Yoruba (Nigeria)",
    yo: "Yoruba",
    zu_ZA: "Zulu (South Africa)",
    zu: "Zulu"
}

*/
