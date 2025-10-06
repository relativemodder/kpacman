import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import org.kde.kirigami as Kirigami

Kirigami.AbstractCard {
    required property string titleText
    required property string descriptionText
    required property string iconSource

    width: parent.width
    height: 120
    leftPadding: Kirigami.Units.largeSpacing * 3.5
    rightPadding: Kirigami.Units.largeSpacing * 3.5

    contentItem: Item {
        implicitWidth: delegateLayout.implicitWidth
        implicitHeight: delegateLayout.implicitHeight

        RowLayout {
            id: delegateLayout
            anchors {
                left: parent.left
                right: parent.right
                verticalCenter: parent.verticalCenter
            }

            spacing: Kirigami.Units.largeSpacing

            Image {
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                source: iconSource
                sourceSize.width: Kirigami.Units.iconSizes.huge
                sourceSize.height: Kirigami.Units.iconSizes.huge
            }

            Item {
                width: 10
            }

            ColumnLayout {
                spacing: 15

                Kirigami.Heading {
                    Layout.fillWidth: true
                    level: 1
                    font.weight: Font.Bold
                    text: titleText
                }
                Label {
                    Layout.fillWidth: true
                    text: descriptionText
                }
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                text: "Download"
                icon.name: "download"
                topPadding: 20
                bottomPadding: 20
            }
        }
    }
}
