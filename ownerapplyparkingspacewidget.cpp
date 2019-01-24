#include "ownerapplyparkingspacewidget.h"
#include <QDebug>
#include <QFont>
#include <QMessageBox>
#include <QSqlRecord>
#include "dbhelper.h"

OwnerApplyParkingSpaceWidget::OwnerApplyParkingSpaceWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << "OwnerApplyParkingSpaceWidget::OwnerApplyParkingSpaceWidget() 1";
    QFont font;
    font.setPointSize(18);

    tableView.setModel(&queryModel);
    connect(&tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_tableViewClicked(QModelIndex)));
    vBoxLayout.addWidget(&tableView);
    qDebug() << "OwnerApplyParkingSpaceWidget::OwnerApplyParkingSpaceWidget() 2";

    pushButton_query.setFont(font);
    pushButton_query.setText(QString("查询可申请车位"));
    connect(&pushButton_query, SIGNAL(clicked(bool)), this, SLOT(slot_query()));
    pushButton_apply.setFont(font);
    pushButton_apply.setText(QString("申请"));
    connect(&pushButton_apply, SIGNAL(clicked(bool)), this, SLOT(slot_apply()));
    hBoxLayout.addStretch();
    hBoxLayout.addWidget(&pushButton_query);
    hBoxLayout.addWidget(&pushButton_apply);
    vBoxLayout.addLayout(&hBoxLayout);
    setLayout(&vBoxLayout);
    qDebug() << "OwnerApplyParkingSpaceWidget::OwnerApplyParkingSpaceWidget() 4";
}

void OwnerApplyParkingSpaceWidget::setUser(QString userName, int userId)
{
    this->userName = userName;
    this->userId = userId;
}

void OwnerApplyParkingSpaceWidget::slot_apply()
{
    qDebug() << "OwnerParkingSpaceWidget";
    int row = tableView.currentIndex().row();
    if (row < 0){
        qDebug() << "row < 0";
        QMessageBox::information(this, QString("错误"), QString("未选择记录"), QMessageBox::Ok);
        return;
    }
    QMessageBox::Button button = QMessageBox::question(this,
        QString("申请车位"), QString("是否申请该车位？"), QMessageBox::Ok | QMessageBox::No);
    if (QMessageBox::No == button){
        return;
    }

    QSqlRecord recond = queryModel.record(row);
    int id = recond.value(0).toInt();
    DBHelper db;
    if (!db.open()){
        qDebug() << "数据库打开失败 OwnerParkingSpaceWidget::slot_apply()";
        return;
    }
    QSqlQuery query = db.getQuery();
    QString sql = "insert into parkingSpaceApplyAccount(parkingSpaceID, ownerId, name) values("
            + QString::number(id) + ", "
            + QString::number(this->userId) + ", "
            + "'" + this->userName + "')";
    qDebug() << sql;
    if (!query.exec(sql)){
        qDebug() << "执行失败 OwnerParkingSpaceWidget::slot_apply()";
        db.close();
        return;
    }
    db.close();
    slot_query();
    QMessageBox::information(this, QString("车位申请"), QString("提交成功。"), QMessageBox::Ok);
}

void OwnerApplyParkingSpaceWidget::slot_query()
{
    qDebug() << "OwnerParkingSpaceWidget::slot_apply()";
    QString sql = "select id as 'ID', local as '位置', "
                  "price as '价格', width as '宽度', "
                  "height as '长度', status as '状态', ownerId as '业主ID' from parkingSpaceAccount "
                  "where status = '可申请'";
    qDebug() << sql;
    queryModel.setQuery(sql);
}

void OwnerApplyParkingSpaceWidget::slot_tableViewClicked(const QModelIndex index)
{
    qDebug() << "OwnerParkingSpaceWidget::slot_tableViewClicked()";
    tableView.selectRow(index.row());
}
