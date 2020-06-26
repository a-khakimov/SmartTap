#include "dbmanager.h"
#include <memory>
#include "player-odb.hxx"
#include "player.hxx"
#include <odb/pgsql/database.hxx>
#include <QDebug>

DbManager::DbManager() : db {nullptr}
{

}

bool DbManager::connect(const std::string &user, const std::string &password, const std::string &database, const std::string &host)
{
    try {
        if (db == nullptr) {
            db = new odb::pgsql::database(user, password, database, host);
        }
    } catch (const odb::exception& e) {
        qDebug() << e.what();
        return false;
    }
    return true;
}

bool DbManager::saveStatInfo(
        const std::string& ip,
        const QDateTime datetime,
        const std::string& platform)
{
    try {
        player p(ip, datetime, platform);
        odb::transaction transaction(db->begin());
        db->persist(p);
        transaction.commit();
    }
    catch (const odb::exception& e) {
        qDebug() << e.what();
        return false;
    }
    return true;
}

QVector<tap::StatisticsData> DbManager::getStatInfo()
{
    QVector<tap::StatisticsData> stat;
    try {
        odb::transaction t (db->begin());
        odb::result<player> r(db->query<player>(/* odb::query<player>::timestamp condition*/));
        for (auto i = r.begin(); i != r.end(); i++) {
            //qDebug() << (*i).ip().c_str() << (*i).datetime() << (*i).platform().c_str();
            tap::StatisticsData data {
                (*i).datetime().toMSecsSinceEpoch(),
                (*i).platform().c_str(),
                (*i).ip().c_str()
            };
            stat.push_back(data);
        }
        t.commit();
    }
    catch (const odb::exception& e) {
        qDebug() << e.what();
    }
    return  stat;
}

DbManager::~DbManager()
{
    delete db;
    db = nullptr;
}
