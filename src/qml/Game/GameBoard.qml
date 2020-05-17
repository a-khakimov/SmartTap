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
    property int curTileIndex: 0
    signal back()

    function updateScores()
    {
        if (_scoreA.score != _gameBoard.model.scoreA)
            _scoreA.setScore(_gameBoard.model.scoreA)
        if (_scoreB.score != _gameBoard.model.scoreB)
            _scoreB.setScore(_gameBoard.model.scoreB)
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

    function getRandomInt(min, max) {
        min = Math.ceil(min);
        max = Math.floor(max);
        return Math.floor(Math.random() * (max - min + 1)) + min;
    }

    GridView {
        id: _gameBoard
        anchors.fill: parent
        cellWidth: root.width / _gameBoard.model.dimension
        cellHeight: root.height / _gameBoard.model.dimension
        focus: true

        model: GameBoardModel {
            id: _gameBoardModel
        }

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

        delegate: Item {
            id: _backgroundDelegate
            width: _gameBoard.cellWidth
            height: _gameBoard.cellHeight
            SequentialAnimation on y {
                id: _yAnim
                running: false
                NumberAnimation { from: y; to: root.height * 3; duration: 1000; easing.type: Easing.InCubic }
                NumberAnimation { from: root.height * 3; to: y; duration: 1000; easing.type: Easing.InCubic }
            }
            SequentialAnimation on rotation {
                id: _rotAnim
                running: false
                NumberAnimation { from: rotation; to: 360 * getRandomInt(-1, 1); duration: 1000; easing.type: Easing.InCubic }
            }

            Tile {
                id: _tile
                displayText: value
                anchors.fill: _backgroundDelegate
                anchors.margins: 4
                color: isActive ? Style.tileRectActiveColor : Style.tileRectColor

                SequentialAnimation on visible {
                    id: _visibleAnim
                    running: false
                    NumberAnimation { from: 1; to: 0; duration: 1500; easing.type: Easing.InCubic }
                }

                onClicked: {
                    if (gameMode == GameBoardModel.X2) {
                        if(_gameBoard.model.moveX2(index)) {
                            _visibleAnim.running = true
                            _rotAnim.running = true
                            _yAnim.running = true
                        }
                    } else if (gameMode == GameBoardModel.Ai) {
                        if (_aiCompleteMove == true) {
                            if(_gameBoard.model.moveX2(index)) {
                                _aiMoveTimer.start()
                                _aiCompleteMove = false
                                _visibleAnim.running = true
                                _rotAnim.running = true
                                _yAnim.running = true
                            }
                        }
                    }
                    root.updateScores()
                    root.checkGameState()
                }

                Connections {
                    target: _gameBoardModel
                    onAiMoveIndex: {
                        if (index == aiindex) {
                            _visibleAnim.running = true
                            _rotAnim.running = true
                            _yAnim.running = true
                        }
                    }
                    onResetBoard: {
                        _tile.visible = true
                    }
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
            _scoreA.setScore()
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
        anchors.left: _gameBoard.left
        font.pointSize: _gameBoard.width / 15
    }

    Score {
        id: _scoreB
        score: _gameBoard.model.scoreB
        anchors.right: _gameBoard.right
        font.pointSize: _gameBoard.width / 15
    }
}
