TARGET = tst_database

include(../../common.pri)

QT += sql

# copied from src/engine/engine.pro, modified for test db
DEFINES += 'QTCONTACTS_SQLITE_PRIVILEGED_DIR=\'\"privileged\"\''
DEFINES += 'QTCONTACTS_SQLITE_DATABASE_DIR=\'\"Contacts/qtcontacts-sqlite\"\''
DEFINES += 'QTCONTACTS_SQLITE_DATABASE_NAME=\'\"contacts-test.db\"\''
# we build a path like: /home/nemo/.local/share/system/Contacts/qtcontacts-sqlite-test/contacts-test.db

TEST_DATA_DIR = $$PWD/data
DEFINES += 'TEST_DATA_DIR=\'\"$$TEST_DATA_DIR\"\''

INCLUDEPATH += \
    ../../../src/engine/

HEADERS += ../../../src/engine/contactsdatabase.h
SOURCES += ../../../src/engine/contactsdatabase.cpp

HEADERS += ../../../src/engine/semaphore_p.h
SOURCES += ../../../src/engine/semaphore_p.cpp

HEADERS += ../../../src/engine/contactstransientstore.h
SOURCES += ../../../src/engine/contactstransientstore.cpp

HEADERS += ../../../src/engine/memorytable.h
SOURCES += ../../../src/engine/memorytable.cpp

HEADERS += ../../../src/engine/conversion_p.h
SOURCES += ../../../src/engine/conversion.cpp

HEADERS += ../../../src/engine/defaultdlggenerator.h
SOURCES += ../../../src/engine/defaultdlggenerator.cpp

SOURCES += stub_contactsengine.cpp

SOURCES += tst_database.cpp
