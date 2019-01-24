#include "ownerfaultapplyingwidget.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlRecord>
#include <QTextEdit>
#include <QFont>
#include "dbhelper.h"

OwnerFaultApplyingWidget::OwnerFaultApplyingWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << "OwnerFaultApplyingWidget::OwnerFaultApplyingWidget() 1";

    connect(&remarkWisget, SIGNAL(signal_remarked()), this, SLOT(slot_remarked()));

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
    QString status = recond.value(5).toString();
    if (0 == status.compare("已处理")){
        QMessageBox::information(this, QString("评论"), QString("您已结束该维修服务"), QMessageBox::Ok);
        return;
    }
    remarkWisget.setFaultAccountId(id);
    remarkWisget.show();
}

void OwnerFaultApplyingWidget::slot_tableViewClicked(const QModelIndex index)
{
    tableView.selectRow(index.row());
}

void OwnerFaultApplyingWidget::slot_remarked()
{
    DBHelper db;
    if (!db.open()){
        qDebug() << "数据库打开失败";
        return;
    }
    QSqlQuery query = db.getQuery();
    QString sql = "insert into costaccount(ownerId, type, cost, status) values("
            + QString::number(this->userId) + ", '维修费', 100, '未缴费')";
    qDebug() <<sql;
    if (!query.exec(sql)){
        qDebug() << "提交失败";
        QMessageBox::information(this, QString("失败"), QString("提交失败"), QMessageBox::Ok);
    }
    db.close();
    slot_query();
}
