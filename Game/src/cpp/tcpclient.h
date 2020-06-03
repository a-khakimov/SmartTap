#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    TcpClient(QObject *parent = nullptr, const QString& host = "localhost", const int port = 4040);
    virtual ~TcpClient();


signals:
    void isServerReply(QByteArray);
    void connected();

public slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError);
    bool sendToServer(void* data, const size_t size);
    void slotConnected();
    void tryConnectToServer(QString& host);

private:
    QTcpSocket* m_socket;
    quint16 m_nNextBlockSize;
    QString m_host;
    int m_port;
    bool isClientConnected;
};

#endif // TCPCLIENT_H
