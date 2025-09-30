# gtkmm4-dropdown-language-selection

This small sample C++ code which demonstrate language selection dropdown for easy use in your app, this code is possible to build and run on Debian13 or on Windows in MSYS2 enviroment.

![Screenschot](Screenshot.png)

Building on Windows:
====================

1.) Install MSYS2
-----------------
Download and run the msys2 installer from http://msys2.github.io/ Tested only with the 64bit version. Make sure that the path you select for installation doesn’t contain any spaces.

2.) Start MSYS console
----------------------
Launch the Start Menu item “MSYS2 mingw 64 bit” you should be greeted with a console window. All steps below refer to what you should type into that window.

3.) Install updates
-------------------
Type:

   pacman -Syu

if it tells you to close restart msys, close the console window and start it again. Then run pacman -Syu again.

4.) Install dependencies
------------------------
Type/paste

   pacman -S \\ \
   mingw-w64-x86_64-gcc \\ \
   mingw-w64-x86_64-pkgconf \\ \
   mingw-w64-x86_64-gtkmm4 \\ \
   zip \\ \
   unzip \\ \
   git \\ \
   --needed

When prompted, just hit return. Sit back and wait for it to install what’s almost a complete linux environment.

Before continuing you may change to another directory. It easiest to type cd followed by a space and drop the folder you want to change to on the window.

5.) Clone gtkmm4-dropdown-language-selection by type/paste on commandline:
--------------------------------------------------------------------------

   git clone https://github.com/Peta-T/gtkmm4-dropdown-language-selection \
   cd gtkmm4-dropdown-language-selection
   
6.) Build it - type on command line:
------------------------------------

   g++ -std=c++17 main.cc languageselector.cc ./images/resources.c -o app $(pkg-config --cflags --libs gtkmm-4.0)

7.) Run app - type on command line:
-----------------------------------

   ./app



