#include "loginview.h"
#include "ui_loginview.h"
#include "dbhelper.h"
#include <QString>
#include <QFont>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>

LoginView::LoginView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginView)
{
    qDebug() << "LoginView() start";
    ui->setupUi(this);
    setWindowTitle(QString("登录"));

    connect(&administratorView, SIGNAL(signal_quit()), this, SLOT(slot_quitFromMainWindow()));
    connect(&employeeView, SIGNAL(signal_quit()), this, SLOT(slot_quitFromMainWindow()));
    connect(&ownerView, SIGNAL(signal_quit()), this, SLOT(slot_quitFromMainWindow()));
    connect(this, SIGNAL(signal_loginToAdministratorView()), &administratorView, SLOT(slot_login()));
    connect(this, SIGNAL(signal_loginToEmployeeView()), &employeeView, SLOT(slot_login()));
    connect(this, SIGNAL(signal_loginToOwnerView()), &ownerView, SLOT(slot_login()));

    vBoxLayout.addStretch();

    label_system.setText(QString("智慧小区管理系统"));
    QFont font;
    font.setPointSize(18);
    label_system.setFont(font);
    hBoxLayout_system.addStretch();
    hBoxLayout_system.addWidget(&label_system);
    hBoxLayout_system.addStretch();
    vBoxLayout.addLayout(&hBoxLayout_system);
    vBoxLayout.addStretch();

    label_count.setText(QString("账号："));
    lineEdit_count.setPlaceholderText(QString("请用手机号登录"));
    hBoxLayout_count.addStretch();
    hBoxLayout_count.addWidget(&label_count);
    hBoxLayout_count.addWidget(&lineEdit_count);
    hBoxLayout_count.addStretch();
    vBoxLayout.addLayout(&hBoxLayout_count);

    label_password.setText(QString("密码："));
    lineEdit_password.setEchoMode(QLineEdit::Password);
    hBoxLayout_password.addStretch();
    hBoxLayout_password.addWidget(&label_password);
    hBoxLayout_password.addWidget(&lineEdit_password);
    hBoxLayout_password.addStretch();
    vBoxLayout.addLayout(&hBoxLayout_password);
    vBoxLayout.addStretch();

    QString str[3] = {"管理员", "工作人员", "业主"};
    hBoxLayout_radio.addStretch();
    for (int i=0; i<3; i++){
        radioButton[i].setText(str[i]);
        hBoxLayout_radio.addWidget(&radioButton[i]);
        buttonGroup.addButton(&radioButton[i], i);
    }
    hBoxLayout_radio.addStretch();
    vBoxLayout.addLayout(&hBoxLayout_radio);
    vBoxLayout.addStretch();

    pushButton_login.setText(QString("登录"));
    connect(&pushButton_login, SIGNAL(clicked(bool)), this, SLOT(slot_login()));
    hBoxLayout_button.addStretch();
    hBoxLayout_button.addWidget(&pushButton_login);
    pushButton_quit.setText(QString("退出"));
    connect(&pushButton_quit, SIGNAL(clicked(bool)), this, SLOT(slot_quit()));
    hBoxLayout_button.addStretch();
    hBoxLayout_button.addWidget(&pushButton_quit);
    hBoxLayout_button.addStretch();
    vBoxLayout.addLayout(&hBoxLayout_button);
    vBoxLayout.addStretch();

    setLayout(&vBoxLayout);
    setFixedSize(this->width(), this->height());
    qDebug() << "LoginView() end";
}

LoginView::~LoginView()
{
    delete ui;
}

void LoginView::slot_login()
{
    DBHelper dbHelper;
    if (dbHelper.open()){
        qDebug() << "数据库打开成功！";
        QString account = this->lineEdit_count.text(); //获取输入的账号，这里用手机号作为登录账号
        QString password = this->lineEdit_password.text();
        DBHelper::Role role = (DBHelper::Role)buttonGroup.checkedId();
        if(role < 0){
            QMessageBox::information(this, QString("错误"), QString("请选择登录身份"), QMessageBox::Ok);
            return;
        }
        QSqlQuery query = dbHelper.getQuery();
        QString sql = "";
        switch (role) {
        case DBHelper::Role::administrator:
            sql = "select password, name, id from user_administrator where phone = '" + account + "'";
            break;
        case DBHelper::Role::employee:
            sql = "select password, name, id from user_employee where phone = '" + account + "'";
            break;
        case DBHelper::Role::owner:
            sql = "select password, name, id from user_owner where phone = '" + account + "'";
            break;
        default:
            break;
        }
        query.exec(sql);
        qDebug() << sql;
        if (query.next()){
            QString password_db = query.value(0).toString();
            QString name_db = query.value(1).toString();
            qDebug() << name_db;
            int id = query.value(2).toInt();
            if (password.compare(password_db) == 0){
                qDebug() << "登录成功";/**替换为界面切换操作*/
                switch (role) {
                case DBHelper::Role::administrator:
                    administratorView.setUser(name_db, id);
                    administratorView.setWindowTitle("管理员界面-" + name_db);
                    administratorView.show();
                    administratorView.checkAskForLeave();
                    emit signal_loginToAdministratorView();
                    break;
                case DBHelper::Role::employee:
                    qDebug() << "LoginView::slot_login() id = " << id;
                    employeeView.setUser(name_db, id);
                    employeeView.setWindowTitle("工作人员界面-" + name_db);
                    employeeView.show();
                    emit signal_loginToEmployeeView();
                    break;
                case DBHelper::Role::owner:
                    qDebug() << "业主登录";
                    ownerView.setUser(name_db, id);
                    ownerView.setWindowTitle("业主界面-" + name_db);
                    ownerView.show();
                    emit signal_loginToOwnerView();
                    break;
                default:
                    break;
                }
                this->hide();
            }else{
                qDebug() << "密码不正确";
                QMessageBox::information(this, QString("错误"), QString("用户名或密码错误，请重新检查"), QMessageBox::Ok);
            }
        }else{
            qDebug() << "查询为空";
            QMessageBox::information(this, QString("错误"), QString("用户名或密码错误，请重新检查"), QMessageBox::Ok);
        }
        dbHelper.close();
    }else{
        qDebug() << "数据库打开失败！";
    }
}

void LoginView::slot_quit()
{
    close();
}

void LoginView::slot_quitFromMainWindow()
{
    lineEdit_count.clear();
    lineEdit_password.clear();
    /*QRadioButton *button = (QRadioButton*)buttonGroup.checkedButton();
    int checkedId = buttonGroup.checkedId();
    if (0 != button){
        qDebug() << "button != 0";
        buttonGroup.removeButton(button);
        button->setChecked(false);
        buttonGroup.addButton(button, checkedId);
    }else{
        qDebug() << "button == 0";
    }*/
    this->show();
}
