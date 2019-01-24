#include <QMessageBox>
#include <QCloseEvent>
#include <QDebug>
#include <QFont>
#include <QDate>
#include "ownerview.h"
#include "ui_ownerview.h"
#include "dbhelper.h"

OwnerView::OwnerView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OwnerView)
{
    qDebug() << "OwnerView::OwnerView() 1";
    ui->setupUi(this);

    init_addParkingSpaceManagementMenu();
    init_addFautlManagementMenu();
    init_tabWidget();
}

OwnerView::~OwnerView()
{
    if (NULL != widget_tabWiget){
        delete widget_tabWiget;
        widget_tabWiget = NULL;
    }
    if (NULL != menu_parkingSpaceManagement){
        delete menu_parkingSpaceManagement;
        menu_parkingSpaceManagement = NULL;
    }
    if (NULL != action_applyParkingSpace){
        delete action_applyParkingSpace;
        action_applyParkingSpace = NULL;
    }
    if (NULL != action_myParkingSpaceApplying){
        delete action_myParkingSpaceApplying;
        action_myParkingSpaceApplying = NULL;
    }
    if (NULL != menu_faultManage){
        delete menu_faultManage;
        menu_faultManage = NULL;
    }
    if (NULL != action_applyFault){
        delete action_applyFault;
        action_applyFault = NULL;
    }
    if (NULL != action_myFaultApplying){
        delete action_myFaultApplying;
        action_myFaultApplying = NULL;
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

    action_cost = new QAction(QString("缴费管理"));
    connect(action_cost, &QAction::triggered, this, &OwnerView::slot_cost);
    menu_parkingSpaceManagement->addAction(action_cost);
}

void OwnerView::init_addFautlManagementMenu()
{
    menu_faultManage = menuBar()->addMenu(QString("故障管理"));
    if (NULL == menu_parkingSpaceManagement){
        qDebug() << "menu_ownerManagement添加失败";
        return;
    }

    action_applyFault = new QAction(QString("故障报修"));
    connect(action_applyFault, &QAction::triggered, this, &OwnerView::slot_applyFault);
    menu_faultManage->addAction(action_applyFault);

    action_myFaultApplying = new QAction(QString("我的报修申请"));
    connect(action_myFaultApplying, &QAction::triggered, this, &OwnerView::slot_myFaultApplying);
    menu_faultManage->addAction(action_myFaultApplying);

    menu_faultManage->addAction(action_cost);
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
    tabWidget.addTab(&ownerApplyFaultWidget, QString("故障报修"));
    tabWidget.addTab(&ownerFaultApplyingWidget, QString("我的故障申请"));
    tabWidget.addTab(&ownerCoastWidget, QString("缴费管理"));
    tabWidget.hide();

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
    ownerApplyFaultWidget.setUser(userName, userId);
    ownerFaultApplyingWidget.setUser(userName, userId);
    ownerCoastWidget.setUser(userName, userId);
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

void OwnerView::slot_applyFault()
{
    qDebug() << "OwnerView::slot_applyFault()";
    tabWidget.setCurrentIndex(3);
}

void OwnerView::slot_myFaultApplying()
{
    qDebug() << "OwnerView::slot_myFaultApplying()";
    tabWidget.setCurrentIndex(4);
}

void OwnerView::slot_cost()
{
    tabWidget.setCurrentIndex(5);
}

void OwnerView::slot_login()
{
    qDebug() << "OwnerView::slot_login()";
    DBHelper db;
    if (!db.open()){
        qDebug() << "数据库打开失败 OwnerView::slot_login()";
        return;
    }
    QSqlQuery query = db.getQuery();
    QString sql = "select * from costaccount where status = '未缴费' and ownerId = "
            + QString::number(this->userId);
    qDebug() << sql;
    if (!query.exec(sql)){
        qDebug() << "执行失败 OwnerView::slot_login()";
        db.close();
        return;
    }
    if (query.next()){
        QMessageBox::information(this, QString("缴费"),
            QString("您有未缴费项，请到缴费界面缴费。"), QMessageBox::Ok);
    }
    db.close();
}
