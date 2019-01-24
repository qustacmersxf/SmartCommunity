#include "ownercostwidget.h"
#include <QDebug>
#include <QFont>
#include <QMessageBox>
#include <QSqlRecord>
#include "dbhelper.h"

OwnerCostWidget::OwnerCostWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << "OwnerCostWidget::OwnerCostWidget() 1";
    QFont font;
    font.setPointSize(18);

    tableView.setModel(&queryModel);
    connect(&tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_tableViewClicked(QModelIndex)));
    vBoxLayout.addWidget(&tableView);
    qDebug() << "OwnerCostWidget::OwnerCostWidget() 2";

    pushButton_query.setFont(font);
    pushButton_query.setText(QString("缴费查询"));
    connect(&pushButton_query, SIGNAL(clicked(bool)), this, SLOT(slot_query()));
    pushButton_pay.setFont(font);
    pushButton_pay.setText(QString("缴费"));
    connect(&pushButton_pay, SIGNAL(clicked(bool)), this, SLOT(slot_pay()));
    hBoxLayout.addStretch();
    hBoxLayout.addWidget(&pushButton_query);
    hBoxLayout.addWidget(&pushButton_pay);
    vBoxLayout.addLayout(&hBoxLayout);
    setLayout(&vBoxLayout);
    qDebug() << "OwnerCostWidget::OwnerCostWidget() 4";
}

void OwnerCostWidget::setUser(QString userName, int userId)
{
    this->userName = userName;
    this->userId = userId;
}

void OwnerCostWidget::slot_pay()
{
    int row = tableView.currentIndex().row();
    if (row < 0){
        qDebug() << "row < 0";
        QMessageBox::information(this, QString("错误"), QString("未选择记录"), QMessageBox::Ok);
        return;
    }
    QMessageBox::Button button = QMessageBox::question(this,
        QString("缴费"), QString("是否缴费？"), QMessageBox::Ok | QMessageBox::No);
    if (QMessageBox::No == button){
        return;
    }

    QSqlRecord recond = queryModel.record(row);
    int id = recond.value(0).toInt();
    DBHelper db;
    if (!db.open()){
        qDebug() << "数据库打开失败 OwnerCostWidget::slot_pay()";
        return;
    }
    QSqlQuery query = db.getQuery();
    QString sql = "update costaccount set status = '已缴费' where id = " + QString::number(id);
    qDebug() << sql;
    if (!query.exec(sql)){
        qDebug() << "执行失败 OwnerCostWidget::slot_pay()";
        db.close();
        return;
    }
    db.close();
    slot_query();
    QMessageBox::information(this, QString("缴费"), QString("缴费成功。"), QMessageBox::Ok);
}

void OwnerCostWidget::slot_query()
{
    qDebug() << "OwnerCostWidget::slot_query()";
    QString sql = "select costaccount.id as 'ID', ownerId as '业主ID', "
                  "name as '业主姓名', type as '缴费类型', cost as '费用', "
                  "status as '状态' from costaccount join user on ownerId = user.id "
                  "where user.id = " + QString::number(this->userId);
    qDebug() << sql;
    queryModel.setQuery(sql);
}

void OwnerCostWidget::slot_tableViewClicked(const QModelIndex index)
{
    qDebug() << "OwnerParkingSpaceWidget::slot_tableViewClicked()";
    tableView.selectRow(index.row());
}
