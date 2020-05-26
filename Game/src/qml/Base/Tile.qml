import QtQuick 2.0
import StyleSettings 1.0

Rectangle {
    id: root
    color: Style.tileRectColor
    radius: 5
    border {
        width: root.width / 12
        color: Style.tileBorderColor
    }

    signal clicked()
    property string displayText: ""

    Text {
        id: _text
        anchors.centerIn: root
        text: qsTr(displayText)
        color: Style.tileFontColor
        font.family: GlobalFont.name
        font.pointSize: root.width / 1.8

        ColorAnimation on color {
            id: _tileColorAnim
            running: false
            from: Style.tileFontAnimColor
            to: Style.tileFontColor
            duration: 700
        }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onClicked: root.clicked()
        onEntered: _tileColorAnim.running = true
    }
}
