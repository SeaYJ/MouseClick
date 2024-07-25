!defined(QMAKE_QWK_CORE_INCLUDED, var) {
    QMAKE_QWK_CORE_INCLUDED = 1

    # CMake variables
    QMAKE_QWK_INSTALL_PREFIX = $$PWD/../../..
    QMAKE_QWK_INSTALL_BINDIR = bin
    QMAKE_QWK_INSTALL_LIBDIR = lib
    QMAKE_QWK_INSTALL_INCDIR = include

    # Shared include directory
    INCLUDEPATH += \
        $$QMAKE_QWK_INSTALL_PREFIX/$$QMAKE_QWK_INSTALL_INCDIR/QWindowKit

    # Shared link directory
    LIBS += \
        "-L$$QMAKE_QWK_INSTALL_PREFIX/$$QMAKE_QWK_INSTALL_LIBDIR"
    
    CONFIG(debug, debug|release) {
        LIBS += -lQWKCore
    } else {
        LIBS += -lQWKCore
    }

    
}
