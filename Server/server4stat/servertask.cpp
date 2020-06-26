#include "servertask.h"
#include "dbmanager.h"
#include "singleton.h"
#include <QDataStream>
#include <QDebug>

ServerTask::ServerTask()
{

}

ServerTask::ServerTask(const QHostAddress clientAddr, const tap::RequestHeader data, QObject *parent)
    : QObject {parent}, m_data {data}, m_clientAddr {clientAddr}
{

}

ServerTask::~ServerTask()
{

}

#include <QDataStream>

QDataStream& operator << (QDataStream &stream, const tap::StatisticsData &d)
{
    stream << static_cast<qint64>(d.timestamp)
           << static_cast<QString>(d.platform)
           << static_cast<QString>(d.ip);
    return stream;
}


void ServerTask::run()
{
    switch (m_data.id) {
    case tap::PlayerInfomationId: {
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

        DbManager* dbManager = Singleton<DbManager>::Instance();
        dbManager->saveStatInfo(
                    m_clientAddr.toString().toStdString(),
                    QDateTime::currentDateTime(), platform.toStdString());
        break;
    }
    case tap::StatisticsDataId: {
        DbManager* dbManager = Singleton<DbManager>::Instance();
        QVector<tap::StatisticsData> data = dbManager->getStatInfo();
        QByteArray bytes;
        QDataStream stream(&bytes, QIODevice::WriteOnly);
        stream << data;
        emit result(bytes);
        break;
    }
    default:
        break;
    }
}
