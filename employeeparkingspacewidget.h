#ifndef EMPLOYEEPARKINGSPACEWIDGET_H
#define EMPLOYEEPARKINGSPACEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QSqlQueryModel>
#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>

class EmployeeParkingSpaceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EmployeeParkingSpaceWidget(QWidget *parent = 0);

private:
    QLabel label_addParkingSpace, label_local, label_price, label_width, label_height, label_status, label_result;
    QLineEdit lineEdit_local;
    QSpinBox spinBox_prince;
    QComboBox comboBox_status;
    QDoubleSpinBox doubleSpinBox_width, doubleSpinBox_height;
    QPushButton pushButton_submit, pushButon_query;
    QSqlQueryModel queryModel;
    QTableView tableView;
    QVBoxLayout leftVBoxLayout, rightVBoxLayout;
    QHBoxLayout leftHBoxLayout[6], rightHBoxLayout, wholeHBoxLayout;

signals:

public slots:
    void slot_submit();
    void slot_query();
};

#endif // EMPLOYEEPARKINGSPACEWIDGET_H
