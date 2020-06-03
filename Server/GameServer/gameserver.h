#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>

class GameServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit GameServer(QObject* parent = nullptr);
    virtual ~GameServer();
    void start();

protected:
    void incomingConnection(qintptr handle) override;
};

#endif // GAMESERVER_H
