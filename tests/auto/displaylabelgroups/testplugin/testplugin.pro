TEMPLATE        = lib
CONFIG         += plugin c++11 link_pkgconfig
INCLUDEPATH    += ../../../../src/extensions/
QT             -= gui
HEADERS         = testdlggplugin.h
SOURCES         = testdlggplugin.cpp
TARGET          = $$qtLibraryTarget(testdlgg)
PLUGIN_TYPE     = contacts_dlgg
DESTDIR         = $${PLUGIN_TYPE}
PKGCONFIG      += Qt5Contacts
target.path     = /usr/lib/qtcontacts-sqlite-qt5/
INSTALLS       += target
