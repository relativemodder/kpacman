import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import org.kde.kirigami as Kirigami

Rectangle {
    color: palette.base
    Kirigami.ScrollablePage {
        anchors.fill: parent
        background: palette.base

        ListModel {
            id: packageItemModel
            ListElement {
                titleText: "Firefox"
                descriptionText: "Fast, private and secure web browser from Mozilla"
                iconSource: "image://icon/firefox"
            }
            ListElement {
                titleText: "VLC Media Player"
                descriptionText: "Powerful multimedia player that plays most video and audio formats"
                iconSource: "image://icon/vlc"
            }
            ListElement {
                titleText: "Visual Studio Code"
                descriptionText: "Lightweight but powerful source code editor with built-in Git support"
                iconSource: "image://icon/visual-studio-code"
            }
            ListElement {
                titleText: "Telegram Desktop"
                descriptionText: "Fast and secure messaging app with cloud-based synchronization"
                iconSource: "image://icon/org.telegram.desktop"
            }
            ListElement {
                titleText: "Audacity"
                descriptionText: "Free, open source audio editor and recording software"
                iconSource: "image://icon/audacity"
            }
            ListElement {
                titleText: "Inkscape"
                descriptionText: "Vector graphics editor for creating illustrations, diagrams, and logos"
                iconSource: "image://icon/org.inkscape.Inkscape"
            }
            ListElement {
                titleText: "Steam"
                descriptionText: "Gaming platform with thousands of games and community features"
                iconSource: "image://icon/steam"
            }
        }

        Kirigami.CardsListView {
            model: packageItemModel
            delegate: PackageItem {}
            spacing: 30
        }
    }
}
