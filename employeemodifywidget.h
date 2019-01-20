#ifndef EMPLOYEEMODIFYWIDGET_H
#define EMPLOYEEMODIFYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class EmployeeModifyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EmployeeModifyWidget(QWidget *parent = 0);

    void setInfo(int id, QString name, QString phone, QString password, QString homeAddress);

private:
    QLabel label_name, label_phone, label_password,label_homeAddress;
    QLineEdit lineEdit_name, lineEdit_phone, lineEdit_password, lineEdit_homeAddress;
    QPushButton pushButton_submit, pushButton_cancel;
    QHBoxLayout hBoxLayout[5];
    QVBoxLayout vBoxLayout;

    int id;

signals:
    void signal_submitSuccess();

public slots:
    void slot_submit();
    void slot_cancel();
};

#endif // EMPLOYEEMODIFYWIDGET_H
