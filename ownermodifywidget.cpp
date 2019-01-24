#include "ownermodifywidget.h"
#include "ui_ownermodifywidget.h"
#include <QFont>
#include <QDebug>
#include <QMessageBox>
#include <dbhelper.h>

OwnerModifyWidget::OwnerModifyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OwnerModifyWidget)
{
    ui->setupUi(this);

    QFont font;
    font.setPointSize(18);

    setWindowTitle(QString("修改信息"));

    label_name.setText(QString("姓名"));
    label_name.setFont(font);
    lineEdit_name.setFont(font);
    hBoxLayout[0].addWidget(&label_name);
    hBoxLayout[0].addWidget(&lineEdit_name);

    label_phone.setText(QString("电话"));
    label_phone.setFont(font);
    lineEdit_phone.setFont(font);
    hBoxLayout[1].addWidget(&label_phone);
    hBoxLayout[1].addWidget(&lineEdit_phone);

    label_password.setText(QString("密码"));
    label_password.setFont(font);
    lineEdit_password.setFont(font);
    hBoxLayout[2].addWidget(&label_password);
    hBoxLayout[2].addWidget(&lineEdit_password);

    label_homeAddress.setText(QString("住址"));
    label_homeAddress.setFont(font);
    lineEdit_homeAddress.setFont(font);
    hBoxLayout[3].addWidget(&label_homeAddress);
    hBoxLayout[3].addWidget(&lineEdit_homeAddress);

    pushButton_submit.setText(QString("提交"));
    pushButton_submit.setFont(font);
    connect(&pushButton_submit, SIGNAL(clicked(bool)), this, SLOT(slot_submit()));
    pushButton_cancel.setText(QString("取消"));
    pushButton_cancel.setFont(font);
    connect(&pushButton_cancel, SIGNAL(clicked(bool)), this, SLOT(slot_cancel()));
    hBoxLayout[4].addStretch();
    hBoxLayout[4].addWidget(&pushButton_submit);
    hBoxLayout[4].addWidget(&pushButton_cancel);

    for (int i=0; i<5; i++){
        vBoxLayout.addLayout(&hBoxLayout[i]);
    }

    setLayout(&vBoxLayout);
}

OwnerModifyWidget::~OwnerModifyWidget()
{
    delete ui;
}

void OwnerModifyWidget::setInfo(int id, QString name, QString phone, QString password, QString homeAddress)
{
    this->id = id;
    lineEdit_name.setText(name);
    lineEdit_phone.setText(phone);
    lineEdit_password.setText(password);
    lineEdit_homeAddress.setText(homeAddress);
}

void OwnerModifyWidget::slot_submit()
{
    QString name = lineEdit_name.text();
    QString phone = lineEdit_phone.text();
    QString password = lineEdit_password.text();
    QString homeAddress = lineEdit_homeAddress.text();
    QString sql = "update user set name = '" + name + "' ,"
            + "phone = '" + phone + "', "
            + "password = '" + password + "', "
            + "homeAddress = '" + homeAddress + "'"
            + "where id = " + QString::number(this->id);
    qDebug() << sql;
    DBHelper dbHelper;
    if (!dbHelper.open()){
        qDebug() << "数据库打开失败";
        return;
    }
    QSqlQuery query = dbHelper.getQuery();
    if (!query.exec(sql)){
        qDebug() << "提交失败";
        dbHelper.close();
        QMessageBox::information(this, QString("失败"), QString("提交失败"), QMessageBox::Ok);
        return;
    }
    qDebug() << "提交成功";
    dbHelper.close();
    QMessageBox::information(this, QString("成功"), QString("提交成功"), QMessageBox::Ok);
    emit signal_submitSuccess();
    close();
}

void OwnerModifyWidget::slot_cancel()
{
    close();
}

