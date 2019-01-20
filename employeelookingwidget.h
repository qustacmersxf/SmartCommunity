#ifndef EMPLOYEELOOKINGWIDGET_H
#define EMPLOYEELOOKINGWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QTableView>
#include <QRadioButton>
#include <QButtonGroup>

namespace Ui {
class EmployeeLookingWidget;
}

class EmployeeLookingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EmployeeLookingWidget(QWidget *parent = 0);
    ~EmployeeLookingWidget();

private:
    Ui::EmployeeLookingWidget *ui;
    QLabel label_condition, label_result ,label_name, label_role, label_phone, label_homeAddress;
    QLineEdit lineEdit_name, lineEdit_role, lineEdit_phone, lineEdit_homeAddress;
    QRadioButton radioButton[3];
    QButtonGroup buttonGroup;
    QPushButton pushButton_query;
    QHBoxLayout leftHBoxLayout[6], wholeHBoxLayout;
    QVBoxLayout leftVBoxLayout, rightVBoxLayout;
    QSqlQueryModel queryModel;
    QTableView tableView;

public slots:
    void slot_query();
};

#endif // EMPLOYEELOOKINGWIDGET_H
