#include "ownerlookingwidget.h"
#include "ui_ownerlookingwidget.h"
#include <QFont>
#include <QDebug>
#include <QSqlRecord>
#include <QMessageBox>
#include <vector>
#include <dbhelper.h>

OwnerLookingWidget::OwnerLookingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OwnerLookingWidget)
{
    qDebug() << "ownerLookingWidget start";
    ui->setupUi(this);

    QFont font;
    font.setPointSize(10);

    connect(&ownerModifyWidget, SIGNAL(signal_submitSuccess()), this, SLOT(slot_submitSuccess()));

    label_condition.setText(QString("筛选条件"));
    label_condition.setFont(font);
    leftHBoxLayout[0].addWidget(&label_condition);
    qDebug() << "OwnerLookingWidget() 1";

    label_name.setText(QString("姓名"));
    label_name.setFont(font);
    lineEdit_name.setFont(font);
    leftHBoxLayout[1].addWidget(&label_name);
    leftHBoxLayout[1].addWidget(&lineEdit_name);
    qDebug() << "OwnerLookingWidget() 2";

    label_phone.setText(QString("电话"));
    label_phone.setFont(font);
    lineEdit_phone.setFont(font);
    leftHBoxLayout[2].addWidget(&label_phone);
    leftHBoxLayout[2].addWidget(&lineEdit_phone);
    qDebug() << "OwnerLookingWidget() 3";

    pushButton_query.setText(QString("查询"));
    pushButton_query.setFont(font);
    connect(&pushButton_query, SIGNAL(clicked(bool)), this, SLOT(slot_query()));
    leftHBoxLayout[3].addWidget(&pushButton_query);
    leftHBoxLayout[3].setAlignment(Qt::AlignRight);
    qDebug() << "OwnerLookingWidget() 4";

    for (int i=0; i<4; i++){
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
    qDebug() << "OwnerLookingWidget() 5";

    pushButton_delete.setText(QString("删除"));
    connect(&pushButton_delete, SIGNAL(clicked(bool)), this, SLOT(slot_delete()));
    rightHBoxLayout.addStretch();
    rightHBoxLayout.addWidget(&pushButton_delete);
    rightVBoxLayout.addLayout(&rightHBoxLayout);
    qDebug() << "OwnerLookingWidget() 6";

    wholeHBoxLayout.addLayout(&leftVBoxLayout, 1);
    wholeHBoxLayout.addLayout(&rightVBoxLayout, 4);
    setLayout(&wholeHBoxLayout);
    qDebug() << "OwnerLookingWidget() end";
}

OwnerLookingWidget::~OwnerLookingWidget()
{
    delete ui;
}
void OwnerLookingWidget::slot_query()
{
    QString sql = "select * from user where role = 2";
    std::vector<QString> conditions;
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
            sql += " and " + conditions[i];
    }
    qDebug() << sql;
    queryModel.setQuery(sql);
    tableView.resizeColumnsToContents();
    lineEdit_name.clear();
    lineEdit_phone.clear();
    qDebug() << "查询成功";
}

void OwnerLookingWidget::slot_tableViewDoubleClicked(const QModelIndex index)
{
    if (index.isValid()){
        QSqlRecord recond = queryModel.record(index.row());
        int id = recond.value(0).toInt();
        QString name = recond.value(1).toString();
        QString phone = recond.value(3).toString();
        QString password = recond.value(4).toString();
        QString homeAddress = recond.value(5).toString();
        qDebug() << name + phone + password + homeAddress;

        ownerModifyWidget.setInfo(id, name, phone, password, homeAddress);
        ownerModifyWidget.show();
    }
}

void OwnerLookingWidget::slot_tableViewClicked(const QModelIndex index)
{
    tableView.selectRow(index.row());
}

void OwnerLookingWidget::slot_submitSuccess()
{
    queryModel.setQuery("select * from user");
}

void OwnerLookingWidget::slot_delete()
{
    QSqlRecord recond = queryModel.record(tableView.currentIndex().row());
    int id = recond.value(0).toInt();
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
