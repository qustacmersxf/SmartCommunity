#include "loginview.h"
#include "ui_loginview.h"
#include "dbhelper.h"
#include <QString>
#include <QFont>
#include <QDebug>
#include <QSqlQuery>

LoginView::LoginView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginView)
{
    ui->setupUi(this);

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
    hBoxLayout_count.addStretch();
    hBoxLayout_count.addWidget(&label_count);
    hBoxLayout_count.addWidget(&lineEdit_count);
    hBoxLayout_count.addStretch();
    vBoxLayout.addLayout(&hBoxLayout_count);

    label_password.setText(QString("密码："));
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
        buttonGroup.addButton(&radioButton[i]);
    }
    hBoxLayout_radio.addStretch();
    vBoxLayout.addLayout(&hBoxLayout_radio);
    vBoxLayout.addStretch();

    pushButton_login.setText(QString("登录"));
    connect(&pushButton_login, SIGNAL(clicked(bool)), this, SLOT(slot_login(bool)));
    hBoxLayout_button.addStretch();
    hBoxLayout_button.addWidget(&pushButton_login);
    pushButton_quit.setText(QString("退出"));
    connect(&pushButton_quit, SIGNAL(clicked(bool)), this, SLOT(slot_quit(bool)));
    hBoxLayout_button.addStretch();
    hBoxLayout_button.addWidget(&pushButton_quit);
    hBoxLayout_button.addStretch();
    vBoxLayout.addLayout(&hBoxLayout_button);
    vBoxLayout.addStretch();

    setLayout(&vBoxLayout);
}

LoginView::~LoginView()
{
    delete ui;
}

void LoginView::slot_login(bool value)
{
    DBHelper dbHelper;
    if (dbHelper.open()){
        qDebug() << "数据库打开成功！";
        dbHelper.close();
    }else{
        qDebug() << "数据库打开失败！";
    }
}

void LoginView::slot_quit(bool value)
{
    close();
}
