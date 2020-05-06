import QtQuick 2.0
import QtQuick.Controls 2.5
import GameBoardModel 1.0;

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

        _scoreA.score = _gameBoard.model.scoreA
        _scoreB.score = _gameBoard.model.scoreB

        if (_gameBoard.model.isEndGame) {
            _gameBoard.visible = false
            _endGameText.text = "Game over"
            _endGameText.visible = true
            _restartButton.visible = true
        }
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

            Tile {
                displayText: value
                anchors.fill: _backgroundDelegate
                anchors.margins: 4
                color: isActive ? "ivory" : "beige"

                // TODO: animate it
                visible: !isRemoved

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        move(index);
                    }
                }
            }
        }
    }

    Text {
        id: _endGameText
        visible: false
        font.bold: true
        font.pointSize: 20
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Button {
        id: _restartButton
        text: "Restart"
        visible: false
        anchors.margins: 10
        anchors.top: _endGameText.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {
            _gameBoard.visible = true
            _gameBoard.model.boardInit(5)
            _restartButton.visible = false
            _endGameText.visible = false
            _scoreA.score = 0
            _scoreB.score = 0
        }
    }

    Button {
        id: _backButton
        text: "Menu"
        visible: true
        anchors.margins: 30
        anchors.top: _gameBoard.bottom
        anchors.horizontalCenter: parent.horizontalCenter
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
        font.pointSize: _gameBoard.width / 20
    }

    Score {
        id: _scoreB
        score: _gameBoard.model.scoreB
        anchors.bottom: _gameBoard.top
        anchors.right: _gameBoard.right
        anchors.margins: 20
        font.pointSize: _gameBoard.width / 20
    }
}
