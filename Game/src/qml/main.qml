import QtQuick.Window 2.12
import QtQuick 2.12
import QtMultimedia 5.12
import QtQuick.Controls 2.5
import GameBoardModel 1.0
import StyleSettings 1.0
import Sounds 1.0
import Game 1.0
import Base 1.0

ApplicationWindow {
    visible: true
    width: 1000
    height: 600
    //visibility: "FullScreen"
    title: qsTr("SmartTap")

    Rectangle {
        anchors.fill: parent
        color: Style.backgroundColor

        Item {
            id: _optButtons
            anchors.horizontalCenter: parent.horizontalCenter
            y : parent.height / 16
            height: parent.height / 13
            width: height * 3
            /*
            ThemeButton {
                id: _themeButton
                height: parent.height
                width: height
                anchors.left: parent.left
                anchors.top: parent.top
                onDark: Style.isDarkTheme = true
                onLight: Style.isDarkTheme = false
            }
            */

            SoundButton {
                id: _soundButton
                anchors.top: parent.top
                //anchors.right: parent.right
                anchors.horizontalCenter: parent.horizontalCenter
                width: height
                height: parent.height
            }
        }

        GameBoard {
            id: _gameBoard
            visible: false
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            width: (parent.width > parent.height ? (parent.width / 4) : parent.width)
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
