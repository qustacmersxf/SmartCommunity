#include "employeecostwidget.h"
#include <QFont>
#include <QDebug>
#include <QSqlRecord>
#include <QMessageBox>
#include <vector>
#include <dbhelper.h>

EmployeeCostWidget::EmployeeCostWidget(QWidget *parent) : QWidget(parent)
{

    QFont font;
    font.setPointSize(18);

    label_condition.setText(QString("筛选条件"));
    label_condition.setFont(font);
    leftHBoxLayout[0].addWidget(&label_condition);

    label_name.setText(QString("姓名："));
    label_name.setFont(font);
    lineEdit_name.setFont(font);
    leftHBoxLayout[1].addWidget(&label_name);
    leftHBoxLayout[1].addWidget(&lineEdit_name);

    label_type.setText(QString("类型："));
    label_type.setFont(font);
    comboBox_type.setFont(font);
    comboBox_type.addItem(QString("所有"));
    comboBox_type.addItem(QString("物业费"));
    comboBox_type.addItem(QString("车位费"));
    comboBox_type.addItem(QString("保修费"));
    leftHBoxLayout[2].addWidget(&label_type);
    leftHBoxLayout[2].addWidget(&comboBox_type, 1);

    pushButton_query.setText(QString("查询"));
    pushButton_query.setFont(font);
    connect(&pushButton_query, SIGNAL(clicked(bool)), this, SLOT(slot_query()));
    leftHBoxLayout[3].addWidget(&pushButton_query);
    leftHBoxLayout[3].setAlignment(Qt::AlignRight);

    for (int i=0; i<4; i++){
        leftVBoxLayout.addLayout(&leftHBoxLayout[i]);
    }
    leftVBoxLayout.addStretch();

    label_result.setText(QString("查询结果"));
    label_result.setFont(font);
    rightVBoxLayout.addWidget(&label_result);
    tableView.setModel(&queryModel);
    connect(&tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slot_tableViewDoubleClicked(QModelIndex)));
    connect(&tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_tableViewClicked(QModelIndex)));
    rightVBoxLayout.addWidget(&tableView);

    pushButton_remind.setText(QString("提醒业主缴费"));
    pushButton_remind.setFont(font);
    connect(&pushButton_remind, SIGNAL(clicked(bool)), this, SLOT(slot_remind()));
    rightHBoxLayout.addStretch();
    rightHBoxLayout.addWidget(&pushButton_remind);
    rightVBoxLayout.addLayout(&rightHBoxLayout);

    wholeHBoxLayout.addLayout(&leftVBoxLayout, 1);
    wholeHBoxLayout.addLayout(&rightVBoxLayout, 3);
    setLayout(&wholeHBoxLayout);
}

void EmployeeCostWidget::slot_query()
{
    QString sql = "select costaccount.id as 'ID', ownerId as '业主ID', "
                  "name as '业主姓名', type as '缴费类型', cost as '费用', "
                  "status as '状态' from costaccount join user on ownerId = user.id";
    std::vector<QString> conditions;
    QString name = lineEdit_name.text();
    if (!name.isEmpty()){
        conditions.push_back( "name = '" + name + "'");
    }
    QString type = comboBox_type.currentText();
    if (0 != type.compare("所有")){
        conditions.push_back("type = '" + type + "'");
    }
    if (conditions.size() > 0){
        sql += " where " + conditions[0];
        int n = conditions.size();
        for (int i=1; i<n; i++)
            sql += " and " + conditions[i];
    }
    qDebug() << sql;
    queryModel.setQuery(sql);
    lineEdit_name.clear();
    comboBox_type.setCurrentIndex(0);
}

void EmployeeCostWidget::slot_tableViewClicked(const QModelIndex index)
{
    tableView.selectRow(index.row());
}

void EmployeeCostWidget::slot_submitSuccess()
{
    queryModel.setQuery("select id as 'ID', name as '姓名', phone as '电话', password as '密码', homeAddress as '住址' from user");
}

void EmployeeCostWidget::slot_remind()
{
    QMessageBox::information(this, QString("缴费提醒"), QString("已经提醒业主"), QMessageBox::Ok);
}
