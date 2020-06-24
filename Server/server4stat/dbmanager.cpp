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

DbManager::~DbManager()
{
    delete db;
    db = nullptr;
}
