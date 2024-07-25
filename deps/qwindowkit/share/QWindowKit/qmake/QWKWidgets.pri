!defined(QMAKE_QWK_WIDGETS_INCLUDED, var) {
    QMAKE_QWK_WIDGETS_INCLUDED = 1

    include($$PWD/QWKCore.pri)

    CONFIG(debug, debug|release) {
        LIBS += -lQWKWidgets
    } else {
        LIBS += -lQWKWidgets
    }

    
}
