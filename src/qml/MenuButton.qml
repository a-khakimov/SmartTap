import QtQuick 2.0

Rectangle {
    id: root
    color: "white"
    property string displayText: ""
    anchors.margins: root.height / 10

    signal clicked()

    FontLoader { id: _font; source: "qrc:/fonts/kongtext.ttf" }

    Text {
        id: _text
        anchors.centerIn: root
        text: qsTr(displayText)
        font.pointSize: root.width / 15
        font.bold: false
        font.family: _font.name
        color: "black"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
        onPressed: root.border.color = "darkslategray"
        onReleased: root.border.color = "black"
    }

    border.width: root.width / 50
    radius: 10
}
