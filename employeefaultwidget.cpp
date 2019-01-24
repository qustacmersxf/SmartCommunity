#include "employeefaultwidget.h"
#include <QDebug>
#include <QFont>
#include <QMessageBox>
#include <QSqlRecord>
#include "dbhelper.h"

EmployeeFaultWidget::EmployeeFaultWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << "EmployeeFaultWidget::EmployeeFaultWidget() 1";
    QFont font;
    font.setPointSize(18);

    tableView.setModel(&queryModel);
    connect(&tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_tableViewClicked(QModelIndex)));
    vBoxLayout.addWidget(&tableView);
    qDebug() << "EmployeeFaultWidget::EmployeeFaultWidget() 2";

    pushButton_query.setFont(font);
    pushButton_query.setText(QString("故障申请查询"));
    connect(&pushButton_query, SIGNAL(clicked(bool)), this, SLOT(slot_query()));
    pushButton_dealWith.setFont(font);
    pushButton_dealWith.setText(QString("故障申请处理"));
    connect(&pushButton_dealWith, SIGNAL(clicked(bool)), this, SLOT(slot_dealWith()));
    hBoxLayout.addStretch();
    hBoxLayout.addWidget(&pushButton_query);
    hBoxLayout.addWidget(&pushButton_dealWith);
    vBoxLayout.addLayout(&hBoxLayout);
    setLayout(&vBoxLayout);
    qDebug() << "EmployeeFaultWidget::EmployeeFaultWidget() 4";
}

void EmployeeFaultWidget::slot_dealWith()
{
    qDebug() << "EmployeeFaultWidget::slot_dealWith()";
    int row = tableView.currentIndex().row();
    if (row < 0){
        qDebug() << "row < 0";
        QMessageBox::information(this, QString("错误"), QString("未选择记录"), QMessageBox::Ok);
        return;
    }

    QSqlRecord recond = queryModel.record(row);
    int id = recond.value(0).toInt();
    DBHelper db;
    if (!db.open()){
        qDebug() << "数据库打开失败 EmployeeFaultWidget::slot_dealWith()";
        return;
    }
    QSqlQuery query = db.getQuery();
    QString sql = "update faultaccount set status = '处理中' where id = " + QString::number(id);
    qDebug() << sql;
    if (!query.exec(sql)){
        qDebug() << "执行失败 EmployeeFaultWidget::slot_dealWith()";
        db.close();
        return;
    }
    db.close();
    slot_dealWith();
    QMessageBox::information(this, QString("申请处理"), QString("已通知维修人员前去处理。"), QMessageBox::Ok);
}

void EmployeeFaultWidget::slot_query()
{
    qDebug() << "EmployeeFaultWidget::slot_query()";
    QString sql = "select faultaccount.id as 'ID', ownerId as '业主ID', "
                  "name as '业主姓名', fault as '故障描述', status as '状态', remark as '评论' "
                  "from faultaccount join user on ownerId = user.id";
    qDebug() << sql;
    queryModel.setQuery(sql);
}

void EmployeeFaultWidget::slot_tableViewClicked(const QModelIndex index)
{
    tableView.selectRow(index.row());
}
