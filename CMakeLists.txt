cmake_minimum_required(VERSION 3.20)

project(Kpacman VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(APP_ID="com.github.relative.kpacman")

find_package(ECM 6.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(ECMFindQmlModule)
include(ECMQmlModule)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Quick
    Test
    Gui
    QuickControls2
    Widgets
)
find_package(KF6 REQUIRED COMPONENTS
    Kirigami
    I18n
    CoreAddons
    QQC2DesktopStyle
    IconThemes
)

ecm_find_qmlmodule(org.kde.kirigami REQUIRED)

qt_standard_project_setup(REQUIRES 6.8)

macro(make_relative_paths IN_LIST OUT_LIST BASE_DIR)
  set(${OUT_LIST})

  string(REGEX REPLACE "([^/])$" "\\1/" REPLACE_PREFIX ${BASE_DIR})

  foreach(ABS_PATH IN LISTS ${IN_LIST})
    string(REPLACE "${REPLACE_PREFIX}" "" REL_PATH ${ABS_PATH})
    list(APPEND ${OUT_LIST} ${REL_PATH})
  endforeach()
endmacro()


qt_add_executable(appKpacman
    src/main.cpp
)

file(GLOB_RECURSE PROJ_SRC src/*.cpp)
file(GLOB_RECURSE PROJ_H include/*.h)
file(GLOB_RECURSE PROJ_QML qml/*.qml)

make_relative_paths(PROJ_SRC PROJ_SRC_REL ${CMAKE_CURRENT_SOURCE_DIR})
make_relative_paths(PROJ_H PROJ_H_REL ${CMAKE_CURRENT_SOURCE_DIR})
make_relative_paths(PROJ_QML PROJ_QML_REL ${CMAKE_CURRENT_SOURCE_DIR})

qt_add_qml_module(appKpacman
    URI Kpacman
    VERSION 1.0
    QML_FILES ${PROJ_QML_REL}
    SOURCES ${PROJ_H_REL}
    SOURCES ${PROJ_SRC_REL}
    RESOURCES README.md
    RESOURCES LICENSE
)

target_link_libraries(appKpacman
    PRIVATE Qt6::Quick Qt6::QuickControls2
)
target_link_libraries(appKpacman PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)

target_include_directories(appKpacman PUBLIC include/)

include(GNUInstallDirs)
install(TARGETS appKpacman
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
add_subdirectory(kpacmand)
