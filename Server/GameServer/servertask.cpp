#include "servertask.h"
#include <QDebug>

ServerTask::ServerTask()
{

}

ServerTask::ServerTask(const tap::StatisticsData data, QObject *parent)
    : QObject {parent}, m_data {data}
{

}

ServerTask::~ServerTask()
{

}

void ServerTask::run()
{
    qDebug() << "id:" << QString::number(m_data.id, 16);
    qDebug() << "platform:" << m_data.platform;
    emit result(1);
}
