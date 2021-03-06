#ifndef EMPLOYEEREGISTERWIDGET_H
#define EMPLOYEEREGISTERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "dbhelper.h"

namespace Ui {
class EmployeeRegisterWidget;
}

class EmployeeRegisterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EmployeeRegisterWidget(QWidget *parent = 0);
    ~EmployeeRegisterWidget();

    void setRole(DBHelper::Role role);

private:
    Ui::EmployeeRegisterWidget *ui;
    QLabel label_name, label_phone, label_password, label_confirm, label_homeAddress;
    QLineEdit lineEdit_name, lineEdit_phone, lineEdit_password, lineEdit_confirm, lineEdit_homeAddress;
    QPushButton pushButton_submit_employee;
    QHBoxLayout hBoxLayout[6];
    QVBoxLayout vBoxLayout;

    DBHelper::Role role;

public slots:
    void slot_submit_employee();
};

#endif // EMPLOYEEREGISTERWIDGET_H
