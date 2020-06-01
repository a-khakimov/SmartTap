#include "gameserver.h"
#include "tcpclient.h"
#include <QDebug>

GameServer::GameServer(QObject *parent)
{

}

void GameServer::start()
{
    if (listen(QHostAddress::Any, 4040)) {
        qDebug() << "start server...";
    } else {
        qDebug() << "server is not started!";
    }
}

void GameServer::incomingConnection(qintptr handle)
{
    TcpClient* client = new TcpClient(this);
    client->setSocket(handle);
}
