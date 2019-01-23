#include <QMessageBox>
#include <QCloseEvent>
#include "ownerview.h"
#include "ui_ownerview.h"

OwnerView::OwnerView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OwnerView)
{
    ui->setupUi(this);
}

OwnerView::~OwnerView()
{
    delete ui;
}

void OwnerView::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, tr("退出程序"),
        QString(tr("是否返回登录界面？")),
        QMessageBox::Yes | QMessageBox::No);

    if (button == QMessageBox::No) {
        event->ignore();  //忽略退出信号，程序继续运行
    }
    else if (button == QMessageBox::Yes){
        emit signal_quit();
        event->accept();  //接受退出信号，程序退出
    }
}

void OwnerView::setUser(QString userName, int userId)
{
    this->userName = userName;
    this->userId = userId;
}
