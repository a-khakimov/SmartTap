#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QThreadPool>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject* parent = nullptr);
    void setSocket(qintptr handle);

public slots:
    void connected();
    void disconnected();
    void readyRead();
    void taskResult(int number);

private:
    QTcpSocket* socket;
};

#endif // TCPCLIENT_H
