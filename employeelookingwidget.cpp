#include "employeelookingwidget.h"
#include "ui_employeelookingwidget.h"
#include <QFont>
#include <QDebug>

EmployeeLookingWidget::EmployeeLookingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmployeeLookingWidget)
{
    ui->setupUi(this);

    QFont font;
    font.setPointSize(12);

    label_condition.setText(QString("筛选条件"));
    label_condition.setFont(font);
    leftHBoxLayout[0].addWidget(&label_condition);

    label_name.setText(QString("姓名"));
    label_name.setFont(font);
    lineEdit_name.setFont(font);
    leftHBoxLayout[1].addWidget(&label_name);
    leftHBoxLayout[1].addWidget(&lineEdit_name);

    label_role.setText(QString("身份"));
    label_role.setFont(font);
    lineEdit_role.setFont(font);
    leftHBoxLayout[2].addWidget(&label_role);
    QString str[3] = {"管理员", "工作人员", "业主"};
    for (int i=0; i<3; i++){
        radioButton[i].setText(str[i]);
        radioButton[i].setFont(font);
        leftHBoxLayout[2].addWidget(&radioButton[i]);
        if (i < 2){
            leftHBoxLayout[2].addStretch();
        }
        buttonGroup.addButton(&radioButton[i]);
    }

    label_phone.setText(QString("电话"));
    label_phone.setFont(font);
    lineEdit_phone.setFont(font);
    leftHBoxLayout[3].addWidget(&label_phone);
    leftHBoxLayout[3].addWidget(&lineEdit_phone);

    label_homeAddress.setText(QString("住址"));
    label_homeAddress.setFont(font);
    lineEdit_homeAddress.setFont(font);
    leftHBoxLayout[4].addWidget(&label_homeAddress);
    leftHBoxLayout[4].addWidget(&lineEdit_homeAddress);

    pushButton_query.setText(QString("查询"));
    pushButton_query.setFont(font);
    connect(&pushButton_query, SIGNAL(clicked(bool)), this, SLOT(slot_query()));
    leftHBoxLayout[5].addWidget(&pushButton_query);
    leftHBoxLayout[5].setAlignment(Qt::AlignRight);

    for (int i=0; i<6; i++){
        leftVBoxLayout.addLayout(&leftHBoxLayout[i]);
    }
    leftVBoxLayout.addStretch();

    label_result.setText(QString("查询结果（双击可修改）"));
    label_result.setFont(font);
    rightVBoxLayout.addWidget(&label_result);
    rightVBoxLayout.addWidget(&tableView);

    wholeHBoxLayout.addLayout(&leftVBoxLayout, 1);
    wholeHBoxLayout.addLayout(&rightVBoxLayout, 3);
    setLayout(&wholeHBoxLayout);
}

EmployeeLookingWidget::~EmployeeLookingWidget()
{
    delete ui;
}

void EmployeeLookingWidget::slot_query()
{
    qDebug() << "查询成功";
}
