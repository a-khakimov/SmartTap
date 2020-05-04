import QtQuick 2.14
import QtQuick.Window 2.14

Window {
    visible: true
    width: 400
    height: 600
    minimumWidth: 400
    minimumHeight: 600
    title: qsTr("SmartTap")

    Rectangle {
        anchors.fill: parent
        GameBoard {
            id: _gameBoard
            visible: false
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width
            height: width

            onBack: {
                _gameBoard.visible = false
                _gameMenu.visible = true
            }
        }

        GameMenu {
            id: _gameMenu
            onStartX1: {
                // TODO: AI
            }
            onStartX2: {
                _gameBoard.visible = true
                _gameMenu.visible = false
            }
            onStartMultiplayer: {
                // TODO: Multiplayer
            }
            onChangeBoardSize: {

            }
        }
    }
}
