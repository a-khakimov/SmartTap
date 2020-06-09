#include "client.h"
#include "servertask.h"
#include "data.h"
#include <QDebug>
#include <QHostAddress>

Client::Client(QObject *parent) : QObject(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(10);
}

Client::~Client()
{

}

void Client::setSocket(qintptr handle)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(handle);

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void Client::connected()
{
    qDebug() << "Client connected";
}

void Client::disconnected()
{
    qDebug() << "Client disconnected";
}

void Client::readyRead()
{
    if (socket->bytesAvailable() < (qint64)sizeof(tap::StatisticsData)) {
        return;
    }

    auto const buf = socket->read(sizeof(tap::StatisticsData));
    tap::StatisticsData data;
    memcpy(&data, buf.constData(), buf.size());

    ServerTask* task = new ServerTask(socket->peerAddress(), data, this);
    task->setAutoDelete(true);

    connect(task, SIGNAL(result(int)), this, SLOT(taskResult(int)), Qt::QueuedConnection);
    QThreadPool::globalInstance()->start(task);
}

void Client::taskResult(int number)
{
    QByteArray buf;
    buf.append("Result: ");
    buf.append(QString::number(number));
    socket->write(buf);
}
