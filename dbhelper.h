#ifndef DBHELPER_H
#define DBHELPER_H

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlDriver>

class DBHelper
{
public:
    enum Role{
        administrator, employee, owner
    };
public:
    DBHelper();
    bool open();
    void close();
    QSqlQuery getQuery();
    bool addUser(QString name, Role role, QString phone, QString password, QString homeAddress);
private:
    QSqlDatabase db;
    QSqlQuery query;
};

#endif // DBHELPER_H
