#ifndef EMPLOYEEMODIFYWIDGET_H
#define EMPLOYEEMODIFYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Ui {
class EmployeeModifyWidget;
}

class EmployeeModifyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EmployeeModifyWidget(QWidget *parent = 0);
    ~EmployeeModifyWidget();

private:
    Ui::EmployeeModifyWidget *ui;
    QLabel label_name, label_phone, label_password, label_confirm, label_homeAddress;
    QLineEdit lineEdit_name, lineEdit_phone, lineEdit_password, lineEdit_confirm, lineEdit_homeAddress;
    QPushButton pushButton_submit_employee;
    QHBoxLayout hBoxLayout[6];
    QVBoxLayout vBoxLayout;
};

#endif // EMPLOYEEMODIFYWIDGET_H
