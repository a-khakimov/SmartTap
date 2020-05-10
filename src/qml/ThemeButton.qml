import QtQuick 2.0

Rectangle {
    id: root
    color: "white"
    anchors.margins: root.height / 10

    signal dark()
    signal light()

    Text {
        id: _text
        anchors.centerIn: root
        text: "⬓"
        font.pointSize: root.width / 2
        font.bold: false
        color: "#555555"
    }

    MouseArea {
        anchors.fill: parent
        onPressed: root.border.color = "darkslategrey"
        onReleased: root.border.color = "#555555"
        onClicked: {
            if (_text.text == "⬓") {
                root.dark()
                _text.text = "⬒"
            } else {
                root.light()
                _text.text = "⬓"
            }
        }
    }

    border {
        width: root.width / 15
        color: "#555555"
    }

    radius: 5
}
