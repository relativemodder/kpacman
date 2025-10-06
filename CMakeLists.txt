cmake_minimum_required(VERSION 3.20)

project(Kpacman VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ECM 6.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
# include(KDECompilerSettings NO_POLICY_SCOPE)
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

qt_add_executable(appKpacman
    main.cpp
)

qt_add_qml_module(appKpacman
    URI Kpacman
    VERSION 1.0
    QML_FILES
        Main.qml
        Icon.qml
        DownloadPage.qml
        RemovePage.qml
        UpdatePage.qml
        SettingsPage.qml
    SOURCES IconProvider.h IconProvider.cpp
    QML_FILES AboutDialog.qml
)

target_link_libraries(appKpacman
    PRIVATE Qt6::Quick Qt6::QuickControls2
)
target_link_libraries(appKpacman PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)

include(GNUInstallDirs)
install(TARGETS appKpacman
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
