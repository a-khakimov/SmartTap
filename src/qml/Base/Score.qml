import QtQuick 2.0
import StyleSettings 1.0

Text {
    property string score: "0"
    text: score
    font.family: GlobalFont.name
    font.bold: true
    anchors.bottom: parent.top
    anchors.margins: 20
    color: Style.scoreColor

    ColorAnimation on color {
        id: _colorAnim
        running: false
        from: Style.scoreAnimColor
        to: Style.scoreColor
        duration: 1000
    }

    function setScore(newScore) {
        score = newScore
        _colorAnim.running = true
    }
}
