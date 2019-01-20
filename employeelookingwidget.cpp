#include "employeelookingwidget.h"
#include "ui_employeelookingwidget.h"
#include <QFont>
#include <QDebug>
#include <QSqlRecord>
#include <vector>
#include <dbhelper.h>

EmployeeLookingWidget::EmployeeLookingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmployeeLookingWidget)
{
    ui->setupUi(this);

    QFont font;
    font.setPointSize(10);

    connect(&employeeModifyWidget, SIGNAL(signal_submitSuccess()), this, SLOT(slot_submitSuccess()));

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
        buttonGroup.addButton(&radioButton[i], i);
    }

    label_phone.setText(QString("电话"));
    label_phone.setFont(font);
    lineEdit_phone.setFont(font);
    leftHBoxLayout[3].addWidget(&label_phone);
    leftHBoxLayout[3].addWidget(&lineEdit_phone);

    /*label_homeAddress.setText(QString("住址"));
    label_homeAddress.setFont(font);
    lineEdit_homeAddress.setFont(font);
    leftHBoxLayout[4].addWidget(&label_homeAddress);
    leftHBoxLayout[4].addWidget(&lineEdit_homeAddress);*/

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
    queryModel.setHeaderData(0, Qt::Horizontal, QString("ID"));
    queryModel.setHeaderData(1, Qt::Horizontal, QString("姓名"));
    queryModel.setHeaderData(3, Qt::Horizontal, QString("联系电话"));
    queryModel.setHeaderData(4, Qt::Horizontal, QString("家庭住址"));
    tableView.setModel(&queryModel);
    connect(&tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slot_tableViewDoubleClicked(QModelIndex)));
    connect(&tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_tableViewClicked(QModelIndex)));
    rightVBoxLayout.addWidget(&tableView);
    qDebug() << "查询成功";

    wholeHBoxLayout.addLayout(&leftVBoxLayout, 1);
    wholeHBoxLayout.addLayout(&rightVBoxLayout, 4);
    setLayout(&wholeHBoxLayout);
}

EmployeeLookingWidget::~EmployeeLookingWidget()
{
    delete ui;
}

void EmployeeLookingWidget::slot_query()
{
    QString sql = "";
    std::vector<QString> conditions;
    DBHelper::Role role = (DBHelper::Role)buttonGroup.checkedId();
    qDebug() << (int)role;
    switch (role) {
    case DBHelper::Role::administrator:
        sql = "select * from user_administrator";
        break;
    case DBHelper::Role::employee:
        sql = "select * from user_employee";
        break;
    case DBHelper::Role::owner:
        sql = "select * from user_owner";
        break;
    default:
        sql = "select * from user";
        break;
    }
    QString name = lineEdit_name.text();
    if (!name.isEmpty()){
        conditions.push_back( "name = '" + name + "'");
    }
    QString phone = lineEdit_phone.text();
    if (!phone.isEmpty()){
        conditions.push_back("phone = '" + phone + "'");
    }
    if (conditions.size() > 0){
        sql += " where " + conditions[0];
        for (int i=1; i<conditions.size(); i++)
            sql += ", " + conditions[i];
    }
    qDebug() << sql;
    queryModel.setQuery(sql);
    tableView.resizeColumnsToContents();
    QRadioButton *button = (QRadioButton*)buttonGroup.checkedButton();
    if (0 != button){
        qDebug() << "button != 0";
        buttonGroup.removeButton(button);
        button->setChecked(false);
        buttonGroup.addButton(button, (int)role);
    }else{
        qDebug() << "button == 0";
    }
    lineEdit_name.clear();
    lineEdit_phone.clear();
    qDebug() << "查询成功";
}

void EmployeeLookingWidget::slot_tableViewDoubleClicked(const QModelIndex index)
{
    if (index.isValid()){
        QSqlRecord recond = queryModel.record(index.row());
        int id = recond.value(0).toInt();
        QString name = recond.value(1).toString();
        QString phone = recond.value(3).toString();
        QString password = recond.value(4).toString();
        QString homeAddress = recond.value(5).toString();
        qDebug() << name + phone + password + homeAddress;

        employeeModifyWidget.setInfo(id, name, phone, password, homeAddress);
        employeeModifyWidget.show();
    }
}

void EmployeeLookingWidget::slot_tableViewClicked(const QModelIndex index)
{
    tableView.selectRow(index.row());
}

void EmployeeLookingWidget::slot_submitSuccess()
{
    queryModel.setQuery("select * from user");
}
