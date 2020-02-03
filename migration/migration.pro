TEMPLATE = app
TARGET = eds_importer

QT += \
    core \
    sql

CONFIG += \
    c++11 \
    link_pkgconfig

PKGCONFIG += \
    Qt5Contacts \
    Qt5Versit

SOURCES += \
    eds_importer.cpp

target.path = /usr/bin
INSTALLS += target
