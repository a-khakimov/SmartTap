import QtQuick 2.0

Text {
    FontLoader { id: _font; source: "qrc:/fonts/kongtext.ttf" }
    property string score: "0"
    text: score
    font.family: _font.name
    font.bold: true
    color: "darkslategray"
}
