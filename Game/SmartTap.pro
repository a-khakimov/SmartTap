QT += quick

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#QMAKE_CXXFLAGS += -ggdb

SOURCES += \
        src/cpp/ai.cpp \
        src/cpp/gameboardmodel.cpp \
        src/cpp/gamelogic.cpp \
        src/cpp/main.cpp \
        src/cpp/statistics.cpp \
        src/cpp/tcpclient.cpp

RESOURCES += qml.qrc

QMAKE_CXXFLAGS += -Wl,--heap,10000000

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += ../Server/server4stat/common/

HEADERS += \
    src/cpp/ai.h \
    src/cpp/gameboardmodel.h \
    src/cpp/gamelogic.h \
    src/cpp/statistics.h \
    src/cpp/tile.h \
    src/cpp/tcpclient.h

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml
android: include(/home/ainr/Android/Sdk/android_openssl/openssl.pri)

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
