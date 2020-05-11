import QtQuick 2.0
import QtQuick.Controls 2.5
import GameBoardModel 1.0
import StyleSettings 1.0
import Base 1.0

Item {
    id: root
    property int gameMode: GameBoardModel.X2
    property bool _aiCompleteMove: true
    property alias gameBoard: _gameBoard
    signal back()

    Timer {
        id: _aiMoveTimer
        interval: 1000;
        running: false;
        repeat: false
        onTriggered: {
            _gameBoard.model.moveAI()
            _aiCompleteMove = true
            root.updateScores()
            root.checkGameState()
        }
    }

    function updateScores()
    {
        _scoreA.score = _gameBoard.model.scoreA
        _scoreB.score = _gameBoard.model.scoreB
    }

    function checkGameState()
    {
        if (_gameBoard.model.isEndGame) {
            _gameBoard.visible = false
            _endGameText.text = "Game over"
            _endGameText.visible = true
            _restartButton.visible = true
        }
    }

    function move(index)
    {
        if (gameMode == GameBoardModel.X2) {
            _gameBoard.model.moveX2(index)
        } else if (gameMode == GameBoardModel.Ai) {
            if (_aiCompleteMove) {
                if(_gameBoard.model.moveX2(index)) {
                    _aiMoveTimer.start()
                    _aiCompleteMove = false
                }
            }
        }
        root.updateScores()
        root.checkGameState()
    }

    GridView {
        id: _gameBoard

        model: GameBoardModel {
            id: _gameBoardModel
        }

        anchors.fill: parent
        cellWidth: root.width / _gameBoard.model.dimension
        cellHeight: root.height / _gameBoard.model.dimension

        delegate: Item {
            id: _backgroundDelegate
            width: _gameBoard.cellWidth
            height: _gameBoard.cellHeight
            onStateChanged: {
                console.log("Delegate item state changed")
            }

            Tile {
                displayText: value
                anchors.fill: _backgroundDelegate
                anchors.margins: 4
                color: isActive ? Style.tileRectActiveColor : Style.tileRectColor
                visible: !isRemoved // TODO: animate it
                onClicked: {
                    console.log("Delegate item clicked:", index)
                    move(index)
                }
            }
        }
    }

    Text {
        id: _endGameText
        visible: false
        color: Style.endGameTextColor
        font {
            family: GlobalFont.name
            bold: true
            pointSize: 20
        }
        anchors {
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
        }
    }

    MenuButton {
        id: _restartButton
        displayText: "Restart"
        visible: false
        anchors.margins: 10
        anchors.top: _endGameText.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        height: parent.height / 6
        width: height * 4
        onClicked: {
            _gameBoard.visible = true
            _gameBoard.model.boardInit(5)
            _restartButton.visible = false
            _endGameText.visible = false
            _scoreA.score = 0
            _scoreB.score = 0
        }
    }

    MenuButton {
        id: _backButton
        displayText: "Menu"
        anchors.margins: 80
        anchors.top: _gameBoard.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        height: parent.height / 6
        width: height * 4
        onClicked: {
            _gameBoard.model.boardInit(5)
            _scoreA.score = 0
            _scoreB.score = 0
            root.back()
        }
    }

    Score {
        id: _scoreA
        score: _gameBoard.model.scoreA
        anchors.bottom: _gameBoard.top
        anchors.left: _gameBoard.left
        anchors.margins: 20
        font.pointSize: _gameBoard.width / 15
    }

    Score {
        id: _scoreB
        score: _gameBoard.model.scoreB
        anchors.bottom: _gameBoard.top
        anchors.right: _gameBoard.right
        anchors.margins: 20
        font.pointSize: _gameBoard.width / 15
    }
}
