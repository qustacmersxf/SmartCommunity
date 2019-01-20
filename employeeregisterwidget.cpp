#include "dbhelper.h"
#include "employeeregisterwidget.h"
#include "ui_employeeregisterwidget.h"
#include <QFont>
#include <QDebug>
#include <QMessageBox>

EmployeeRegisterWidget::EmployeeRegisterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmployeeRegisterWidget)
{
    ui->setupUi(this);

    QFont font;
    font.setPointSize(30);

    label_name.setText(QString("姓    名："));
    label_name.setFont(font);
    lineEdit_name.setFont(font);
    hBoxLayout[0].addWidget(&label_name);
    hBoxLayout[0].addWidget(&lineEdit_name);

    label_phone.setText(QString("联系电话："));
    label_phone.setFont(font);
    lineEdit_phone.setFont(font);
    hBoxLayout[1].addWidget(&label_phone);
    hBoxLayout[1].addWidget(&lineEdit_phone);

    label_password.setText(QString("密    码："));
    label_password.setFont(font);
    lineEdit_password.setFont(font);
    lineEdit_password.setEchoMode(QLineEdit::Password);
    hBoxLayout[2].addWidget(&label_password);
    hBoxLayout[2].addWidget(&lineEdit_password);

    label_confirm.setText(QString("确认密码："));
    label_confirm.setFont(font);
    lineEdit_confirm.setFont(font);
    lineEdit_confirm.setEchoMode(QLineEdit::Password);
    hBoxLayout[3].addWidget(&label_confirm);
    hBoxLayout[3].addWidget(&lineEdit_confirm);

    label_homeAddress.setText(QString("家庭住址："));
    label_homeAddress.setFont(font);
    lineEdit_homeAddress.setFont(font);
    hBoxLayout[4].addWidget(&label_homeAddress);
    hBoxLayout[4].addWidget(&lineEdit_homeAddress);

    pushButton_submit_employee.setText(QString("提交"));
    pushButton_submit_employee.setFont(font);
    pushButton_submit_employee.setFixedSize(120, 50);
    connect(&pushButton_submit_employee, SIGNAL(clicked(bool)), this, SLOT(slot_submit_employee()));
    hBoxLayout[5].addWidget(&pushButton_submit_employee);
    hBoxLayout[5].setAlignment(Qt::AlignRight);

    for (int i=0; i<6; i++){
        vBoxLayout.addLayout(&hBoxLayout[i]);
    }

    setLayout(&vBoxLayout);
}

EmployeeRegisterWidget::~EmployeeRegisterWidget()
{
    delete ui;
}

void EmployeeRegisterWidget::slot_submit_employee()
{
    QString name = lineEdit_name.text();
    QString phone = lineEdit_phone.text();
    QString password = lineEdit_password.text();
    QString password_confirm = lineEdit_confirm.text();
    QString homeAddress = lineEdit_homeAddress.text();

    if (name.isEmpty() || phone.isEmpty() || password.isEmpty() ||
        password_confirm.isEmpty() || homeAddress.isEmpty()){
        QMessageBox::information(this, QString("错误"), QString("请把信息输入完整"), QMessageBox::Ok);
        return;
    }
    if (0 != password.compare(password_confirm)){
        QMessageBox::information(this, QString("错误"), QString("密码确认不符，请重新输入"), QMessageBox::Ok);
        password.clear();
        password_confirm.clear();
        return;
    }

    DBHelper dbHelper;
    if (!dbHelper.open()){
        qDebug() << "数据库打开失败";
        return;
    }
    QSqlQuery query = dbHelper.getQuery();
    QString sql = "insert into user(name, role, phone, password, homeAddress) values('"
            + name + "', "
            + QString::number(1) + ", '"
            + phone + "', '"
            + password + "', '"
            + homeAddress + "')";
    qDebug() << sql;
    if (query.exec(sql)){
        qDebug() << "添加成功";
        QMessageBox::information(this, QString("成功"), QString("添加成功"), QMessageBox::Ok);
    }else{
        qDebug() << "添加失败";
        QMessageBox::information(this, QString("失败"), QString("添加失败"), QMessageBox::Ok);
    }
    dbHelper.close();
    qDebug() << "提交成功";
}
