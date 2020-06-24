#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <memory>
#include <odb/database.hxx>
#include <QDateTime>

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

    virtual ~DbManager();

private:
    odb::database* db;
};

#endif // DBMANAGER_H
