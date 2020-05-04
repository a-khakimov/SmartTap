import QtQuick 2.0
import Game 1.0;

Rectangle {
    id: root
    anchors.fill: parent

    signal startX1()
    signal startX2()
    signal startMultiplayer()
    signal changeBoardSize()

    MenuButton {
        id: _themeButton
        displayText: "Theme"
        anchors.horizontalCenter: parent.horizontalCenter
        y : parent.height / 16
        height: parent.height / 6
        width: height * 3
        MouseArea {
            anchors.fill: parent
            onClicked: {

            }
        }
    }

    MenuButton {
        id: _startX1Button
        displayText: "Start x1"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: _themeButton.bottom
        height: parent.height / 6
        width: height * 3
        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.startX1()
            }
        }
    }

    MenuButton {
        id: _startX2Button
        displayText: "Start x2"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: _startX1Button.bottom
        height: parent.height / 6
        width: height * 3
        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.startX2()
            }
        }
    }

    MenuButton {
        id: _multiplayerButton
        displayText: "Multiplayer"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: _startX2Button.bottom
        height: parent.height / 6
        width: height * 3
        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.startMultiplayer()
            }
        }
    }
    MenuButton {
        id: _boardSizeButton
        displayText: "Size: 5x5"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: _multiplayerButton.bottom
        height: parent.height / 6
        width: height * 3
        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.changeBoardSize()
            }
        }
    }
}
