#include "servertask.h"
#include <QDebug>

ServerTask::ServerTask()
{

}

void ServerTask::run()
{
    qDebug() << "task run";
    emit result(1);
}
