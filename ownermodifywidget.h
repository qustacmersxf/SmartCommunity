#ifndef OWNERMODIFYWIDGET_H
#define OWNERMODIFYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Ui {
class OwnerModifyWidget;
}

class OwnerModifyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OwnerModifyWidget(QWidget *parent = 0);
    ~OwnerModifyWidget();

    void setInfo(int id, QString name, QString phone, QString password, QString homeAddress);


private:
    Ui::OwnerModifyWidget *ui;
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

#endif // OWNERMODIFYWIDGET_H
