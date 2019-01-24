#include <QApplication>
#include <QTextCodec>
#include <QDebug>
#include <QDate>
#include <vector>
#include "dbhelper.h"
#include "mainwindow.h"
#include "loginview.h"

void init_database()
{
    DBHelper db;
    if (!db.open()){
        qDebug() << "数据库打开失败 main::init_database()";
        exit(1);
    }
    QSqlQuery query = db.getQuery();
    //清除非本月出勤记录
    QDate currentDate = QDate::currentDate();
    QString sql = "select * from attendencerecond";
    qDebug() << sql;
    if (!query.exec(sql)){
         qDebug() << "执行失败 main::init_database() 1";
    }
    std::vector<int> ids;
    bool hasCurrentMonthRecond = false;
    while (query.next()){
        QDate date = query.value(3).toDate();
        int id = query.value(0).toInt();
        if (!(currentDate.year() == date.year()
              && currentDate.month() == date.month())){
            ids.push_back(id);
        }else{
            hasCurrentMonthRecond = true;
        }
    }
    qDebug() << "init_database() 1";
    int n = ids.size();
    for (int i=0; i<n; i++){
        sql = "delete from attendencerecond where id = " + QString::number(ids[i]);
        qDebug() <<sql;
        if (!query.exec(sql)){
            qDebug() << "执行失败  main::init_database() 2";
            db.close();
            exit(1);
        }
    }
    qDebug() << "init_database() 2";

    //添加本月记录
    if (!hasCurrentMonthRecond){
        //查询所有员工
        std::vector<int> employeeIds;
        std::vector<QString> employeeNames;
        if (!query.exec("select id, name from user_employee")){
            qDebug() << "执行失败 main::init_database() 3";
            exit(1);
        }
        while (query.next()){
            employeeIds.push_back(query.value(0).toInt());
            employeeNames.push_back(query.value(1).toString());
        }
        qDebug() << "init_database() 3";
        //添加记录
        int day = 1;
        QDate date;
        int year = currentDate.year();
        int month = currentDate.month();
        while (date.setDate(year, month, day)){
            int n = employeeIds.size();
            for (int i=0; i<n; i++){
                QString str = "insert into attendencerecond(employeeId, name, attendentDate, status) values("
                        + QString::number(employeeIds[i]) + ", "
                        + "'" + employeeNames[i] + "', "
                        + "'" + date.toString("yyyy-MM-dd") + "', "
                        + QString::number(2) + ")";
                qDebug() << str;
                if (!query.exec(str)){
                    qDebug() << "执行失败  main::init_database() 4";
                    exit(1);
                    db.close();
                    exit(1);
                }
            }
            day++;
        }
        qDebug() << "init_database() 5";

        //添加月初的物业费
        for (int i=0; i<n; i++){
            sql = "insert into costaccount(employeeId, type, cost, status) values("
                  + QString::number(employeeIds[i]) + ", '物业费', 500, '未缴费')";
            qDebug() << sql;
            if (!query.exec(sql)){
                qDebug() << "执行失败  main::init_database() 6";
                exit(1);
                db.close();
                exit(1);
            }
        }
    }

    db.close();
}

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    QApplication a(argc, argv);

    init_database();

    LoginView loginView;
    loginView.show();

    return a.exec();
}
