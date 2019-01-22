#include "attendenceview.h"
#include <QFont>
#include <QDebug>
#include <QMessageBox>
#include <QDate>
#include <vector>
#include "dbhelper.h"

AttendenceView::AttendenceView(QWidget *parent) : QWidget(parent)
{
    QFont font;
    font.setPixelSize(18);

    label_condition.setFont(font);
    label_condition.setText(QString("筛选条件"));
    leftVBoxLayout.addWidget(&label_condition);

    label_name.setFont(font);
    label_name.setText(QString("姓名:"));
    lineEdit_name.setFont(font);
    leftHBoxLayout[0].addWidget(&label_name);
    leftHBoxLayout[0].addWidget(&lineEdit_name);
    leftVBoxLayout.addLayout(&leftHBoxLayout[0]);

    leftHBoxLayout[1].addStretch();
    pushButton_query.setFont(font);
    pushButton_query.setText(QString("看出勤"));
    connect(&pushButton_query, SIGNAL(clicked(bool)), this, SLOT(slot_query()));
    leftHBoxLayout[1].addWidget(&pushButton_query);
    leftVBoxLayout.addLayout(&leftHBoxLayout[1]);

    /*label_description.setFont(font);
    label_description.setFixedSize(this->width() / 4, 500);
    label_description.setGeometry(Q);
    label_description.hide();
    leftVBoxLayout.addWidget(&label_description);*/
    leftVBoxLayout.addStretch();

    label_result.setFont(font);
    label_result.setText(QString("查询结果"));
    rightVBoxLayout.addWidget(&label_result);

    this->queryModel.setHeaderData(0, Qt::Horizontal, tr("ID"));
    this->queryModel.setHeaderData(1, Qt::Horizontal, tr("员工ID"));
    this->queryModel.setHeaderData(2, Qt::Horizontal, tr("员工姓名"));
    this->queryModel.setHeaderData(3, Qt::Horizontal, QString("请假原因"));
    this->queryModel.setHeaderData(4, Qt::Horizontal, QString("日期"));
    this->queryModel.setHeaderData(6, Qt::Horizontal, QString("状态"));
    tableView.setModel(&queryModel);
    rightVBoxLayout.addWidget(&tableView);

    wholeBoxLayout.addLayout(&leftVBoxLayout, 1);
    wholeBoxLayout.addLayout(&rightVBoxLayout, 3);
    setLayout(&wholeBoxLayout);

    clearRedundentRecond();
}

void AttendenceView::slot_query()
{
    qDebug() << "slot_query()";

    QString name = lineEdit_name.text();
    QString sql = "select id as 'ID', employeeId as '员工ID',"
                  "name as '姓名', attendentDate as '日期', "
                  "status as '状态' from attendencerecond";
    if (!name.isEmpty()){
        sql += " where name = '" + name + "'";
        int nAttendent = 0, nFake = 0, nAbsenteeism = 0;
        DBHelper dbHelper;
        if (!dbHelper.open()){
            qDebug() << "数据库打开失败";
            return;
        }
        QSqlQuery query = dbHelper.getQuery();
        query.exec(sql);
        while (query.next()){
            int status = query.value(4).toInt();
            switch (status){
            case 0:
                nAttendent++;
                break;
            case 1:
                nFake++;
                break;
            case 2:
                nAbsenteeism++;
                break;
            default:
                break;
            }
        }
        dbHelper.close();
        QString info = "    员工 " + name + " 在本月共出勤" + QString::number(nAttendent)
                + "天，请假" + QString::number(nFake) + "天，旷工" + QString::number(nAbsenteeism)
                + "天。"; //添加对员工本月出勤情况的描述
        queryModel.setQuery(sql);
        QMessageBox::information(this, QString("本月出勤情况"), info, QMessageBox::Ok);
        lineEdit_name.clear();
    }else{
        queryModel.setQuery(sql);
    }
    qDebug() << sql;
}

void AttendenceView::clearRedundentRecond()
{
    DBHelper dbHelper;
    if (!dbHelper.open()){
        qDebug() << "数据库打开失败";
        return;
    }
    QSqlQuery query = dbHelper.getQuery();
    QString sql = "select id, attendentDate from attendencerecond";
    if (!query.exec(sql)){
        qDebug() << "执行失败";
        dbHelper.close();
        return;
    }

    std::vector<int> ids;
    QDate date = QDate::currentDate();
    int year = date.year();
    int month = date.month();
    qDebug() << year << "年" << month << "月";
    while (query.next()){
        int id = query.value(0).toInt();
        QStringList list = query.value(1).toString().split('-');
        QStringList::iterator it = list.begin();
        int year_ = (*it).toInt();
        it++;
        int month_ = (*it).toInt();
        qDebug() << year_ << "," << month_;
        if (!(year_ == year && month_ == month)){
            ids.push_back(id);
        }
    }
    for (int i=0; i<ids.size(); i++){
        query.exec("delete from attendencerecond where id = " + QString::number(ids[i]));
    }
    dbHelper.close();
}
