include(../../../common-xlets.pri)

HEADERS     = *.h
SOURCES     = *.cpp
TRANSLATIONS = $$ROOT_DIR/i18n/queueentrydetails_fr.ts
TRANSLATIONS += $$ROOT_DIR/i18n/queueentrydetails_nl.ts

TARGET      = $$qtLibraryTarget(queueentrydetailsplugin)

RESOURCES = queueentrydetails.qrc