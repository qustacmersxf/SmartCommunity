#include "employeelookingwidget.h"
#include "ui_employeelookingwidget.h"
#include <QFont>
#include <QDebug>
#include <QSqlRecord>
#include <QMessageBox>
#include <vector>
#include <dbhelper.h>

EmployeeLookingWidget::EmployeeLookingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmployeeLookingWidget)
{
    ui->setupUi(this);

    QFont font;
    font.setPointSize(18);

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
    QString str[2] = {"工作人员", "业主"};
    for (int i=0; i<2; i++){
        radioButton[i].setText(str[i]);
        radioButton[i].setFont(font);
        leftHBoxLayout[2].addWidget(&radioButton[i]);
        if (i < 1){
            leftHBoxLayout[2].addStretch();
        }
        buttonGroup.addButton(&radioButton[i], i);
    }

    label_phone.setText(QString("电话"));
    label_phone.setFont(font);
    lineEdit_phone.setFont(font);
    leftHBoxLayout[3].addWidget(&label_phone);
    leftHBoxLayout[3].addWidget(&lineEdit_phone);

    pushButton_query.setText(QString("查询"));
    pushButton_query.setFont(font);
    connect(&pushButton_query, SIGNAL(clicked(bool)), this, SLOT(slot_query()));
    leftHBoxLayout[4].addWidget(&pushButton_query);
    leftHBoxLayout[4].setAlignment(Qt::AlignRight);

    for (int i=0; i<5; i++){
        leftVBoxLayout.addLayout(&leftHBoxLayout[i]);
    }
    leftVBoxLayout.addStretch();

    label_result.setText(QString("查询结果（双击可修改）"));
    label_result.setFont(font);
    rightVBoxLayout.addWidget(&label_result);

    queryModel.setHeaderData(0, Qt::Horizontal, QString("ID"));
    queryModel.setHeaderData(1, Qt::Horizontal, QString("姓名"));
    queryModel.setHeaderData(2, Qt::Horizontal, QString("密码"));
    queryModel.setHeaderData(3, Qt::Horizontal, QString("联系电话"));
    queryModel.setHeaderData(4, Qt::Horizontal, QString("家庭住址"));
    tableView.setModel(&queryModel);
    connect(&tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slot_tableViewDoubleClicked(QModelIndex)));
    connect(&tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_tableViewClicked(QModelIndex)));
    rightVBoxLayout.addWidget(&tableView);

    pushButton_delete.setText(QString("删除"));
    pushButton_delete.setFont(font);
    connect(&pushButton_delete, SIGNAL(clicked(bool)), this, SLOT(slot_delete()));
    rightHBoxLayout.addStretch();
    rightHBoxLayout.addWidget(&pushButton_delete);
    rightVBoxLayout.addLayout(&rightHBoxLayout);

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
    DBHelper::Role role = (DBHelper::Role)(buttonGroup.checkedId() - 1);
    qDebug() << (int)role;
    switch (role) {
    case DBHelper::Role::employee:
        sql = "select id as 'ID', name as '姓名', role as '身份', phone as '电话', password as '密码', homeAddress as '家庭住址' from user_employee where role <> 0";
        break;
    case DBHelper::Role::owner:
        sql = "select id as 'ID', name as '姓名', role as '身份', phone as '电话', password as '密码', homeAddress as '家庭住址' from user_owner where role <> 0";
        break;
    default:
        sql = "select id as 'ID', name as '姓名', role as '身份', phone as '电话', password as '密码', homeAddress as '家庭住址' from user where role <> 0";
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
        for (int i=1; i<conditions.size(); i++)
            sql += "and " + conditions[i];
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
    queryModel.setQuery("select id as 'ID', name as '姓名', role as '身份', phone as '电话', password as '密码', homeAddress as '家庭住址' from user where role <> 0");
}

void EmployeeLookingWidget::slot_delete()
{
    int row = tableView.currentIndex().row();
    if (row < 0){
        qDebug() << "row < 0";
        QMessageBox::information(this, QString("错误"), QString("未选择记录"), QMessageBox::Ok);
        return;
    }
    QSqlRecord recond = queryModel.record(row);
    int id = recond.value(0).toInt();
    QString name = recond.value(1).toString();
    QMessageBox::Button button = QMessageBox::question(this, QString("删除"), "是否删除" + name + "的信息?",
                                                            QMessageBox::Ok | QMessageBox::No);
    if (QMessageBox::No == button){
        return;
    }
    QString sql = "delete from user where id = " + QString::number(id);
    DBHelper dbHelper;
    if (!dbHelper.open()){
        qDebug() << "数据库打开失败";
        return;
    }
    QSqlQuery query = dbHelper.getQuery();
    if (!query.exec(sql)){
        qDebug() << "删除失败";
        QMessageBox::information(this, QString("错误"), QString("删除失败"), QMessageBox::Ok);
        return;
    }
    QMessageBox::information(this, QString("成功"), QString("删除成功"), QMessageBox::Ok);
    qDebug() << "删除成功";
    queryModel.setQuery("select * from user");
}
