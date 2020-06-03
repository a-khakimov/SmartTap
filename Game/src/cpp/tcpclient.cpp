#include "tcpclient.h"
#include <QDebug>

TcpClient::TcpClient(QObject *parent, const QString &host, const int port)
    : QObject(parent),  m_host{host}, m_port{port}
{
    m_socket = new QTcpSocket(this);
    tryConnectToServer(m_host);
}

TcpClient::~TcpClient()
{
    m_socket->close();
    delete m_socket;
}

void TcpClient::slotReadyRead()
{
    QByteArray data = m_socket->readAll();
    emit isServerReply(data);
}

void TcpClient::slotError(QAbstractSocket::SocketError err)
{
    switch (err) {
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "HostNotFoundError";
        break;
    case QAbstractSocket::RemoteHostClosedError:
        qDebug() << "RemoteHostClosedError";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "ConnectionRefusedError";
        break;
    default:
        qDebug() << "Unknown error";
        break;
    }

    isClientConnected = false;
}

bool TcpClient::sendToServer(void *data, const size_t size)
{
    bool result = false;
     const char* pData = static_cast<const char*>(data);

     if (!isClientConnected) {
         tryConnectToServer(m_host);
     }

     if (isClientConnected) {
         result = (m_socket->write(pData, size) == -1);
     }

     return result;
}

void TcpClient::slotConnected()
{
    qDebug() << "Connected to server";
    isClientConnected = true;
    emit connected();
}

void TcpClient::tryConnectToServer(QString &host)
{
    m_host = host;

    if (m_socket->isOpen()) {
        m_socket->close();
    }

    qDebug() << "Try to connect server: " << m_host << "::" << m_port;

    m_socket->connectToHost(m_host, m_port);
    connect(m_socket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_socket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
}
