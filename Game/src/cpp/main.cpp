#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "gameboardmodel.h"

int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  engine.addImportPath(":/src/qml");
  GameBoardModel::declareQML();
  const QUrl url(QStringLiteral("qrc:/src/qml/main.qml"));
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
    &app, [url](QObject *obj, const QUrl &objUrl) {
      if (!obj && url == objUrl)
        QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
