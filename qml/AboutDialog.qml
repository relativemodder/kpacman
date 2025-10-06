import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import org.kde.kirigami as Kirigami

Kirigami.OverlaySheet {
    id: aboutKPacmanDialog
    title: qsTr("About KPacman")
    modal: true
    focus: true
    padding: 10
    width: 400
    height: 200

    footer: Row {
        topPadding: 10
        Label {
            text: qsTr("2025 Relative. Free software. Developer preview.")
        }
    }

    Row {
        spacing: Kirigami.Units.gridUnit
        padding: 10

        Kirigami.Icon {
            source: "help-about"
            width: Kirigami.Units.iconSizes.huge
            height: Kirigami.Units.iconSizes.huge
            Layout.alignment: Qt.AlignHCenter
            color: Kirigami.Theme.linkColor
        }

        Label {
            text: qsTr("KPacman is a GUI package manager,\n"
                       + "built on top of Qt and KDE technologies.")
            wrapMode: Label.Wrap
        }
    }
}
