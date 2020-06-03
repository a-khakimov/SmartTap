#include "dbmanager.h"

#include "player-odb.hxx"
#include "player.hxx"
#include <odb/pgsql/database.hxx>
#include <odb/database.hxx>
#include <QDebug>

DbManager::DbManager()
{
    try {
        std::auto_ptr<odb::database> db(new odb::pgsql::database("ainr", "pass", "huidb", "localhost"));

        player p("1.1.1.0", "today", "linux");


        odb::transaction t(db->begin());
        db->persist(p);
        t.commit();
    } catch (const odb::exception& e) {
        qDebug() << e.what();
    }
}

DbManager::~DbManager()
{

}
