#ifndef EMPLOYEECOSTWIDGET_H
#define EMPLOYEECOSTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QTableView>
#include <QRadioButton>
#include <QButtonGroup>

class EmployeeCostWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EmployeeCostWidget(QWidget *parent = 0);

private:
    QLabel label_condition, label_result ,label_name, label_type;
    QLineEdit lineEdit_name;
    QComboBox comboBox_type;
    QPushButton pushButton_query, pushButton_remind;
    QHBoxLayout leftHBoxLayout[4], wholeHBoxLayout, rightHBoxLayout;
    QVBoxLayout leftVBoxLayout, rightVBoxLayout;
    QSqlQueryModel queryModel;
    QTableView tableView;

signals:

public slots:
    void slot_query();
    void slot_tableViewClicked(const QModelIndex index);
    void slot_submitSuccess();
    void slot_remind();
};

#endif // EMPLOYEECOSTWIDGET_H
