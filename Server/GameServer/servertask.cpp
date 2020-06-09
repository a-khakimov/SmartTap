#include "servertask.h"
#include "dbmanager.h"
#include "singleton.h"
#include <QDebug>

ServerTask::ServerTask()
{

}

ServerTask::ServerTask(const QHostAddress clientAddr, const tap::StatisticsData data, QObject *parent)
    : QObject {parent}, m_data {data}, m_clientAddr {clientAddr}
{

}

ServerTask::~ServerTask()
{

}

void ServerTask::run()
{
    if (m_data.id != tap::StatisticsDataId) {
        emit result(1);
    } else {
        QString platform;
        switch (m_data.platform) {
        case tap::_ios:
            platform = "ios";
            break;
        case tap::_linux:
            platform = "linux";
            break;
        case tap::_webasm:
            platform = "webasm";
            break;
        case tap::_android:
            platform = "android";
            break;
        case tap::_windows:
            platform = "windows";
            break;
        default:
            break;
        }
        qDebug() << "Client: " << m_clientAddr.toString() <<  " platform:" << platform;

        DbManager* dbManager = Singleton<DbManager>::Instance();
        dbManager->saveStatInfo(
                    m_clientAddr.toString().toStdString(),
                    QDateTime::currentDateTime().toSecsSinceEpoch(),
                    platform.toStdString());
        emit result(0);
    }
}
