pragma Singleton
import QtMultimedia 5.12
import QtQuick 2.12

Item {
    id: root

    property bool muted: false

    function mute() {
        muted = true
        _backgroundMusic.stop()
    }

    function unmute() {
        muted = false
        _backgroundMusic.play()
    }

    function touchSound() {
        if (!muted) _touchSound.play()
    }

    Audio {
        id: _touchSound
        source: "qrc:/sounds/touchsound.wav"
        autoLoad: true
        volume: 1
    }
    Audio {
        id: _backgroundMusic
        source: "qrc:/sounds/background.mp3"
        autoPlay: true
        autoLoad: true
        volume: 0.2
        loops: 1000
    }
}
