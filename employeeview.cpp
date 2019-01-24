#include "employeeview.h"
#include "ui_employeeview.h"
#include <QDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDate>
#include <vector>
#include "dbhelper.h"

EmployeeView::EmployeeView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EmployeeView)
{
    ui->setupUi(this);

    init_addOwnerManagementMenu();
    init_addPersonalAttendenceManagementMenu();
    init_addParkingSpaceManagementMenu();
    init_tabWidget();

    setFixedSize(this->width(), this->height());
    qDebug() << "EmployeeView() end";
}

EmployeeView::~EmployeeView()
{
    if (NULL != menu_ownerManagement){
        delete menu_ownerManagement;
        menu_ownerManagement = NULL;
    }
    if (NULL != action_ownerAdd){
        delete action_ownerAdd;
        action_ownerAdd = NULL;
    }
    if (NULL != action_ownerView){
        delete action_ownerView;
        action_ownerView = NULL;
    }
    if (NULL != action_ownerModify){
        delete action_ownerModify;
        action_ownerModify = NULL;
    }

    if (NULL != menu_personalAttendenceManagement){
        delete menu_personalAttendenceManagement;
        menu_personalAttendenceManagement = NULL;
    }
    if (NULL != action_askForLeave){
        delete action_askForLeave;
        action_askForLeave = NULL;
    }
    if (NULL != action_terminateLeave){
        delete action_terminateLeave;
        action_terminateLeave = NULL;
    }
    if (NULL != action_attendence){
        delete action_attendence;
        action_attendence = NULL;
    }

    if (NULL != menu_parkingSpaceManagement){
        delete menu_parkingSpaceManagement;
        menu_parkingSpaceManagement = NULL;
    }
    if (NULL != action_addParkingSpace){
        delete action_addParkingSpace;
        action_addParkingSpace = NULL;
    }
    if (NULL != action_dealWithParkingSpaceApply){
        delete action_dealWithParkingSpaceApply;
        action_dealWithParkingSpaceApply = NULL;
    }

    delete ui;
}

void EmployeeView::init_addOwnerManagementMenu()
{
    menu_ownerManagement = menuBar()->addMenu(QString("物业管理"));
    if (NULL == menu_ownerManagement){
        qDebug() << "menu_ownerManagement添加失败";
        return;
    }

    action_ownerAdd = new QAction(QString("业主添加"), this);
    action_ownerAdd->setShortcut(QString("Ctrl+A"));
    //action_ownerAdd->setIcon(QIcon(QString(""))); //添加图标
    connect(action_ownerAdd, &QAction::triggered, this, &EmployeeView::slot_ownerAdd);
    menu_ownerManagement->addAction(action_ownerAdd);

    action_ownerView = new QAction(QString("业主查看"), this);
    action_ownerView->setShortcut(QString("Ctrl+V"));
    //action_ownerAdd->setIcon(QIcon(QString(""))); //添加图标
    connect(action_ownerView, &QAction::triggered, this, &EmployeeView::slot_ownerView);
    menu_ownerManagement->addAction(action_ownerView);

    action_ownerModify = new QAction(QString("业主修改"), this);
    action_ownerModify->setShortcut(QString("Ctrl+M"));
    //action_ownerAdd->setIcon(QIcon(QString(""))); //添加图标
    connect(action_ownerModify, &QAction::triggered, this, &EmployeeView::slot_ownerModify);
    menu_ownerManagement->addAction(action_ownerModify);

    action_ownerFault = new QAction(QString("故障报修管理"), this);
    //action_ownerAdd->setIcon(QIcon(QString(""))); //添加图标
    connect(action_ownerFault, &QAction::triggered, this, &EmployeeView::slot_ownerFault);
    menu_ownerManagement->addAction(action_ownerFault);
}

