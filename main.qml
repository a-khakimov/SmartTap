import QtQuick 2.14
import QtQuick.Window 2.14

Window {
    visible: true
    width: 400
    height: 500
    title: qsTr("SmartTap")

    Rectangle {
        anchors.fill: parent
        GameBoard {
            id: _gameBoard
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width
            height: width
        }
    }
}
