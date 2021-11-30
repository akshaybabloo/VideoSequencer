cmake_minimum_required(VERSION 3.5)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_BINARY_DIR}/conan_toolchain.cmake")

project(VideoSequencer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CLion setting. This will not work in Windows.
if ($ENV{CLION_IDE})
    set(QT_VERSION_MAJOR 6)
    # Note: This path needs to be update on every new Qt version
    if (WIN32)
        # For some reason its not working on Windows. Use Qt Creator to make it runnable.
        list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.2.1/msvc2019_64/")
    elseif (APPLE)
        list(APPEND CMAKE_PREFIX_PATH /Users/akshayrajgollahalli/Qt/6.2.1/macos)
    endif ()
endif ()

find_package(QT NAMES Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui REQUIRED)
find_package(OpenCV REQUIRED)
find_package(boost REQUIRED COMPONENTS range)
find_package(ffmpeg REQUIRED COMPONENTS avcodec avformat)

if (APPLE)
    set(MACOS_BUNDLE_ICON_FILE logo.icns)
    set(app_icon_macos "assets/logo/logo.icns")
    set_source_files_properties(${app_icon_macos} PROPERTIES MACOS_PACKAGE_LOCATION "Resources")
endif ()

if (WIN32)
    set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/win.rc")
endif ()

set(PROJECT_SOURCES
        main.cpp

        assets.qrc

        ${app_icon_macos}
        ${APP_ICON_RESOURCE_WINDOWS}

        mainwindow.cpp mainwindow.h mainwindow.ui

        converter.cpp converter.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(VideoSequencer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
endif()

if (APPLE)
    set_property(TARGET VideoSequencer PROPERTY MACOSX_BUNDLE_INFO_PLAYLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist")
endif ()

target_link_libraries(VideoSequencer PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Gui

        Boost::boost
        opencv::core
        opencv::videoio
        opencv::video
        opencv::imgcodecs
        ffmpeg::avcodec
        ffmpeg::avformat
        )

set_target_properties(VideoSequencer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.gollahalli.videosequencer
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(VideoSequencer)
endif()
