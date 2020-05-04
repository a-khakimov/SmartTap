import QtQuick 2.0

Rectangle {
    id: root
    //color: "gainsboro"
    color: "whitesmoke"
    property string displayText: ""

    Text {
        id: _text
        anchors.centerIn: root
        text: qsTr(displayText)
        font.pointSize: root.width / 3
        font.bold: true
        color: "darkslategray"
    }

    border {
        width: 2
    }

    radius: 10
}
