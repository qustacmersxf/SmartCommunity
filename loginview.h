#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QButtonGroup>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <dbhelper.h>
#include <administratorview.h>

namespace Ui {
class LoginView;
}

class LoginView : public QWidget
{
    Q_OBJECT

public:
    explicit LoginView(QWidget *parent = 0);
    ~LoginView();

private:
    Ui::LoginView *ui;
    QLabel label_system;
    QLabel label_count;
    QLabel label_password;
    QLineEdit lineEdit_count;
    QLineEdit lineEdit_password;
    QRadioButton radioButton[3];
    QButtonGroup buttonGroup;
    QPushButton pushButton_login;
    QPushButton pushButton_quit;
    QHBoxLayout hBoxLayout_system, hBoxLayout_count, hBoxLayout_password, hBoxLayout_radio, hBoxLayout_button;
    QVBoxLayout vBoxLayout;

    AdministratorView administratorView;

signals:


private slots:
    void slot_login();  //pushButton_login的相应槽函数，进行数据库查询与账号密码对比，并发射登录信号signal_loginToView()
    void slot_quit();
};

#endif // LOGINVIEW_H
