TARGET = tst_qcontactmanagerfiltering

include(../../common.pri)

INCLUDEPATH += \
    ../../../src/engine/

HEADERS += \
    ../../../src/engine/contactid_p.h \
    ../../../src/extensions/contactmanagerengine.h \
    ../../util.h \
    ../../qcontactmanagerdataholder.h
SOURCES += \
    tst_qcontactmanagerfiltering.cpp

CONFIG(new_qtpim) {
    SOURCES += ../../../src/engine/contactid.cpp
} else {
    SOURCES += ../../../src/engine/contactengineid.cpp
}