void EmployeeView::init_addPersonalAttendenceManagementMenu()
{
    menu_personalAttendenceManagement = menuBar()->addMenu(QString("个人出勤管理"));
    if (NULL == menu_personalAttendenceManagement){
        qDebug() << "menu_personalAttendenceManagement添加失败";
        return;
    }

    action_askForLeave = new QAction(QString("请假"));
    connect(action_askForLeave, &QAction::triggered, this, &EmployeeView::slot_askForLeave);
    menu_personalAttendenceManagement->addAction(action_askForLeave);

    action_terminateLeave = new QAction(QString("销假"));
    connect(action_terminateLeave, &QAction::triggered, this, &EmployeeView::slot_terminateLeave);
    menu_personalAttendenceManagement->addAction(action_terminateLeave);

    action_attendence = new QAction(QString("月度出勤"));
    connect(action_attendence, &QAction::triggered, this, &EmployeeView::slot_attendence);
    menu_personalAttendenceManagement->addAction(action_attendence);
}

void EmployeeView::init_addParkingSpaceManagementMenu()
{
    menu_parkingSpaceManagement = menuBar()->addMenu(QString("车位管理"));

    action_addParkingSpace = new QAction(QString("添加车位"));
    connect(action_addParkingSpace, &QAction::triggered, this, &EmployeeView::slot_addParkingSpace);
    menu_parkingSpaceManagement->addAction(action_addParkingSpace);

    action_dealWithParkingSpaceApply = new QAction(QString("车位申请处理"));
    connect(action_dealWithParkingSpaceApply, &QAction::triggered, this, &EmployeeView::slot_dealWithParkingSpaceApply);
    menu_parkingSpaceManagement->addAction(action_dealWithParkingSpaceApply);
}

void EmployeeView::init_tabWidget()
{
    label_welcome.setText(QString("欢迎进入智慧小区系统"));
    QFont font;
    font.setPointSize(30);
    font.setFamily("华文彩云");
    label_welcome.setFont(font);
    label_welcome.setAlignment(Qt::AlignCenter);
    tabWidget = new QTabWidget();

    tabWidget->addTab(&label_welcome, QString("欢迎"));
    tabWidget->addTab(&ownerRegisterWidget, QString("业主添加"));
    tabWidget->addTab(&ownerLookingWidget, QString("业主查看/修改"));
    tabWidget->addTab(&employeeAskForLeaveWidget, QString("请假"));
    tabWidget->addTab(&employeeAttendenceWidget, QString("查看出勤"));
    tabWidget->addTab(&employeeParkingSpaceWidget, QString("车位管理"));
    tabWidget->addTab(&employeeParkingSpaceApplyingWidget, QString("车位申请处理"));
    tabWidget->addTab(&employeeFaultWidget, QString("物业故障管理"));
    //tabWidget->tabBar()->hide();

    hBoxLayout.addWidget(tabWidget);
    widget_tabWiget = new QWidget(this);
    widget_tabWiget->setLayout(&hBoxLayout);
    widget_tabWiget->resize(this->width(), this->height());
    widget_tabWiget->setGeometry(0, 20, this->width(), this->height()-20);
}

void EmployeeView::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, tr("退出程序"),
        QString(tr("是否返回登录界面？")),
        QMessageBox::Yes | QMessageBox::No);

    if (button == QMessageBox::No) {
        event->ignore();  //忽略退出信号，程序继续运行
    }
    else if (button == QMessageBox::Yes) {
        emit signal_quit();
        event->accept();  //接受退出信号，程序退出
    }
}

void EmployeeView::setUser(QString userName, int userId)
{
    this->userName = userName;
    this->userId = userId;
    this->employeeAttendenceWidget.setUserId(userId);
    this->employeeAskForLeaveWidget.setUser(userName, userId);
}

void EmployeeView::slot_ownerAdd()
{
    qDebug() << "slot_ownerAdd()";
    tabWidget->setCurrentIndex(1);
}

void EmployeeView::slot_ownerView()
{
    qDebug() << "slot_ownerView()";
    tabWidget->setCurrentIndex(2);
}

void EmployeeView::slot_ownerModify()
{
    qDebug() << "slot_ownerModify()";
    tabWidget->setCurrentIndex(2);
}

void EmployeeView::slot_askForLeave()
{
    qDebug() << "slot_askForLeave()";
    tabWidget->setCurrentIndex(3);
}

