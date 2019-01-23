#include "attendencemanagement.h"
#include <QFont>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QDate>
#include <vector>
#include "dbhelper.h"

AttendenceManagement::AttendenceManagement(QWidget *parent) : QWidget(parent)
{
    QFont font;
    font.setPointSize(12);

    label_condition.setText(QString("筛选条件"));
    label_condition.setFont(font);
    leftVBoxLayout.addWidget(&label_condition);
    qDebug() << "1";

    label_name.setText(QString("姓名："));
    label_name.setFont(font);
    lineEdit_name.setFont(font);
    leftHBoxLayout[0].addWidget(&label_name);
    leftHBoxLayout[0].addWidget(&lineEdit_name);

    radioButton[0].setText(QString("待审批"));
    radioButton[0].setFont(font);
    radioButton[1].setText(QString("已审批"));
    radioButton[1].setFont(font);
    leftHBoxLayout[1].addWidget(&radioButton[0]);
    leftHBoxLayout[1].addStretch();
    leftHBoxLayout[1].addWidget(&radioButton[1]);
    buttonGroup.addButton(&radioButton[0], 0);
    buttonGroup.addButton(&radioButton[1], 1);

    pushButton_fakeStrip.setText(QString("看假条"));
    pushButton_fakeStrip.setFont(font);
    connect(&pushButton_fakeStrip, SIGNAL(clicked(bool)), this, SLOT(slot_fakeStrip()));
    leftHBoxLayout[2].addStretch();
    leftHBoxLayout[2].addWidget(&pushButton_fakeStrip);

    leftVBoxLayout.addLayout(&leftHBoxLayout[0]);
    leftVBoxLayout.addLayout(&leftHBoxLayout[1]);
    leftVBoxLayout.addLayout(&leftHBoxLayout[2]);
    leftVBoxLayout.addStretch(1);
    qDebug() << "2";

    label_result.setText(QString("查询结果(状态:0/1/2分别表示待处理、已批准、已驳回)"));
    label_result.setFont(font);

    /*this->queryModel.setHeaderData(0, Qt::Horizontal, tr("ID"));
    this->queryModel.setHeaderData(1, Qt::Horizontal, QString("员工ID"));
    this->queryModel.setHeaderData(2, Qt::Horizontal, QString("员工姓名"));
    this->queryModel.setHeaderData(3, Qt::Horizontal, QString("请假原因"));
    this->queryModel.setHeaderData(4, Qt::Horizontal, QString("起始日期"));
    this->queryModel.setHeaderData(5, Qt::Horizontal, QString("截止日期"));
    this->queryModel.setHeaderData(6, Qt::Horizontal, QString("状态"));*/
    queryModel.setQuery("select reason, startDate, endDate, status, id as 'ID', employeeId as '员工ID',name as '姓名' "
                        " from fakestrip");
    tableView.setModel(&(this->queryModel));
    connect(&tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slot_tableViewDoubleClicked(QModelIndex)));
    connect(&tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_tableViewClicked(QModelIndex)));
    rightVBoxLayout.addWidget(&label_result);
    rightVBoxLayout.addWidget(&tableView);
    qDebug() << "4";

    wholeBoxLayout.addLayout(&leftVBoxLayout, 1);
    wholeBoxLayout.addLayout(&rightVBoxLayout, 2);
    setLayout(&wholeBoxLayout);
    qDebug() << "5";
}

