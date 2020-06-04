#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <memory>
#include <odb/database.hxx>

class DbManager
{
public:
    DbManager();
    bool connect(const std::string& user,
                 const std::string& password,
                 const std::string& database,
                 const std::string& host);
    bool saveStatInfo(const std::string& ip, const std::string& date, const std::string& platform);
    virtual ~DbManager();

private:
    odb::database* db;
};

#endif // DBMANAGER_H