| Flag | Autonymum | Locale | English Name |
|------|-----------|--------|--------------|
| ![](images/zz.svg) | C | C.UTF-8 | C locale |
| ![](images/dj.svg) | Afaraf | aa_DJ.UTF-8 | Afar |
| ![](images/za.svg) | Afrikaans | af_ZA.UTF-8 | Afrikaans |
| ![](images/es.svg) | Aragonés | an_ES.UTF-8 | Aragonese |
| ![](images/ae.svg) | العربية | ar_AE.UTF-8 | Arabic (UAE) |
| ![](images/bh.svg) | العربية | ar_BH.UTF-8 | Arabic (Bahrain) |
| ![](images/dz.svg) | العربية | ar_DZ.UTF-8 | Arabic (Algeria) |
| ![](images/eg.svg) | العربية | ar_EG.UTF-8 | Arabic (Egypt) |
| ![](images/iq.svg) | العربية | ar_IQ.UTF-8 | Arabic (Iraq) |
| ![](images/jo.svg) | العربية | ar_JO.UTF-8 | Arabic (Jordan) |
| ![](images/kw.svg) | العربية | ar_KW.UTF-8 | Arabic (Kuwait) |
| ![](images/lb.svg) | العربية | ar_LB.UTF-8 | Arabic (Lebanon) |
| ![](images/ly.svg) | العربية | ar_LY.UTF-8 | Arabic (Libya) |
| ![](images/ma.svg) | العربية | ar_MA.UTF-8 | Arabic (Morocco) |
| ![](images/om.svg) | العربية | ar_OM.UTF-8 | Arabic (Oman) |
| ![](images/qa.svg) | العربية | ar_QA.UTF-8 | Arabic (Qatar) |
| ![](images/sa.svg) | العربية | ar_SA.UTF-8 | Arabic (Saudi Arabia) |
| ![](images/sd.svg) | العربية | ar_SD.UTF-8 | Arabic (Sudan) |
| ![](images/sy.svg) | العربية | ar_SY.UTF-8 | Arabic (Syria) |
| ![](images/tn.svg) | العربية | ar_TN.UTF-8 | Arabic (Tunisia) |
| ![](images/ye.svg) | العربية | ar_YE.UTF-8 | Arabic (Yemen) |
| ![](images/es.svg) | Asturianu | ast_ES.UTF-8 | Asturian |
| ![](images/by.svg) | Беларуская | be_BY.UTF-8 | Belarusian |
| ![](images/bg.svg) | български език | bg_BG.UTF-8 | Bulgarian |
| ![](images/in.svg) | भिल्ली | bhb_IN.UTF-8 | Bhili |
| ![](images/fr.svg) | brezhoneg | br_FR.UTF-8 | Breton |
| ![](images/ba.svg) | bosanski jezik | bs_BA.UTF-8 | Bosnian |
| ![](images/ad.svg) | Català | ca_AD.UTF-8 | Catalan (Andorra) |
| ![](images/es.svg) | Català | ca_ES.UTF-8 | Catalan (Spain) |
| ![](images/fr.svg) | Català | ca_FR.UTF-8 | Catalan (France) |
| ![](images/it.svg) | Català | ca_IT.UTF-8 | Catalan (Italy) |
| ![](images/cz.svg) | čeština | cs_CZ.UTF-8 | Czech |
| ![](images/gb.svg) | Cymraeg | cy_GB.UTF-8 | Welsh |
| ![](images/dk.svg) | dansk | da_DK.UTF-8 | Danish |
| ![](images/at.svg) | Deutsch | de_AT.UTF-8 | German (Austria) |
| ![](images/be.svg) | Deutsch | de_BE.UTF-8 | German (Belgium) |
| ![](images/ch.svg) | Deutsch | de_CH.UTF-8 | German (Switzerland) |
| ![](images/de.svg) | Deutsch | de_DE.UTF-8 | German (Germany) |
| ![](images/it.svg) | Deutsch | de_IT.UTF-8 | German (Italy) |
| ![](images/li.svg) | Deutsch | de_LI.UTF-8 | German (Liechtenstein) |
| ![](images/lu.svg) | Deutsch | de_LU.UTF-8 | German (Luxembourg) |
| ![](images/cy.svg) | Ελληνικά | el_CY.UTF-8 | Greek (Cyprus) |
| ![](images/gr.svg) | Ελληνικά | el_GR.UTF-8 | Greek (Greece) |
| ![](images/au.svg) | English | en_AU.UTF-8 | English (Australia) |
| ![](images/bw.svg) | English | en_BW.UTF-8 | English (Botswana) |
| ![](images/ca.svg) | English | en_CA.UTF-8 | English (Canada) |
| ![](images/dk.svg) | English | en_DK.UTF-8 | English (Denmark) |
| ![](images/gb.svg) | English | en_GB.UTF-8 | English (UK) |
| ![](images/hk.svg) | English | en_HK.UTF-8 | English (Hong Kong) |
| ![](images/ie.svg) | English | en_IE.UTF-8 | English (Ireland) |
| ![](images/in.svg) | English | en_IN.UTF-8 | English (India) |
| ![](images/nz.svg) | English | en_NZ.UTF-8 | English (New Zealand) |
| ![](images/ph.svg) | English | en_PH.UTF-8 | English (Philippines) |
| ![](images/se.svg) | English | en_SE.UTF-8 | English (Sweden) |
| ![](images/sc.svg) | English | en_SC.UTF-8 | English (Seychelles) |
| ![](images/sg.svg) | English | en_SG.UTF-8 | English (Singapore) |
| ![](images/us.svg) | English | en_US.UTF-8 | English (USA) |
| ![](images/za.svg) | English | en_ZA.UTF-8 | English (South Africa) |
| ![](images/zw.svg) | English | en_ZW.UTF-8 | English (Zimbabwe) |
| ![](images/ar.svg) | español; castellano | es_AR.UTF-8 | Spanish (Argentina) |
| ![](images/bo.svg) | español; castellano | es_BO.UTF-8 | Spanish (Bolivia) |
| ![](images/cl.svg) | español; castellano | es_CL.UTF-8 | Spanish (Chile) |
| ![](images/co.svg) | español; castellano | es_CO.UTF-8 | Spanish (Colombia) |
| ![](images/cr.svg) | español; castellano | es_CR.UTF-8 | Spanish (Costa Rica) |
| ![](images/do.svg) | español; castellano | es_DO.UTF-8 | Spanish (Dominican Rep.) |
| ![](images/ec.svg) | español; castellano | es_EC.UTF-8 | Spanish (Ecuador) |
| ![](images/es.svg) | español; castellano | es_ES.UTF-8 | Spanish (Spain) |
| ![](images/gt.svg) | español; castellano | es_GT.UTF-8 | Spanish (Guatemala) |
| ![](images/hn.svg) | español; castellano | es_HN.UTF-8 | Spanish (Honduras) |
| ![](images/mx.svg) | español; castellano | es_MX.UTF-8 | Spanish (Mexico) |
| ![](images/ni.svg) | español; castellano | es_NI.UTF-8 | Spanish (Nicaragua) |
| ![](images/pa.svg) | español; castellano | es_PA.UTF-8 | Spanish (Panama) |
| ![](images/pe.svg) | español; castellano | es_PE.UTF-8 | Spanish (Peru) |
| ![](images/pr.svg) | español; castellano | es_PR.UTF-8 | Spanish (Puerto Rico) |
| ![](images/py.svg) | español; castellano | es_PY.UTF-8 | Spanish (Paraguay) |
| ![](images/sv.svg) | español; castellano | es_SV.UTF-8 | Spanish (El Salvador) |
| ![](images/us.svg) | español; castellano | es_US.UTF-8 | Spanish (USA) |
| ![](images/uy.svg) | español; castellano | es_UY.UTF-8 | Spanish (Uruguay) |
| ![](images/ve.svg) | español; castellano | es_VE.UTF-8 | Spanish (Venezuela) |
| ![](images/ee.svg) | Eesti keel | et_EE.UTF-8 | Estonian |
| ![](images/es.svg) | euskara | eu_ES.UTF-8 | Basque (Spain) |
| ![](images/fr.svg) | euskara | eu_FR.UTF-8 | Basque (France) |
| ![](images/ph.svg) | Filipino | fil_PH.UTF-8 | Filipino |
| ![](images/fi.svg) | suomi | fi_FI.UTF-8 | Finnish |
| ![](images/fo.svg) | føroyskt | fo_FO.UTF-8 | Faroese |
| ![](images/be.svg) | français; langue française | fr_BE.UTF-8 | French (Belgium) |
| ![](images/ca.svg) | français; langue française | fr_CA.UTF-8 | French (Canada) |
| ![](images/ch.svg) | français; langue française | fr_CH.UTF-8 | French (Switzerland) |
| ![](images/fr.svg) | français; langue française | fr_FR.UTF-8 | French (France) |
| ![](images/lu.svg) | français; langue française | fr_LU.UTF-8 | French (Luxembourg) |
| ![](images/ie.svg) | Gaeilge | ga_IE.UTF-8 | Irish |
| ![](images/gb.svg) | Gàidhlig | gd_GB.UTF-8 | Scottish Gaelic |
| ![](images/es.svg) | Galego | gl_ES.UTF-8 | Galician |
| ![](images/in.svg) | ગુજરાતી | gu_IN.UTF-8 | Gujarati |
| ![](images/gb.svg) | Gaelg | gv_GB.UTF-8 | Manx |
| ![](images/il.svg) | עברית | he_IL.UTF-8 | Hebrew |
| ![](images/in.svg) | हिन्दी | hi_IN.UTF-8 | Hindi |
| ![](images/hr.svg) | Hrvatski | hr_HR.UTF-8 | Croatian |
| ![](images/de.svg) | hornjoserbšćina | hsb_DE.UTF-8 | Upper Sorbian |
| ![](images/hu.svg) | Magyar | hu_HU.UTF-8 | Hungarian |
| ![](images/id.svg) | Bahasa Indonesia | id_ID.UTF-8 | Indonesian |
| ![](images/is.svg) | íslenska | is_IS.UTF-8 | Icelandic |
| ![](images/ch.svg) | Italiano | it_CH.UTF-8 | Italian (Switzerland) |
| ![](images/it.svg) | Italiano | it_IT.UTF-8 | Italian (Italy) |
| ![](images/jp.svg) | 日本語 | ja_JP.UTF-8 | Japanese |
| ![](images/ge.svg) | ქართული | ka_GE.UTF-8 | Georgian |
| ![](images/kz.svg) | Қазақ тілі | kk_KZ.UTF-8 | Kazakh |
| ![](images/gl.svg) | kalaallisut | kl_GL.UTF-8 | Greenlandic |
| ![](images/kh.svg) | ភាសាខ្មែរ | km_KH.UTF-8 | Khmer |
| ![](images/in.svg) | ಕನ್ನಡ | kn_IN.UTF-8 | Kannada |
| ![](images/kr.svg) | 한국어 (韓國語) | ko_KR.UTF-8 | Korean |
| ![](images/tr.svg) | Kurdî | ku_TR.UTF-8 | Kurdish |
| ![](images/gb.svg) | Kernewek | kw_GB.UTF-8 | Cornish |
| ![](images/ug.svg) | Luganda | lg_UG.UTF-8 | Ganda |
| ![](images/la.svg) | ພາສາລາວ | lo_LA.UTF-8 | Lao |
| ![](images/lt.svg) | lietuvių kalba | lt_LT.UTF-8 | Lithuanian |
| ![](images/lv.svg) | latgaliešu | ltg_LV.UTF-8 | Latgalian |
| ![](images/lv.svg) | latviešu valoda | lv_LV.UTF-8 | Latvian |
| ![](images/mg.svg) | Malagasy fiteny | mg_MG.UTF-8 | Malagasy |
| ![](images/nz.svg) | te reo Māori | mi_NZ.UTF-8 | Maori |
| ![](images/mk.svg) | македонски јазик | mk_MK.UTF-8 | Macedonian |
| ![](images/in.svg) | മലയാളം | ml_IN.UTF-8 | Malayalam |
| ![](images/mn.svg) | Монгол | mn_MN.UTF-8 | Mongolian |
| ![](images/my.svg) | Bahasa Melayu | ms_MY.UTF-8 | Malay |
| ![](images/mt.svg) | Malti | mt_MT.UTF-8 | Maltese |
| ![](images/no.svg) | Norsk (bokmål) | nb_NO.UTF-8 | Norwegian Bokmål |
| ![](images/be.svg) | Nederlands | nl_BE.UTF-8 | Dutch (Belgium) |
| ![](images/nl.svg) | Nederlands | nl_NL.UTF-8 | Dutch (Netherlands) |
| ![](images/no.svg) | Nynorsk | nn_NO.UTF-8 | Norwegian Nynorsk |
| ![](images/no.svg) | Norsk | no_NO.UTF-8 | Norwegian |
| ![](images/fr.svg) | Occitan | oc_FR.UTF-8 | Occitan |
| ![](images/ke.svg) | Afaan Oromoo | om_KE.UTF-8 | Oromo |
| ![](images/pl.svg) | Polski | pl_PL.UTF-8 | Polish |
| ![](images/br.svg) | Português | pt_BR.UTF-8 | Portuguese (Brazil) |
| ![](images/pt.svg) | Português | pt_PT.UTF-8 | Portuguese (Portugal) |
| ![](images/ro.svg) | română | ro_RO.UTF-8 | Romanian |
| ![](images/ru.svg) | русский язык | ru_RU.UTF-8 | Russian |
| ![](images/ua.svg) | русский язык | ru_UA.UTF-8 | Russian (Ukraine) |
| ![](images/sk.svg) | slovenčina | sk_SK.UTF-8 | Slovak |
| ![](images/si.svg) | slovenščina | sl_SI.UTF-8 | Slovenian |
| ![](images/dj.svg) | Soomaali | so_DJ.UTF-8 | Somali (Djibouti) |
| ![](images/ke.svg) | Soomaali | so_KE.UTF-8 | Somali (Kenya) |
| ![](images/so.svg) | Soomaali | so_SO.UTF-8 | Somali (Somalia) |
| ![](images/al.svg) | Shqip | sq_AL.UTF-8 | Albanian |
| ![](images/cs.svg) | српски језик | sr_CS.UTF-8 | Serbian (deprecated) |
| ![](images/za.svg) | seSotho | st_ZA.UTF-8 | Southern Sotho |
| ![](images/fi.svg) | Svenska | sv_FI.UTF-8 | Swedish (Finland) |
| ![](images/se.svg) | Svenska | sv_SE.UTF-8 | Swedish (Sweden) |
| ![](images/in.svg) | தமிழ் | ta_IN.UTF-8 | Tamil |
| ![](images/in.svg) | Tulu | tcy_IN.UTF-8 | Tulu |
| ![](images/tj.svg) | тоҷикӣ | tg_TJ.UTF-8 | Tajik |
| ![](images/th.svg) | ไทย | th_TH.UTF-8 | Thai |
| ![](images/ph.svg) | Tagalog | tl_PH.UTF-8 | Tagalog |
| ![](images/cy.svg) | Türkçe | tr_CY.UTF-8 | Turkish (Cyprus) |
| ![](images/tr.svg) | Türkçe | tr_TR.UTF-8 | Turkish (Turkey) |
| ![](images/ua.svg) | українська мова | uk_UA.UTF-8 | Ukrainian |
| ![](images/uz.svg) | O‘zbek | uz_UZ.UTF-8 | Uzbek |
| ![](images/vn.svg) | Tiếng Việt | vi_VN.UTF-8 | Vietnamese |
| ![](images/be.svg) | Walon | wa_BE.UTF-8 | Walloon |
| ![](images/za.svg) | isiXhosa | xh_ZA.UTF-8 | Xhosa |
| ![](images/us.svg) | ייִדיש | yi_US.UTF-8 | Yiddish |
| ![](images/cn.svg) | 简体中文 | zh_CN.UTF-8 | Simplified Chinese (China) |
| ![](images/hk.svg) | 粤语 | zh_HK.UTF-8 | Cantonese (Hong Kong) |
| ![](images/sg.svg) | 简体中文 | zh_SG.UTF-8 | Simplified Chinese (Singapore) |
| ![](images/tw.svg) | 繁體中文 | zh_TW.UTF-8 | Traditional Chinese (Taiwan) |
| ![](images/za.svg) | isiZulu | zu_ZA.UTF-8 | Zulu |

