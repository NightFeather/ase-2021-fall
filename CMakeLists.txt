cmake_minimum_required(VERSION 3.5)

project(ase-2021-fall VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Sql REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Sql REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        icons.qrc
        images.qrc

        navigate/pagecontext.h
        navigate/pagecontext.cpp
        navigate/navcontext.h
        navigate/navcontext.cpp
        navigate/pagewidget.h
        navigate/pagewidget.cpp

        datatypes/note.h
        datatypes/note.cpp
        datatypes/attachment.h
        datatypes/attachment.cpp

        storage/storagebackend.h
        storage/storagebackend.cpp

        landing/landingwidget.h
        landing/landingwidget.cpp
        landing/landingwidget.ui

        browser/browserwidget.h
        browser/browserwidget.cpp
        browser/browserwidget.ui

        editor/editorwidget.h
        editor/editorwidget.cpp
        editor/editorwidget.ui
        editor/attachmentwidget.h
        editor/attachmentwidget.cpp
        editor/attachmentwidget.ui
        editor/attachmentlist.h
        editor/attachmentlist.cpp
        editor/attachmentlist.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ase-2021-fall
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ase-2021-fall APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ase-2021-fall SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ase-2021-fall
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ase-2021-fall
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
)

set_target_properties(ase-2021-fall PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ase-2021-fall)
endif()
