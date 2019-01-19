#include "employeeregisterwidget.h"
#include "ui_employeeregisterwidget.h"
#include <QFont>
#include <QDebug>

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
    hBoxLayout[2].addWidget(&label_password);
    hBoxLayout[2].addWidget(&lineEdit_password);

    label_confirm.setText(QString("确认密码："));
    label_confirm.setFont(font);
    lineEdit_confirm.setFont(font);
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
    hBoxLayout[5].addWidget(&pushButton_submit_employee);
    hBoxLayout[5].setAlignment(Qt::AlignRight);

    for (int i=0; i<6; i++){
        vBoxLayout.addLayout(&hBoxLayout[i]);
    }

    connect(&pushButton_submit_employee, SIGNAL(clicked(bool)), this, SLOT(slot_submit_employee()));
    setLayout(&vBoxLayout);
}

EmployeeRegisterWidget::~EmployeeRegisterWidget()
{
    delete ui;
}

void EmployeeRegisterWidget::slot_submit_employee()
{
    qDebug() << "提交成功";
}
