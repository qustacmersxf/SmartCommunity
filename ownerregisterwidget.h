#ifndef OWNERREGISTERVIEW_H
#define OWNERREGISTERVIEW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "dbhelper.h"

namespace Ui {
class OwnerRegisterView;
}

class OwnerRegisterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OwnerRegisterWidget(QWidget *parent = 0);
    ~OwnerRegisterWidget();

private:
    Ui::OwnerRegisterView *ui;
    QLabel label_name, label_phone, label_password, label_confirm, label_homeAddress;
    QLineEdit lineEdit_name, lineEdit_phone, lineEdit_password, lineEdit_confirm, lineEdit_homeAddress;
    QPushButton pushButton_submit_owner;
    QHBoxLayout hBoxLayout[6];
    QVBoxLayout vBoxLayout;

public slots:
    void slot_submit_owner();
};

#endif // OWNERREGISTERVIEW_H