void AttendenceManagement::slot_fakeStrip()
{
    qDebug() << "slot_fakeStrip()";

    QString sql = "select id as 'ID', employeeId as '员工ID',name as '姓名', "
                  "reason as '原因', startDate as '起始日期', endDate as '截止日期', "
                  "status as '状态' from fakestrip";
    std::vector<QString> conditions;
    int checkId = buttonGroup.checkedId();
    if (checkId >= 0){
        if (checkId == 0){
            conditions.push_back("status = 0");
        }else{
            conditions.push_back("status <> 0");
        }
    }
    QString name = lineEdit_name.text();
    if (!name.isEmpty()){
        conditions.push_back("name = '" + name + "'");
    }
    if (conditions.size() > 0){
        sql += " where " + conditions[0];
        for (unsigned int i=1; i<conditions.size(); i++){
            sql += ", " + conditions[i];
        }
    }
    qDebug() << sql;
    this->queryModel.setQuery(sql);

    QRadioButton *button = (QRadioButton*)buttonGroup.checkedButton();
    if (0 != button){
        qDebug() << "button != 0";
        buttonGroup.removeButton(button);
        button->setChecked(false);
        buttonGroup.addButton(button, checkId);
    }else{
        qDebug() << "button == 0";
    }
}

void AttendenceManagement::slot_tableViewDoubleClicked(const QModelIndex index)
{
    qDebug() << "slot_tableViewDoubleClicked()";
    if (index.isValid()){
        QSqlRecord recond = queryModel.record(index.row());
        int id = recond.value(0).toInt();
        int employeeId = recond.value(1).toInt();
        QString name = recond.value(2).toString();
        QString reason = recond.value(3).toString();
        QDate startDate = recond.value(4).toDate();
        QDate endDate = recond.value(5).toDate();
        int status = recond.value(6).toInt();
        qDebug() << "1";

        QString info = "    员工" + name +"，出于 " + reason + " 的原因，于" + startDate.toString("yyyy-MM-dd") + "至"
                + endDate.toString("yyyy-MM-dd")
                + "期间请假，";
        switch (status) {
        case 0:
            info += "望批准。";
            break;
        case 1:
            info += "已批准。";
            break;
        case 2:
            info += "已驳回。";
        default:
            break;
        }
        qDebug() << "2";
        QMessageBox::StandardButton button;
        if (0 == status){
            button = QMessageBox::question(this, QString("假条审批"),
                    info, QMessageBox::Yes | QMessageBox::No);
            QString sql = "";
            if (button == QMessageBox::No) {
                sql = "update fakestrip set status = 2 where id = " + QString::number(id);
                return;
            }
            else if (button == QMessageBox::Yes) {
                sql = "update fakestrip set status = 1 where id = " + QString::number(id);
            }
            DBHelper dbHelper;
            if (!dbHelper.open()){
                qDebug() << "数据库打开失败 AttendenceManagement::slot_tableViewDoubleClicked()";
                return;
            }
            qDebug() << "数据库打开成功";
            QSqlQuery query = dbHelper.getQuery();
            if (!query.exec(sql)){
                qDebug() << "执行失败 AttendenceManagement::slot_tableViewDoubleClicked() 1";
                dbHelper.close();
                return;
            }
            qDebug() << "执行成功";
            //在表attendencerecond中添加该员工从起始日期到截止日期的记录，状态为请假
            sql = "select * from attendencerecond where employeeId = " + QString::number(employeeId);
            qDebug() << sql;
            if (!query.exec(sql)){
                qDebug() << "执行失败 AttendenceManagement::slot_tableViewDoubleClicked() 2";
                dbHelper.close();
                return;
            }
            std::vector<int> ids;
            while (query.next()){
                QDate date = query.value(3).toDate();
                if (date >= startDate && date <= endDate){
                    ids.push_back(query.value(0).toInt());
                }
            }
            int n = ids.size();
            for (int i=0; i<n; i++){
                QString str = "update attendencerecond set status = 1 where id = " + QString::number(ids[i]);
                qDebug() << str;
                if (!query.exec(str)){
                    qDebug() << "执行失败 AttendenceManagement::slot_tableViewDoubleClicked() 3";
                    dbHelper.close();
                    return;
                }
            }
            dbHelper.close();
        }else{
            QMessageBox::question(this, QString("假条审批"), info, QMessageBox::Yes);
        }
    }
}

void AttendenceManagement::slot_tableViewClicked(const QModelIndex index)
{
    qDebug() << "slot_tableViewClicked()";
    tableView.selectRow(index.row());
}
