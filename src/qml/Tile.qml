import QtQuick 2.0

Rectangle {
    id: root
    color: "white"
    property string displayText: ""

    Text {
        id: _text
        anchors.centerIn: root

        text: qsTr(displayText)
        color: "black"

        FontLoader { id: _font; source: "qrc:/fonts/kongtext.ttf" }

        font.family: _font.name
        font.pointSize: root.width / 1.8
        //font.bold: true

    }

    border {
        width: root.width / 12
    }

    radius: 5
}
