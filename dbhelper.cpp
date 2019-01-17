#include "dbhelper.h"

DBHelper::DBHelper()
{

}

bool DBHelper::open()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    //db.setPort(3306);
    db.setDatabaseName("SmartCommunity");
    db.setUserName("root");
    db.setPassword("");
    if (db.open()){
        query = QSqlQuery(db);
        return true;
    }
    return false;
}

void DBHelper::close()
{
    db.close();
}

QSqlQuery DBHelper::getQuery()
{
    return query;
}
