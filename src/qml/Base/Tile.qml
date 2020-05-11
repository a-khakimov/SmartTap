import QtQuick 2.0
import StyleSettings 1.0

Rectangle {
    id: root
    color: Style.tileRectColor
    radius: 5
    border {
        width: root.width / 12
        color: Style.tileBorderColor
    }

    signal clicked()
    property string displayText: ""

    function setState(s)
    {
        console.log("tile:", s)
        if (s === "active") {
            root.state = "active"
        } else {
            root.state = "inactive"
        }
    }

    Text {
        id: _text
        anchors.centerIn: root
        text: qsTr(displayText)
        color: Style.tileFontColor
        font.family: GlobalFont.name
        font.pointSize: root.width / 1.8
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.clicked()
        }
    }

    states: [
        State {
            name: "inactive"
            PropertyChanges {
                target: root
                color: Style.tileRectColor
            }
        },
        State {
            name: "active"
            PropertyChanges {
                target: root
                color: Style.tileRectActiveColor
            }
        },
        State {
            name: "removed"
            PropertyChanges {
                target: root
                // TODO
            }
        }
    ]
}
