TARGET = tst_aggregation
include(../../common.pri)

INCLUDEPATH += \
    ../../../src/engine/

HEADERS += \
    ../../../src/engine/contactid_p.h \
    ../../../src/extensions/contactmanagerengine.h \
    ../../util.h \
    testsyncadapter.h

SOURCES += \
    testsyncadapter.cpp \
    tst_aggregation.cpp

CONFIG(new_qtpim) {
    SOURCES += ../../../src/engine/contactid.cpp
} else {
    SOURCES += ../../../src/engine/contactengineid.cpp
}
