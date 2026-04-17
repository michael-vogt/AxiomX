cmake_minimum_required(VERSION 3.16)

project(AxiomX VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES




)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(AxiomX
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        src/core/circle.h src/core/core.h src/core/geoobject.h src/core/line.h src/core/point.h src/tools/linetool.h src/tools/movetool.h src/tools/pointtool.h src/tools/tool.h src/view/geoview.h src/view/graphicsline.h src/view/graphicsobject.h src/view/graphicspoint.h src/view/observer.h src/view/view.h src/main.cpp src/mainwindow.h src/mainwindow.ui
        src/tools/tools.h
        src/control/interactionmanager.h src/control/scenecontroller.h
        src/control/interactionmanager.h src/control/scenecontroller.h
        src/control/selectionmanager.h
        src/tools/selecttool.h
        src/control/control.h
        src/allincludes.h
        src/core/utility.h
        src/command/command.h
        src/command/commandmanager.h
        src/command/createpointcommand.h
        src/command/createlinecommand.h
        src/command/movepointcommand.h
        src/command/resultcommand.h
        src/core/infinitelineitem.h
        src/tools/circletool.h
        src/view/graphicscircle.h
        src/command/createcirclecommand.h
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET AxiomX APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(AxiomX SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(AxiomX
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(AxiomX PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.AxiomX)
endif()
set_target_properties(AxiomX PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS AxiomX
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(AxiomX)
endif()
