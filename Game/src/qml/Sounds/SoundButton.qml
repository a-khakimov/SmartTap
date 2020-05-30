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

    Text {
        id: _text
        anchors.centerIn: root
        text: "M"
        font.family: GlobalFont.name
        font.pointSize: root.width / 3
        font.bold: false
        color: Style.themeButtonFontColor
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onPressed: {
            root.border.color = Style.themeButtonPressedBorderColor
        }
        onClicked: {
            if (SoundManager.muted) {
                SoundManager.unmute()
            } else {
                SoundManager.mute()
            }
            root.border.color = Style.themeButtonBorderColor
        }
    }
    Component.onCompleted: {
        SoundManager.backgroundMusic.play()
    }
}
