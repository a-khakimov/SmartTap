#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QThreadPool>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject* parent = nullptr);
    virtual ~Client();
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
