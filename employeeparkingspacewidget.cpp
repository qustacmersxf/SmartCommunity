#include "employeeparkingspacewidget.h"
#include <QFont>
#include <QDebug>
#include <QMessageBox>
#include "dbhelper.h"

EmployeeParkingSpaceWidget::EmployeeParkingSpaceWidget(QWidget *parent) : QWidget(parent)
{
    QFont font;
    font.setPointSize(18);

    label_addParkingSpace.setFont(font);
    label_addParkingSpace.setText(QString("添加车位销售单"));
    leftVBoxLayout.addWidget(&label_addParkingSpace);

    label_local.setFont(font);
    label_local.setText(QString("地点："));
    lineEdit_local.setFont(font);
    leftHBoxLayout[0].addWidget(&label_local);
    leftHBoxLayout[0].addWidget(&lineEdit_local);
    leftVBoxLayout.addLayout(&leftHBoxLayout[0]);

    label_price.setFont(font);
    label_price.setText(QString("价格："));
    spinBox_prince.setFont(font);
    spinBox_prince.setMaximum(9999999);
    leftHBoxLayout[1].addWidget(&label_price);
    leftHBoxLayout[1].addWidget(&spinBox_prince, 1);
    leftVBoxLayout.addLayout(&leftHBoxLayout[1]);

    label_width.setFont(font);
    label_width.setText(QString("宽度："));
    doubleSpinBox_width.setFont(font);
    leftHBoxLayout[2].addWidget(&label_width);
    leftHBoxLayout[2].addWidget(&doubleSpinBox_width, 1);
    leftVBoxLayout.addLayout(&leftHBoxLayout[2]);

    label_height.setFont(font);
    label_height.setText(QString("长度："));
    doubleSpinBox_height.setFont(font);
    leftHBoxLayout[3].addWidget(&label_height);
    leftHBoxLayout[3].addWidget(&doubleSpinBox_height, 1);
    leftVBoxLayout.addLayout(&leftHBoxLayout[3]);

    label_status.setFont(font);
    label_status.setText(QString("长度："));
    comboBox_status.setFont(font);
    comboBox_status.addItem(QString("待出售"));
    comboBox_status.addItem(QString("待出租"));
    comboBox_status.addItem(QString("订单结束"));
    leftHBoxLayout[4].addWidget(&label_status);
    leftHBoxLayout[4].addWidget(&comboBox_status, 1);
    leftVBoxLayout.addLayout(&leftHBoxLayout[4]);

    pushButton_submit.setFont(font);
    pushButton_submit.setText(QString("提交"));
    connect(&pushButton_submit, SIGNAL(clicked(bool)), this, SLOT(slot_submit()));
    leftHBoxLayout[5].addStretch();
    leftHBoxLayout[5].addWidget(&pushButton_submit);
    leftVBoxLayout.addLayout(&leftHBoxLayout[5]);
    leftVBoxLayout.addStretch();

    label_result.setFont(font);
    label_result.setText(QString("查询结果"));
    rightVBoxLayout.addWidget(&label_result);

    tableView.setModel(&queryModel);
    rightVBoxLayout.addWidget(&tableView);

    pushButon_query.setFont(font);
    pushButon_query.setText(QString("查询车位租售"));
    connect(&pushButon_query, SIGNAL(clicked(bool)), this, SLOT(slot_query()));
    rightHBoxLayout.addStretch();
    rightHBoxLayout.addWidget(&pushButon_query);
    rightVBoxLayout.addLayout(&rightHBoxLayout);

    wholeHBoxLayout.addLayout(&leftVBoxLayout, 1);
    wholeHBoxLayout.addLayout(&rightVBoxLayout, 2);
    setLayout(&wholeHBoxLayout);
}

void EmployeeParkingSpaceWidget::slot_submit()
{
    qDebug() << "EmployeeParkingSpaceWidget::slot_submit()";
    DBHelper db;
    if (!db.open()){
        qDebug() << "打开失败 EmployeeParkingSpaceWidget::slot_submit()";
        return;
    }
    QString local = lineEdit_local.text();
    int price = spinBox_prince.value();
    double width = doubleSpinBox_width.value();
    double height = doubleSpinBox_height.value();
    QString status = comboBox_status.currentText();
    QString sql = "insert into parkingSpaceAccount(local, price, width, height, status, ownerId) values('"
            + local + "', "
            + QString::number(price) + ", "
            + QString::number(width) + ", "
            + QString::number(height) + ", "
            + "'" + status + "', "
            + "null)";
    qDebug() << sql;
    QSqlQuery query = db.getQuery();
    if (!query.exec(sql)){
        qDebug() << "执行失败 EmployeeParkingSpaceWidget::slot_submit()";
        db.close();
        return;
    }
    db.close();
    QMessageBox::information(this, QString("提交"), QString("提交成功"), QMessageBox::Ok);
}

void EmployeeParkingSpaceWidget::slot_query()
{
    qDebug() << "EmployeeParkingSpaceWidget::slot_submit()";
    QString sql = "select id as 'ID', price as '价格',"
                  "width as '宽度', height as '长度', status as '状态', "
                  "local as '地点', ownerId as '业主(若已租出或售出)' from parkingSpaceAccount";
    qDebug() << sql;
    queryModel.setQuery(sql);
    tableView.resizeColumnToContents(0);
}
