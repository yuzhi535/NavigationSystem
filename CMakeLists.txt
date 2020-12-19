cmake_minimum_required(VERSION 3.5)

project(NavigationSystem LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools Multimedia Network LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools Multimedia Network REQUIRED)

set(TS_FILES NavigationSystem_zh_CN.ts graph.cpp graph.h graphui.cpp graphui.h
        mainwindow.cpp mainwindow.h mainwindow.ui
        edgedialog.cpp edgedialog.h vertexdialog.cpp vertexdialog.h)

if (ANDROID)
    add_library(NavigationSystem SHARED
            main.cpp
            mainwindow.cpp
            mainwindow.h
            mainwindow.ui

            ${TS_FILES}
            )
else ()
    add_executable(NavigationSystem
            main.cpp
            mainwindow.cpp
            mainwindow.h
            mainwindow.ui
            graphui.h
            graphui.cpp
            vertexdialog.h
            vertexdialog.cpp
            edgedialog.h
            edgedialog.cpp
            ${TS_FILES}
            )
endif ()

target_link_libraries(NavigationSystem PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::Network)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

add_custom_target(translations ALL DEPENDS ${QM_FILES})
