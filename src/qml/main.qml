import QtQuick 2.14
import QtQuick.Window 2.14
import GameBoardModel 1.0
import StyleSettings 1.0
import Game 1.0
import Base 1.0

Window {
    visible: true
    width: 1000
    height: 600
    minimumWidth: 400
    minimumHeight: 600
    title: qsTr("SmartTap")

    Rectangle {
        anchors.fill: parent
        color: Style.backgroundColor

        ThemeButton {
            id: _themeButton
            anchors.horizontalCenter: parent.horizontalCenter
            y : parent.height / 16
            height: parent.height / 10
            width: height
            onDark: Style.isDarkTheme = true
            onLight: Style.isDarkTheme = false
        }

        GameBoard {
            id: _gameBoard
            visible: false
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width / 4
            height: width
            onBack: {
                _gameBoard.visible = false
                _gameMenu.visible = true
            }
        }

        GameMenu {
            id: _gameMenu
            onStartX1: {
                _gameBoard.gameMode = GameBoardModel.Ai
                _gameBoard.visible = true
                _gameMenu.visible = false
            }
            onStartX2: {
                _gameBoard.gameMode = GameBoardModel.X2
                _gameBoard.visible = true
                _gameMenu.visible = false
            }
            onStartMultiplayer: {
                _gameBoard.gameMode = GameBoardModel.Multiplayer
                // TODO: Multiplayer
            }
            onChangeBoardSize: {
                // TODO: Resizing board
            }
        }
    }
}
