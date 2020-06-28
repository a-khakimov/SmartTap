import QtQuick 2.0
import QtQuick.Controls 2.5
import GameBoardModel 1.0
import StyleSettings 1.0
import Sounds 1.0
import Base 1.0

Item {
    id: root
    property int gameMode: GameBoardModel.X2
    property bool _aiCompleteMove: true
    property alias gameBoard: _gameBoard
    property int curTileIndex: 0

    signal back()
    signal endGame()

    function reset() {
        _endGameText.visible = false
        _restartButton.visible = false
        _gameBoard.visible = true
    }

    function updateScores() {
        if (_scoreA.score != _gameBoard.model.scoreA)
            _scoreA.setScore(_gameBoard.model.scoreA)
        if (_scoreB.score != _gameBoard.model.scoreB)
            _scoreB.setScore(_gameBoard.model.scoreB)
    }

    function checkGameState() {
        if (_gameBoard.model.isEndGame) {
            endGame() // signal
            _endGameTextAnim.running = true
            _restartButtonAnimVisible.running = true
            _restartButtonYPosAnim.running = true
            _gameBoardAnim.running = true
            _endGameText.text = "Game over"
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

        model: GameBoardModel {
            id: _gameBoardModel
        }

        NumberAnimation on visible {
            id: _gameBoardAnim
            running: false
            from: 1; to: 0
            duration: 1000;
            easing.type: Easing.InCubic
        }

        Timer {
            id: _aiMoveTimer
            interval: 1000;
            running: false;
            repeat: false
            onTriggered: {
                _gameBoard.model.moveAI()
                SoundManager.touchSound()
                root.updateScores()
                root.checkGameState()
                _aiCompleteMove = true
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

            NumberAnimation on rotation {
                id: _rotAnim
                running: false
                from: rotation
                to: 360 * (getRandomInt(0, 1) ? 1 : -1)
                duration: 1000
                easing.type: Easing.InCubic
            }

            Tile {
                id: _tile
                displayText: value
                anchors.fill: _backgroundDelegate
                anchors.margins: 4
                color: isActive ? Style.tileRectActiveColor : Style.tileRectColor

                NumberAnimation on visible {
                    id: _visibleAnim
                    running: false
                    from: 1; to: 0;
                    duration: 1500;
                    easing.type: Easing.InCubic
                }

                onClicked: {
                    function start_animation() {
                        _visibleAnim.running = true
                        _rotAnim.running = true
                        _yAnim.running = true
                    }
                    if (gameMode == GameBoardModel.X2 && _gameBoard.model.moveX2(index)) {
                        start_animation()
                        root.updateScores()
                        root.checkGameState()
                    } else if (gameMode == GameBoardModel.Ai) {
                        if (_aiCompleteMove == true && _gameBoard.model.moveX2(index)) {
                            _aiMoveTimer.start()
                            _aiCompleteMove = false
                            start_animation()
                            root.updateScores()
                        }
                    }
                }

                Connections {
                    target: _gameBoardModel
                    function onResetBoard() {
                        _tile.visible = true
                    }
                    function onAiMoveIndex(aiindex) {
                        if (index === aiindex) {
                            _visibleAnim.running = true
                            _rotAnim.running = true
                            _yAnim.running = true
                        }
                    }
                }
                Connections {
                    target: root
                    function onEndGame() {
                        if (!_gameBoard.model.isTileRemoved(index)) {
                            _visibleAnim.running = true
                            _rotAnim.running = true
                            _yAnim.running = true
                        }
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
        ParallelAnimation {
            id: _endGameTextAnim
            running: false
            NumberAnimation {
                target: _endGameText
                property: "visible"
                from: 0; to: 1
                duration: 1000
                easing.type: Easing.InCubic
            }
        }
    }

    MenuButton {
        id: _backButton
        displayText: "Menu"
        anchors.margins: 50
        anchors.top: root.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        height: parent.height / 8
        width: height * 4
        onClicked: {
            _gameBoard.model.boardInit(6)
            _scoreA.setScore(0)
            _scoreB.setScore(0)
            root.back()
            reset()
        }
    }

    MenuButton {
        id: _restartButton
        displayText: "Restart"
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        height: parent.height / 8
        width: height * 4
        y: _backButton.y
        onClicked: {
            _restartButtonY2PosAnim.running = true
            _restartButtonAnimUnVisible.running = true
            _gameBoard.model.boardInit(6)
            _gameBoard.visible = true
            _endGameText.visible = false
            _scoreA.setScore(0)
            _scoreB.setScore(0)
        }
        NumberAnimation on visible {
            id: _restartButtonAnimVisible
            running: false
            from: 0; to: 1;
            duration: 1200;
            easing.type: Easing.InCubic
        }
        NumberAnimation on visible {
            id: _restartButtonAnimUnVisible
            running: false
            from: 1; to: 0;
            duration: 120;
            easing.type: Easing.InCubic
        }
        NumberAnimation on y {
            id: _restartButtonYPosAnim
            from: _backButton.y;
            to: _backButton.y - _backButton.height * 1.5;
            running: false
            duration: 1000;
            easing.type: Easing.InCubic
        }
        NumberAnimation on y {
            id: _restartButtonY2PosAnim
            from: _backButton.y - _backButton.height * 1.5;
            to: _backButton.y;
            running: false
            duration: 500;
            easing.type: Easing.OutCubic
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
