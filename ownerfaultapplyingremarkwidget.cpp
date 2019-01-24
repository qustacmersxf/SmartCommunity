#include "ownerfaultapplyingremarkwidget.h"
#include <QDebug>
#include <QFont>
#include <QMessageBox>
#include "dbhelper.h"

OwnerFaultApplyingRemarkWidget::OwnerFaultApplyingRemarkWidget(QWidget *parent) : QWidget(parent)
{
    QFont font;
    font.setPointSize(18);

    textEdit_remark.setFont(font);
    textEdit_remark.setPlaceholderText(QString("请在这里写评论"));
    vBoxLayout.addWidget(&textEdit_remark);

    pushButton_submit.setFont(font);
    pushButton_submit.setText(QString("提交"));
    connect(&pushButton_submit, SIGNAL(clicked(bool)), this, SLOT(slot_submit()));
    hBoxLayout.addStretch();
    hBoxLayout.addWidget(&pushButton_submit);
    vBoxLayout.addLayout(&hBoxLayout);

    setLayout(&vBoxLayout);
}

void OwnerFaultApplyingRemarkWidget::setUser(QString userName, int userId)
{
    this->userName = userName;
    this->userId = userId;
}

void OwnerFaultApplyingRemarkWidget::setFaultAccountId(int id)
{
    this->faultaccountId = id;
}

void OwnerFaultApplyingRemarkWidget::slot_submit()
{
    QString remark = textEdit_remark.toPlainText();
    DBHelper db;
    if (!db.open()){
        qDebug() << "数据库打开失败 OwnerParkingSpaceWidget::slot_apply()";
        return;
    }
    QSqlQuery query = db.getQuery();
    QString sql = "update faultaccount set status = '已处理', remark = '"
            + remark + "' where id = " + QString::number(this->faultaccountId);
    qDebug() << sql;
    if (!query.exec(sql)){
        qDebug() << "执行失败 OwnerParkingSpaceWidget::slot_apply()";
        db.close();
        return;
    }
    db.close();
    QMessageBox::information(this, QString("故障申请评论"), QString("维修以结束，请到缴费界面缴纳维修费用。"), QMessageBox::Ok);
    emit signal_remarked();
    close();
}
