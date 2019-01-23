#include <QMessageBox>
#include <QCloseEvent>
#include <QDebug>
#include <QFont>
#include "ownerview.h"
#include "ui_ownerview.h"

OwnerView::OwnerView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OwnerView)
{
    qDebug() << "OwnerView::OwnerView() 1";
    ui->setupUi(this);

    init_addParkingSpaceManagementMenu();
    init_tabWidget();
}

OwnerView::~OwnerView()
{
    if (NULL != menu_parkingSpaceManagement){
        delete menu_parkingSpaceManagement;
        menu_parkingSpaceManagement = NULL;
    }
    if (NULL != widget_tabWiget){
        delete widget_tabWiget;
        widget_tabWiget = NULL;
    }
    if (NULL != action_applyParkingSpace){
        delete action_applyParkingSpace;
        action_applyParkingSpace = NULL;
    }
    if (NULL != action_myParkingSpaceApplying){
        delete action_myParkingSpaceApplying;
        action_myParkingSpaceApplying = NULL;
    }
    delete ui;
}

void OwnerView::init_addParkingSpaceManagementMenu()
{
    menu_parkingSpaceManagement = menuBar()->addMenu(QString("车位管理"));
    if (NULL == menu_parkingSpaceManagement){
        qDebug() << "menu_ownerManagement添加失败";
        return;
    }

    action_applyParkingSpace = new QAction(QString("添加车位"));
    connect(action_applyParkingSpace, &QAction::triggered, this, &OwnerView::slot_applyParkingSpace);
    menu_parkingSpaceManagement->addAction(action_applyParkingSpace);

    action_myParkingSpaceApplying = new QAction(QString("我的车位申请"));
    connect(action_myParkingSpaceApplying, &QAction::triggered, this, &OwnerView::slot_myParkingSpaceApplying);
    menu_parkingSpaceManagement->addAction(action_myParkingSpaceApplying);
}

void OwnerView::init_tabWidget()
{
    QFont font;
    font.setPointSize(30);
    font.setFamily("华文彩云");

    label_welcome.setFont(font);
    label_welcome.setAlignment(Qt::AlignCenter);
    label_welcome.setText(QString("欢迎进入智慧小区系统"));
    tabWidget.addTab(&label_welcome, QString("欢迎"));

    tabWidget.addTab(&ownerApplyParkingSpaceWidget, QString("申请车位"));
    tabWidget.addTab(&myParkingSpaceApplyingWidget, QString("我的车位申请"));
    vBoxLayout.addWidget(&tabWidget);

    widget_tabWiget = new QWidget(this);
    widget_tabWiget->setLayout(&vBoxLayout);
    widget_tabWiget->resize(this->width(), this->height());
    widget_tabWiget->setGeometry(0, 20, this->width(), this->height()-20);
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
    ownerApplyParkingSpaceWidget.setUser(userName, userId);
    myParkingSpaceApplyingWidget.setUser(userName, userId);
}

void OwnerView::slot_applyParkingSpace()
{
    qDebug() << "OwnerView::slot_applyParkingSpace()";
    tabWidget.setCurrentIndex(1);
}

void OwnerView::slot_myParkingSpaceApplying()
{
    qDebug() << "OwnerView::slot_myParkingSpaceApplying()";
    tabWidget.setCurrentIndex(2);
}
