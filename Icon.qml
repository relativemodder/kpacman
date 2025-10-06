import QtQuick
import QtQuick.Controls

Image {
    property string name
    source: name ? "image://icon/" + name : ""
    sourceSize.width: width
    sourceSize.height: height
}
