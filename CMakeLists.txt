cmake_minimum_required(VERSION 3.5)

project(MouseClick VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(QWINDOWKIT_ROOT "${CMAKE_SOURCE_DIR}/deps/qwindowkit")
find_package(QWindowKit REQUIRED PATH "${QWINDOWKIT_ROOT}/lib/cmake/QWindowKit")

set(QHOTKEY_ROOT "${CMAKE_SOURCE_DIR}/deps/qhotkey")
find_package(QHotkey REQUIRED PATHS "${QHOTKEY_ROOT}/lib/cmake/QHotkey")

set(QWK_WINDOWBAR_FILES
    src/qwk_window_bar/windowbar.h      src/qwk_window_bar/windowbar.cpp
    src/qwk_window_bar/windowbutton.h   src/qwk_window_bar/windowbutton.cpp
    src/qwk_window_bar/private/windowbar_p.h
    src/qwk_window_bar/private/windowbutton_p.h
)

set(TRANSLATIONS_FILES i18n/MouseClick_zh_CN.ts)

set(QRC_FILES assets/assets.qrc)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.h                        src/mainwindow.cpp
        src/modules/nav_pages/mouseclickpage.h  src/modules/nav_pages/mouseclickpage.cpp
        src/modules/shared.h                    src/modules/shared.cpp
        src/modules/styleagent.h                src/modules/styleagent.cpp
        src/modules/hotkeylineedit.h            src/modules/hotkeylineedit.cpp
        src/utils/clicker.h                     src/utils/clicker.cpp
        ${QWK_WINDOWBAR_FILES}
        ${TRANSLATIONS_FILES}
        ${QRC_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MouseClick
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MouseClick APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    # qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TRANSLATIONS_FILES})
    qt_add_translations(MouseClick TS_FILES ${TRANSLATIONS_FILES})
else()
    if(ANDROID)
        add_library(MouseClick SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MouseClick
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TRANSLATIONS_FILES})
endif()

target_link_libraries(MouseClick PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_include_directories(MouseClick PRIVATE "${QWINDOWKIT_ROOT}/include/QWindowKit::Widgets")
target_link_libraries(MouseClick PRIVATE QWindowKit::Widgets)

target_include_directories(MouseClick PRIVATE ${QHOTKEY_ROOT}/include)
target_link_libraries(MouseClick PRIVATE qhotkey)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.MouseClick)
endif()
set_target_properties(MouseClick PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS MouseClick
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MouseClick)
endif()
