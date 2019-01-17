#ifndef DBHELPER_H
#define DBHELPER_H

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlDriver>

class DBHelper
{
public:
    DBHelper();
    bool open();
    void close();
    QSqlQuery getQuery();
public:
    enum Role{
        administrator, employee, owner
    };
private:
    QSqlDatabase db;
    QSqlQuery query;
};

#endif // DBHELPER_H