include(../../../common-xlets.pri)

HEADERS     = *.h
SOURCES     = *.cpp
FORMS       = people_widget.ui

TARGET      = peopleplugin

TRANSLATIONS += $$ROOT_DIR/i18n/people_en.ts
TRANSLATIONS += $$ROOT_DIR/i18n/people_es_ES.ts
TRANSLATIONS += $$ROOT_DIR/i18n/people_pt_BR.ts
TRANSLATIONS += $$ROOT_DIR/i18n/people_hu.ts
TRANSLATIONS += $$ROOT_DIR/i18n/people_de.ts
TRANSLATIONS += $$ROOT_DIR/i18n/people_ja.ts
TRANSLATIONS += $$ROOT_DIR/i18n/people_it.ts
TRANSLATIONS += $$ROOT_DIR/i18n/people_fr.ts
TRANSLATIONS += $$ROOT_DIR/i18n/people_nl.ts

RESOURCES = people.qrc
