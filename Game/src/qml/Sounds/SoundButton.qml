import QtQuick 2.0
import StyleSettings 1.0
import QtGraphicalEffects 1.15

Rectangle {
    id: root
    color: Style.themeButtonRectColor
    anchors.margins: root.height / 10
    radius: 10
    border {
        width: root.width / 13
        color: Style.themeButtonBorderColor
    }

    Image {
        id: _image
        anchors.fill: parent
        anchors.margins: 10
        source: "qrc:/imgs/soundon.png"
    }

    ColorOverlay {
        anchors.fill: _image
        source: _image
        color: "#88888888"
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
                _image.source = "qrc:/imgs/soundon.png"
            } else {
                SoundManager.mute()
                _image.source = "qrc:/imgs/soundoff.png"
            }
            root.border.color = Style.themeButtonBorderColor
        }
    }
    Component.onCompleted: {
        SoundManager.backgroundMusic.play()
    }
}
