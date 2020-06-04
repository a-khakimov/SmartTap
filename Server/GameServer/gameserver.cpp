#include "gameserver.h"
#include "client.h"
#include <QDebug>


GameServer::GameServer(QObject *parent)
    : QTcpServer(parent)
{

}

GameServer::~GameServer()
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
    Client* client = new Client(this);
    client->setSocket(handle);
}
