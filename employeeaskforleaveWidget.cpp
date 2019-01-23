#include <QFont>
#include <QDebug>
#include <QMessageBox>
#include "employeeaskforleaveWidget.h"
#include "dbhelper.h"

EmployeeAskForLeaveWidget::EmployeeAskForLeaveWidget(QWidget *parent) : QWidget(parent)
{
    QFont font;
    font.setPointSize(18);

    label_date.setFont(font);
    label_date.setText(QString("起止时间："));
    dateEdit_start.setCalendarPopup(true);
    dateEdit_start.setDate(QDate::currentDate());
    dateEdit_start.setFont(font);
    label_spliter.setFont(font);
    label_spliter.setText(QString(""));
    dateEdit_end.setCalendarPopup(true);
    dateEdit_end.setDate(QDate::currentDate());
    dateEdit_end.setFont(font);
    hBoxLayout[0].addWidget(&label_date);
    hBoxLayout[0].addWidget(&dateEdit_start);
    hBoxLayout[0].addStretch();
    hBoxLayout[0].addWidget(&label_spliter);
    hBoxLayout[0].addStretch();
    hBoxLayout[0].addWidget(&dateEdit_end);
    vBoxLayout.addLayout(&hBoxLayout[0]);

    label_reason.setFont(font);
    label_reason.setText(QString("原    因："));
    label_reason.setAlignment(Qt::AlignTop);
    hBoxLayout[1].addWidget(&label_reason);
    textEdit_reason.setFont(font);
    hBoxLayout[1].addWidget(&textEdit_reason);
    vBoxLayout.addLayout(&hBoxLayout[1]);

    pushButton_submit.setFont(font);
    pushButton_submit.setText(QString("提交"));
    connect(&pushButton_submit, SIGNAL(clicked(bool)), this, SLOT(slot_submit()));
    pushButton_cancel.setFont(font);
    pushButton_cancel.setText(QString("取消"));
    connect(&pushButton_cancel, SIGNAL(clicked(bool)), this, SLOT(slot_cancel()));
    hBoxLayout[2].addStretch();
    hBoxLayout[2].addWidget(&pushButton_submit);
    hBoxLayout[2].addWidget(&pushButton_cancel);
    vBoxLayout.addLayout(&hBoxLayout[2]);

    setLayout(&vBoxLayout);
}

void EmployeeAskForLeaveWidget::setUser(QString userName, int userId)
{
    this->userName = userName;
    this->userId = userId;
}

void EmployeeAskForLeaveWidget::slot_submit()
{
    QString reason = textEdit_reason.toPlainText();
    qDebug() << "slot_submit()";
    DBHelper db;
    if (!db.open()){
        qDebug() << "数据库打开失败 EmployeeAskForLeaveWidget::slot_submit()";
        return;
    }
    QSqlQuery query = db.getQuery();
    QString sql = "insert into fakestrip(employeeId, name, reason, startDate, endDate, status) values("
            + QString::number(this->userId) + ", "
            + "'" + this->userName + "', "
            + "'" + reason + "', "
            + "'" + dateEdit_start.date().toString("yyyy-MM-dd") + "', "
            + "'" + dateEdit_end.date().toString("yyyy-MM-dd") + "', "
            + QString::number(0) + ")";
    qDebug() << sql;
    if (!query.exec(sql)){
        qDebug() << "执行失败 EmployeeAskForLeaveWidget::slot_submit()";
        db.close();
        return;
    }
    QMessageBox::information(this, QString("请假"), QString("提交成功，请的等待结果"), QMessageBox::Ok);
}

void EmployeeAskForLeaveWidget::slot_cancel()
{
    qDebug() << "slot_cancel()";
    textEdit_reason.clear();
    QDate date = QDate::currentDate();
    dateEdit_start.setDate(date);
    dateEdit_end.setDate(date);
}
