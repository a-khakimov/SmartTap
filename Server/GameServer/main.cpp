#include <QCoreApplication>
#include "gameserver.h"

int main(int argc, char** argv)
{
    QCoreApplication a(argc, argv);

    GameServer server;
    server.start();

    return a.exec();
}
