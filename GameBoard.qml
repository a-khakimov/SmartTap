import QtQuick 2.0
import Game 1.0;

GridView {
    id: root
    model: GameBoardModel { }

    cellWidth: width / root.model.dimension
    cellHeight: height / root.model.dimension

    delegate: Item {
        id: _backgroundDelegate
        width: root.cellWidth
        height: root.cellHeight

        Tile {
            displayText: display.toString()
            anchors.fill: _backgroundDelegate
            anchors.margins: 5

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (root.model.remove(index))     {
                        parent.visible = false
                        _scoreA.text = root.model.scoreA()
                        _scoreB.text = root.model.scoreB()
                    }
                }
            }
        }
    }

    Text {
        id: _scoreA
        text: root.model.scoreA()
        anchors.top: root.bottom
        anchors.left: root.left
    }
    Text {
        id: _scoreB
        text: root.model.scoreB()
        anchors.top: root.bottom
        anchors.right: root.right
    }
}
