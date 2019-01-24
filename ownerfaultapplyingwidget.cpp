#include "ownerfaultapplyingwidget.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlRecord>
#include <QTextEdit>
#include <QFont>

OwnerFaultApplyingWidget::OwnerFaultApplyingWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << "OwnerFaultApplyingWidget::OwnerFaultApplyingWidget() 1";
    QFont font;
    font.setPointSize(18);

    tableView.setModel(&queryModel);
    connect(&tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_tableViewClicked(QModelIndex)));
    vBoxLayout.addWidget(&tableView);
    qDebug() << "OwnerFaultApplyingWidget::OwnerFaultApplyingWidget() 2";

    pushButton_query.setFont(font);
    pushButton_query.setText(QString("查询"));
    connect(&pushButton_query, SIGNAL(clicked(bool)), this, SLOT(slot_query()));
    pushButton_remark.setFont(font);
    pushButton_remark.setText(QString("完成维修并评价"));
    connect(&pushButton_remark, SIGNAL(clicked(bool)), this, SLOT(slot_remark()));
    hBoxLayout.addStretch();
    hBoxLayout.addWidget(&pushButton_query);
    hBoxLayout.addWidget(&pushButton_remark);
    vBoxLayout.addLayout(&hBoxLayout);
    setLayout(&vBoxLayout);
    qDebug() << "OwnerFaultApplyingWidget::OwnerFaultApplyingWidget() 4";
}

void OwnerFaultApplyingWidget::setUser(QString userName, int userId)
{
    this->userName = userName;
    this->userId = userId;
    remarkWisget.setUser(userName, userId);
}

void OwnerFaultApplyingWidget::slot_query()
{
    QString sql = "select faultaccount.id as 'ID', name as '业主', "
                  "fault as '故障描述', status as '状态', remark as '评价' "
                  "from faultaccount join user on faultaccount.ownerId = user.id "
                  "where ownerId = " + QString::number(this->userId);
    qDebug() << sql;
    queryModel.setQuery(sql);
}

void OwnerFaultApplyingWidget::slot_remark()
{
    qDebug() << "OwnerParkingSpaceWidget";
    int row = tableView.currentIndex().row();
    if (row < 0){
        qDebug() << "row < 0";
        QMessageBox::information(this, QString("错误"), QString("未选择记录"), QMessageBox::Ok);
        return;
    }

    QSqlRecord recond = queryModel.record(tableView.currentIndex().row());
    int id = recond.value(0).toInt();
    remarkWisget.setFaultAccountId(id);
    remarkWisget.show();
}

void OwnerFaultApplyingWidget::slot_tableViewClicked(const QModelIndex index)
{
    tableView.selectRow(index.row());
}
