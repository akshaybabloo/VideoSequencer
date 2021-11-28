set( CMAKE_TOOLCHAIN_FILE "C:/Users/em8273/vcpkg/scripts/buildsystems/vcpkg.cmake" )
cmake_minimum_required(VERSION 3.5)


project(VideoSequencer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CLion setting. This will not work in Windows.
if ($ENV{CLION_IDE})
    set(QT_VERSION_MAJOR 6)
    # Note: This path needs to be update on every new Qt version
    if (WIN32)
        # For some reason its not working on Windows. Use Qt Creator to make it runnable.
        set(Qt6_DIR "C:/Qt/6.2.1/msvc2019_64/lib/cmake/")
        set(CMAKE_PREFIX_PATH "C:/Qt/6.2.1/msvc2019_64/lib/cmake")
    elseif (APPLE)
        set(CMAKE_PREFIX_PATH /Users/akshayrajgollahalli/Qt/6.2.1/macos)
    endif ()
endif ()

message("${CMAKE_CURRENT_BINARY_DIR}")

set(OpenCV_DIR "cmake-build-debug/vcpkg_installed/x64-windows/share/opencv")

find_package(QT NAMES Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui REQUIRED)
find_package(OpenCV CONFIG REQUIRED)

if( OpenCV_FOUND )
    # Additional Include Directories
    include_directories( ${OpenCV_INCLUDE_DIRS} )

    # Additional Library Directories
    link_directories( ${OpenCV_LIB_DIR} )
endif()

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp mainwindow.h mainwindow.ui

        converter.cpp converter.h
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

        ${OpenCV_LIBS}
        )

set_target_properties(VideoSequencer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(VideoSequencer)
endif()
