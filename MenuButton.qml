import QtQuick 2.0

Rectangle {
    id: root
    color: "cadetblue"
    property string displayText: ""
    anchors.margins: 10

    Text {
        id: _text
        anchors.centerIn: root
        text: qsTr(displayText)
        font.pointSize: root.width / 8
        font.bold: true
        color: "darkslategray"
    }

    border {
        width: 2
    }

    radius: 10
}
