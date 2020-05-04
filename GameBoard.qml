import QtQuick 2.0
import Game 1.0;

Rectangle {
    id: root
    color: "#F1F1F1"

    GridView {
        id: _gameBoard
        model: GameBoardModel { }

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
                anchors.margins: 5
                color: isActive ? "ivory" : "beige"

                // TODO: animate it
                visible: !isRemoved

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        _gameBoard.model.move(index)
                        _scoreA.score = _gameBoard.model.scoreA
                        _scoreB.score = _gameBoard.model.scoreB
                        if (_gameBoard.model.isEndGame) {
                            _gameBoard.visible = false
                        }
                    }
                }
            }
        }
    }
    Score {
        id: _scoreA
        score: _gameBoard.model.scoreA
        anchors.bottom: _gameBoard.top
        anchors.left: _gameBoard.left
        font.pointSize: _gameBoard.width / 20
    }
    Score {
        id: _scoreB
        score: _gameBoard.model.scoreB
        anchors.bottom: _gameBoard.top
        anchors.right: _gameBoard.right
        font.pointSize: _gameBoard.width / 20
    }
}
