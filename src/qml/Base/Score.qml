import QtQuick 2.0
import StyleSettings 1.0

Text {
    property string score: "0"
    text: score
    font.family: GlobalFont.name
    font.bold: true
    color: Style.scoreColor
}
