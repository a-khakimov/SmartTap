import QtQuick 2.0
import StyleSettings 1.0

Rectangle {
    id: root
    color: Style.themeButtonRectColor
    anchors.margins: root.height / 10
    radius: 5
    border {
        width: root.width / 15
        color: Style.themeButtonBorderColor
    }

    signal dark()
    signal light()

    Text {
        id: _text
        anchors.centerIn: root
        text: "⬓"
        font.pointSize: root.width / 2
        font.bold: false
        color: Style.themeButtonFontColor
    }

    MouseArea {
        anchors.fill: parent
        onPressed: {
            root.border.color = Style.themeButtonPressedBorderColor
        }
        onClicked: {
            if (_text.text == "⬓") {
                root.dark()
                _text.text = "⬒"
            } else {
                root.light()
                _text.text = "⬓"
            }
            root.border.color = Style.themeButtonBorderColor
        }
    }
}