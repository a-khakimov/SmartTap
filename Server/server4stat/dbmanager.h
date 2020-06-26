#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <memory>
#include <odb/database.hxx>
#include <QDateTime>
#include "data.h"

class DbManager
{
public:
    DbManager();
    bool connect(const std::string& user,
                 const std::string& password,
                 const std::string& database,
                 const std::string& host);

    bool saveStatInfo(
            const std::string& ip,
            const QDateTime dt,
            const std::string& platform);

    QVector<tap::StatisticsData> getStatInfo();

    virtual ~DbManager();

private:
    odb::database* db;
};

#endif // DBMANAGER_H
