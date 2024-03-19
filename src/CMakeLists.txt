cmake_minimum_required(VERSION 3.5)

project(Viewer_2_0 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt6 COMPONENTS Widgets OpenGL OpenGLWidgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_subdirectory(third_party/QtGifImage)

set(PROJECT_SOURCES
        View/main.cpp
        View/viewer.cpp
        View/viewer.h
        View/viewer.ui
        View/glwidget.cpp
        View/glwidget.h
        Model/model.cpp
        Model/obj_data.h
        Model/parser.cpp
        Model/transformation.cpp
        Model/transformation.h
        Controller/contrl.cpp
)
set(CMAKE_CXX_FLAGS
       "-lglut -lGL -lGLU"
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Viewer_2_0
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Viewer_2_0 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Viewer_2_0 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Viewer_2_0
            ${PROJECT_SOURCES}
        )
    endif()
endif()

set(LINK_LIBRARIES
        QtGifImage::QtGifImage
        # other link libraries
        # For example:
        Qt${QT_VERSION_MAJOR}::Widgets
)

target_link_libraries(Viewer_2_0 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets  Qt6::OpenGLWidgets)
target_link_libraries(Viewer_2_0 PRIVATE ${LINK_LIBRARIES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Viewer_2_0)
endif()
set_target_properties(Viewer_2_0 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Viewer_2_0
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Viewer_2_0)
endif()
