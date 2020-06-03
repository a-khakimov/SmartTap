#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include "dbmanager.h"

class GameServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit GameServer(QObject* parent = nullptr);
    virtual ~GameServer();
    void start();

protected:
    void incomingConnection(qintptr handle) override;

private:
    DbManager dbManager;
};

#endif // GAMESERVER_H
