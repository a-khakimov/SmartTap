#include "tcpclient.h"
#include "servertask.h"
#include <QDebug>

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(10);
}

void TcpClient::setSocket(qintptr handle)
{
    socket = new QTcpSocket(this);
    qDebug() << "new socket created";

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    socket->setSocketDescriptor(handle);
    qDebug() << "new socket descriptor " << handle;
}

void TcpClient::connected()
{
    qDebug() << "client connected";
}

void TcpClient::disconnected()
{
    qDebug() << "client disconnected";
}

void TcpClient::readyRead()
{
    qDebug() << "client ready read";
    qDebug() << socket->readAll();

    ServerTask* task = new ServerTask();
    task->setAutoDelete(true);

    connect(task, SIGNAL(result(int)), this, SLOT(taskResult(int)), Qt::QueuedConnection);
    QThreadPool::globalInstance()->start(task);
}

void TcpClient::taskResult(int number)
{
    QByteArray buf;
    buf.append("Result: ");
    buf.append(QString::number(number));
    socket->write(buf);
}
