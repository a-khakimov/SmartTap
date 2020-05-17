pragma Singleton
import QtQuick 2.0

QtObject {
    property bool isDarkTheme: false

    readonly property color backgroundColor: isDarkTheme ? "#323232" : "#FFFFFF"
    readonly property color scoreColor: isDarkTheme ? "gainsboro" : "darkslategray"
    readonly property color scoreAnimColor: isDarkTheme ? "palegoldenrod" : "seagreen"
    readonly property color endGameTextColor: isDarkTheme ? "#EEEEEE" : "#555555"

    readonly property color tileRectColor: isDarkTheme ? "#888888" : "#AAAAAA"
    readonly property color tileRectActiveColor: isDarkTheme ? "#444444" : "#EEEEEE"
    readonly property color tileFontAnimColor: isDarkTheme ? "lightgrey" : "dimgray"
    readonly property color tileFontColor: isDarkTheme ? "#EEEEEE" : "#555555"
    readonly property color tileBorderColor: isDarkTheme ? "#AAAAAA" : "#555555"

    readonly property color themeButtonRectColor: isDarkTheme ? "#555555" : "#EEEEEE"
    readonly property color themeButtonFontColor: isDarkTheme ? "#EEEEEE" : "#555555"
    readonly property color themeButtonBorderColor: isDarkTheme ? "#AAAAAA" : "#555555"
    readonly property color themeButtonPressedBorderColor: isDarkTheme ? "#888888" : "#777777"

    readonly property color menuButtonRectColor: isDarkTheme ? "#555555" : "#EEEEEE"
    readonly property color menuButtonFontColor: isDarkTheme ? "#EEEEEE" : "#555555"
    readonly property color menuButtonBorderColor: isDarkTheme ? "#AAAAAA" : "#666666"
    readonly property color menuButtonPressedBorderColor: "#888888"
}
