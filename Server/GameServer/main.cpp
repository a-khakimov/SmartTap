#include <QCoreApplication>
#include "gameserver.h"
#include "singleton.h"

int main(int argc, char** argv)
{
    QCoreApplication a(argc, argv);

    DbManager* dbManager = Singleton<DbManager>::Instance();
    dbManager->connect("ainr", "pass", "huidb", "localhost");
    GameServer server;
    server.start();

    return a.exec();
}
