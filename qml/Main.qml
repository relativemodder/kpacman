import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

ApplicationWindow {
    id: mainWindow
    width: 1200
    height: 700
    visible: true
    title: qsTr("Download Software - KPacman")

    DownloadPage {
        id: downloadPage
    }
    RemovePage {
        id: removePage
    }
    UpdatePage {
        id: updatePage
    }
    SettingsPage {
        id: settingsPage
    }
    AboutDialog {
        id: aboutDialog
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            id: sidePanel
            Layout.preferredWidth: 250
            Layout.fillHeight: true
            color: palette.window
            z: 1

            ColumnLayout {
                anchors.fill: parent
                spacing: 0

                TextField {
                    id: searchField
                    Layout.fillWidth: true
                    Layout.margins: 5
                    placeholderText: qsTr("Search...")
                    leftPadding: 35
                    topPadding: 10
                    bottomPadding: 10

                    Image {
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.verticalCenter: parent.verticalCenter
                        source: "image://icon/search"
                        sourceSize.width: 16
                        sourceSize.height: 16
                    }
                }

                ScrollView {
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height - searchField.height - 50 - 10
                    clip: true

                    ListView {
                        model: ListModel {
                            ListElement {
                                name: "Download"
                                iconName: "download"
                                page: "downloadPage"
                                highlighted: true
                            }
                            ListElement {
                                name: "Remove"
                                iconName: "edit-delete"
                                page: "removePage"
                                highlighted: false
                            }
                            ListElement {
                                name: "Updates"
                                iconName: "system-software-update"
                                page: "updatePage"
                                highlighted: false
                            }
                            ListElement {
                                name: "Settings"
                                iconName: "preferences-other"
                                page: "settingsPage"
                                highlighted: false
                            }
                        }

                        delegate: ItemDelegate {
                            width: ListView.view.width
                            height: 40
                            highlighted: model.highlighted

                            contentItem: RowLayout {
                                spacing: 15

                                Image {
                                    source: "image://icon/" + model.iconName
                                    sourceSize.width: 22
                                    sourceSize.height: 22
                                    Layout.leftMargin: 5
                                }

                                Text {
                                    text: qsTr(model.name)
                                    color: palette.text
                                    Layout.fillWidth: true
                                }
                            }

                            onClicked: {
                                for (var i = 0; i < ListView.view.model.count; i++) {
                                    ListView.view.model.setProperty(
                                                i, "highlighted", false)
                                }
                                ListView.view.model.setProperty(index,
                                                                "highlighted",
                                                                true)

                                switch (model.page) {
                                case "downloadPage":
                                    contentStack.replace(downloadPage)
                                    mainWindow.title = qsTr(
                                                "Download Software - KPacman")
                                    break
                                case "removePage":
                                    contentStack.replace(removePage)
                                    mainWindow.title = qsTr(
                                                "Remove Packages - KPacman")
                                    break
                                case "updatePage":
                                    contentStack.replace(updatePage)
                                    mainWindow.title = qsTr(
                                                "Update Software - KPacman")
                                    break
                                case "settingsPage":
                                    contentStack.replace(settingsPage)
                                    mainWindow.title = qsTr(
                                                "Settings - KPacman")
                                    break
                                }
                            }
                        }
                    }
                }

                Item {
                    Layout.fillHeight: true
                }

                Rectangle {
                    Layout.fillWidth: true
                    height: 1
                    color: palette.mid
                }

                ItemDelegate {
                    Layout.fillWidth: true
                    height: 40

                    topPadding: 10
                    bottomPadding: 10

                    contentItem: RowLayout {
                        spacing: 15

                        Image {
                            source: "image://icon/help-about"
                            sourceSize.width: 22
                            sourceSize.height: 22
                            Layout.leftMargin: 5
                        }

                        Text {
                            text: qsTr("About")
                            color: palette.text
                            Layout.fillWidth: true
                        }
                    }

                    onClicked: {
                        aboutDialog.open()
                    }
                }
            }
        }

        Rectangle {
            width: 1
            Layout.fillHeight: true
            color: palette.mid
            z: 1
        }

        StackView {
            id: contentStack
            Layout.fillWidth: true
            Layout.fillHeight: true
            initialItem: downloadPage
            clip: true
        }
    }
}
