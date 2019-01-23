#include "employeeattendencewidget.h"
#include <QFont>
#include <QDate>
#include <QMessageBox>
#include <QDebug>
#include "dbhelper.h"

EmployeeAttendenceWidget::EmployeeAttendenceWidget(QWidget *parent) : QWidget(parent)
{
    QFont font;
    font.setPointSize(18);

    tableView.setModel(&queryModel);
    layout.addWidget(&tableView);

    pushButton_signIn.setText(QString("今日签到"));
    pushButton_signIn.setFont(font);
    connect(&pushButton_signIn, SIGNAL(clicked(bool)), this, SLOT(slot_signIn()));
    pushButton_query.setText(QString("查询我的本月出勤"));
    pushButton_query.setFont(font);
    connect(&pushButton_query, SIGNAL(clicked(bool)), this, SLOT(slot_query()));
    hBoxLayout.addStretch();
    hBoxLayout.addWidget(&pushButton_signIn);
    hBoxLayout.addWidget(&pushButton_query);
    layout.addLayout(&hBoxLayout);

    setLayout(&layout);
}

void EmployeeAttendenceWidget::setUserId(int userID)
{
    this->userId = userID;
}

void EmployeeAttendenceWidget::slot_signIn()
{
    DBHelper db;
    if (!db.open()){
        qDebug() << "数据库打开失败 EmployeeAttendenceWidget::slot_signIn()";
        return;
    }
    QSqlQuery query = db.getQuery();
    QString sql = "update attendencerecond set status = 0 where employeeId = "
            + QString::number(this->userId) +
            " and attendentDate = '" + QDate::currentDate().toString("yyyy-MM-dd") + "'";
    qDebug() << sql;
    if (!query.exec(sql)){
        qDebug() << "执行失败  EmployeeAttendenceWidget::slot_signIn()";
        db.close();
        return;
    }
    QMessageBox::information(this, QString("签到"), QString("签到成功。"), QMessageBox::Ok);
}

void EmployeeAttendenceWidget::slot_query()
{
    QString sql = "select id as 'ID', employeeId as '员工ID', name as '姓名', "
                  "attendentDate as '日期', status as '状态' from attendencerecond where "
                  "employeeId = "
                  + QString::number(this->userId);
    qDebug() << sql;
    queryModel.setQuery(sql);
}
