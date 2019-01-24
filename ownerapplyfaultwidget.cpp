#include "ownerapplyfaultwidget.h"
#include <QDebug>
#include <QFont>
#include <QMessageBox>
#include "dbhelper.h"

OwnerApplyFaultWidget::OwnerApplyFaultWidget(QWidget *parent) : QWidget(parent)
{
    QFont font;
    font.setPointSize(18);

    textEdit_fault.setFont(font);
    textEdit_fault.setPlaceholderText(QString("请填写故障地点和故障描述"));
    vBoxLayout.addWidget(&textEdit_fault);

    pushButton_submit.setFont(font);
    pushButton_submit.setText(QString("提交"));
    connect(&pushButton_submit, SIGNAL(clicked(bool)), this, SLOT(slot_submit()));
    hBoxLayout.addStretch();
    hBoxLayout.addWidget(&pushButton_submit);
    vBoxLayout.addLayout(&hBoxLayout);
    setLayout(&vBoxLayout);
}

void OwnerApplyFaultWidget::setUser(QString userName, int userId)
{
    this->userName = userName;
    this->userId = userId;
}

void OwnerApplyFaultWidget::slot_submit()
{
    QString fault = textEdit_fault.toPlainText();
    DBHelper db;
    if (!db.open()){
        qDebug() << "数据库打开失败 OwnerApplyFaultWidget::slot_submit()";
        return;
    }
    QSqlQuery query = db.getQuery();
    QString sql = "insert into faultaccount(ownerId, fault, status) values("
            + QString::number(this->userId) + ", "
            + "'" + fault + "', '未处理')";
    qDebug() << sql;
    if (!query.exec(sql)){
        qDebug() << "执行失败 OwnerApplyFaultWidget::slot_submit()";
        db.close();
        return;
    }
    db.close();
    QMessageBox::information(this, QString("报修"), QString("提交成功。"), QMessageBox::Ok);
}
