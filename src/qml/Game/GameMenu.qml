import QtQuick 2.0
import GameBoardModel 1.0;
import Base 1.0

Item {
    id: root
    anchors.fill: parent

    signal startX1()
    signal startX2()
    signal startMultiplayer()
    signal changeBoardSize()

    MenuButton {
        id: _startX1Button
        displayText: "Start x1"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: _startX2Button.top
        height: parent.height / 8
        width: height * 3
        onClicked: {
            root.startX1()
        }
    }

    MenuButton {
        id: _startX2Button
        displayText: "Start x2"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        height: parent.height / 8
        width: height * 3
        onClicked: {
            root.startX2()
        }
    }
    /*
    MenuButton {
        id: _multiplayerButton
        displayText: "Multiplayer"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: _startX2Button.bottom
        height: parent.height / 8
        width: height * 3
        onClicked: {
            root.startMultiplayer()
        }
    }
    */
    /*
    MenuButton {
        id: _boardSizeButton
        displayText: "Size: 5x5"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: _multiplayerButton.bottom
        height: parent.height / 6
        width: height * 3
        onClicked: {
            root.changeBoardSize()
        }
    }
    */
}
