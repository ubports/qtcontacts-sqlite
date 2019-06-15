CONFIG += \
    c++11 \
    link_pkgconfig
PKGCONFIG += Qt5Contacts

CONFIG(new_qtpim) {
    DEFINES += NEW_QTPIM
}

packagesExist(mlite5) {
    DEFINES += HAS_MLITE
}
