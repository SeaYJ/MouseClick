!defined(QMAKE_QWK_QUICK_INCLUDED, var) {
    QMAKE_QWK_QUICK_INCLUDED = 1

    include($$PWD/QWKCore.pri)

    CONFIG(debug, debug|release) {
        LIBS += -lQWKQuick
    } else {
        LIBS += -lQWKQuick
    }

    
}
