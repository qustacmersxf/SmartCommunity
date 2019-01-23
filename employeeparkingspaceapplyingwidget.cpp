#include <QDebug>
#include <QFont>
#include <QMessageBox>
#include <QSqlRecord>
#include "employeeparkingspaceapplyingwidget.h"
#include "dbhelper.h"

EmployeeParkingSpaceApplyingWidget::EmployeeParkingSpaceApplyingWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << "EmployeeParkingSpaceApplyingWidget::EmployeeParkingSpaceApplyingWidget() 1";
    QFont font;
    font.setPointSize(18);

    tableView.setModel(&queryModel);
    connect(&tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_tableViewClicked(QModelIndex)));
    vBoxLayout.addWidget(&tableView);
    qDebug() << "OwnerParkingSpaceWidget::OwnerParkingSpaceWidget() 2";

    pushButton_query.setFont(font);
    pushButton_query.setText(QString("申请查询"));
    connect(&pushButton_query, SIGNAL(clicked(bool)), this, SLOT(slot_query()));
    pushButton_accept.setFont(font);
    pushButton_accept.setText(QString("接受申请"));
    connect(&pushButton_accept, SIGNAL(clicked(bool)), this, SLOT(slot_accept()));
    hBoxLayout.addStretch();
    hBoxLayout.addWidget(&pushButton_query);
    hBoxLayout.addWidget(&pushButton_accept);
    vBoxLayout.addLayout(&hBoxLayout);
    setLayout(&vBoxLayout);
    qDebug() << "OwnerParkingSpaceWidget::OwnerParkingSpaceWidget() 4";
}

void EmployeeParkingSpaceApplyingWidget::slot_accept()
{
    qDebug() << "EmployeeParkingSpaceApplyingWidget::slot_accept()";
    int row = tableView.currentIndex().row();
    if (row < 0){
        qDebug() << "row < 0";
        QMessageBox::information(this, QString("错误"), QString("未选择记录"), QMessageBox::Ok);
        return;
    }

    QSqlRecord recond = queryModel.record(row);
    int parkingSpaceId = recond.value(1).toInt();
    int ownerId = recond.value(2).toInt();
    DBHelper db;
    if (!db.open()){
        qDebug() << "数据库打开失败 OwnerParkingSpaceWidget::slot_apply()";
        return;
    }
    QSqlQuery query = db.getQuery();
    QString sql = "update parkingspaceaccount set status = '已出售', ownerId = " + QString::number(ownerId)
            + " where id = " + QString::number(parkingSpaceId);
    qDebug() << sql;
    if (!query.exec(sql)){
        qDebug() << "执行失败 OwnerParkingSpaceWidget::slot_apply()";
        db.close();
        return;
    }
    db.close();
    QMessageBox::information(this, QString("申请处理"), QString("处理成功。"), QMessageBox::Ok);
}

void EmployeeParkingSpaceApplyingWidget::slot_query()
{
    qDebug() << "EmployeeParkingSpaceApplyingWidget::slot_query()";
    QString sql = "select id as 'ID', parkingSpaceID as '车位ID', "
                  "ownerId as '申请业主ID', name as '申请业主姓名' from parkingSpaceApplyAccount";
    qDebug() << sql;
    queryModel.setQuery(sql);
}

void EmployeeParkingSpaceApplyingWidget::slot_tableViewClicked(const QModelIndex index)
{
    tableView.selectRow(index.row());
}
