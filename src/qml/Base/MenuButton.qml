import QtQuick 2.0
import StyleSettings 1.0

Rectangle {
    id: root
    color: Style.menuButtonRectColor
    anchors.margins: root.height / 10
    radius: 10
    border {
        width: root.width / 50
        color: Style.menuButtonBorderColor
    }

    property string displayText: ""
    signal clicked()

    Text {
        id: _text
        anchors.centerIn: root
        text: qsTr(displayText)
        font.pointSize: root.width / 15
        font.bold: false
        font.family: GlobalFont.name
        color: Style.menuButtonFontColor
    }

    MouseArea {
        anchors.fill: parent
        onPressed: root.state = "pressed"
        onReleased: root.state = "released"
        onClicked: root.clicked()
    }

    states: [
        State {
            name: "released"
            PropertyChanges {
                target: root.border
                color: Style.menuButtonBorderColor
            }
        },
        State {
            name: "pressed"
            PropertyChanges {
                target: root.border
                color: Style.menuButtonPressedBorderColor
            }
        }
    ]
}