void EmployeeView::slot_terminateLeave()
{
    qDebug() << "slot_terminateLeave()";
    DBHelper db;
    if (!db.open()){
        qDebug() << "数据库打开失败";
        return;
    }
    QSqlQuery query = db.getQuery();
    QString sql = "select * from fakestrip where employeeId = " + QString::number(this->userId)
            + " and status = 1";
    qDebug() << sql;
    if (!query.exec(sql)){
        qDebug() << "执行失败 EmployeeView::slot_terminateLeave() 1";
        db.close();
        return;
    }

    if (!query.next()){
        QMessageBox::information(this, QString("消息"), QString("您没有待销假的假条。"), QMessageBox::Ok);
        db.close();
        return;
    }
    int id = query.value(0).toInt();
    QString reason = query.value(3).toString();
    QString startDate = query.value(4).toString();
    QString endDate = query.value(5).toString();
    QString info = "您出于 " + reason + " 的原因，请了由" + startDate + "到" + endDate + "的假期，确定要销假吗？";
    QMessageBox::Button button = QMessageBox::question(this, QString("销假"),
            info, QMessageBox::Ok | QMessageBox::No);
    std::vector<int> ids;
    if (QMessageBox::Ok == button){
        QDate date = QDate::currentDate();
        sql = "select * from attendencerecond where status = 1 and employeeId = " + QString::number(this->userId);
        qDebug() << sql;
        if (!query.exec(sql)){
            qDebug() << "执行失败 EmployeeView::slot_terminateLeave() 2";
            db.close();
            return;
        }
        while (query.next()){
            QDate date_ = query.value(3).toDate();
            int id = query.value(0).toInt();
            if (date <= date_){
                ids.push_back(id);
            }
        }
        int n = ids.size();
        qDebug() << "n = " << n;
        for (int i=0; i<n; i++){
            sql = "update attendencerecond set status = 2 where id = " + QString::number(ids[i]);
            if (!query.exec(sql)){
                qDebug() << "执行失败 EmployeeView::slot_terminateLeave() 3";
                db.close();
                return;
            }
        }
        sql = "update fakestrip set status = 3 where id = " + QString::number(id);
        if (!query.exec(sql)){
            qDebug() << "执行失败 EmployeeView::slot_terminateLeave() 4";
            db.close();
            return;
        }
        QMessageBox::information(this, QString("销假"), QString("销假成功，请到“月度出勤”界面签到。"), QMessageBox::Ok);
    }
    db.close();
}

void EmployeeView::slot_attendence()
{
    qDebug() << "slot_attendence()";
    tabWidget->setCurrentIndex(4);
}

void EmployeeView::slot_addParkingSpace()
{
    qDebug() << "EmployeeView::slot_parkingSpace()";
    tabWidget->setCurrentIndex(5);
}

void EmployeeView::slot_ownerFault()
{
    tabWidget->setCurrentIndex(7);
}

void EmployeeView::slot_dealWithParkingSpaceApply()
{
    qDebug() << "EmployeeView::slot_dealWithParkingSpaceApply()";
    tabWidget->setCurrentIndex(6);
}

void EmployeeView::slot_login()
{
    qDebug() << "slot_login()";
    QDate currentDate = QDate::currentDate();
    DBHelper db;
    if (!db.open()){
        qDebug() << "数据库打开失败 EmployeeView::slot_login()";
        return;
    }
    QSqlQuery query = db.getQuery();
    QString sql = "select status from attendencerecond where employeeId = " + QString::number(this->userId)
            + " and attendentDate = '" + currentDate.toString("yyyy-MM-dd") + "'";
    qDebug() << sql;
    if (!query.exec(sql)){
        qDebug() << "执行失败 EmployeeView::slot_login()";
        db.close();
        return;
    }
    if (!query.next()){
        qDebug() << "查询为空 EmployeeView::slot_login()";
        db.close();
        return ;
    }
    if (0 != query.value(0).toInt()){
        QMessageBox::information(this, QString("小提示"), QString("您今日还未签到，请到“月度出勤”界面签到。"),
                                 QMessageBox::Ok);
    }

    db.close();
}


