cmake_minimum_required(VERSION 3.5)

project(VideoSequencer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(conan_paths.cmake)

# CLion setting. This will not work in Windows.
if ($ENV{CLION_IDE})
    set(QT_VERSION_MAJOR 6)
    # Note: This path needs to be update on every new Qt version
    if (WIN32)
        # For some reason its not working on Windows. Use Qt Creator to make it runnable.
        set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/msvc2019_64")
    elseif (APPLE)
        set(CMAKE_PREFIX_PATH /Users/akshayrajgollahalli/Qt/6.2.0/macos)
    endif ()
endif ()

find_package(QT NAMES Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(ffmpeg REQUIRED IMPORTED_TARGET libavformat)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(VideoSequencer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(VideoSequencer PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Gui
        PkgConfig::ffmpeg)

set_target_properties(VideoSequencer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(VideoSequencer)
endif()
