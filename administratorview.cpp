#include "administratorview.h"
#include "ui_administratorview.h"
#include <QMenuBar>
#include <QDebug>
#include <QFont>
#include <QMainWindow>
#include <QDialog>
#include <QMessageBox>

AdministratorView::AdministratorView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdministratorView)
{
    ui->setupUi(this);

    init_addPersonelMagementMenu();
    init_tabWidget();
    init_addtendenceManagementMenu();

    employeeRegisterWidget.setRole(DBHelper::Role::employee);
    setFixedSize(this->width(), this->height());

    qDebug() << "AdministratorView() end";
}

AdministratorView::~AdministratorView()
{
    if (0 != menu_personelManagement){
        delete menu_personelManagement;
        menu_personelManagement = NULL;
    }
    if (0 != action_personelAdd){
        delete action_personelAdd;
        action_personelAdd = NULL;
    }
    if (0 != action_personelView){
        delete action_personelView;
        action_personelView = NULL;
    }
    if (0 != action_personelModify){
        delete action_personelModify;
        action_personelModify = NULL;
    }
    if (0 != action_fakeView){
        delete action_fakeView;
        action_fakeView = NULL;
    }
    if (0 != action_EAA){
        delete action_EAA;
        action_EAA = NULL;
    }
    if (0 != action_attendenceView){
        delete action_attendenceView;
        action_attendenceView = NULL;
    }
    delete ui;
}

void AdministratorView::init_addPersonelMagementMenu()
{
    menu_personelManagement = menuBar()->addMenu(QString("人事管理"));
    if (0 == menu_personelManagement){
        qDebug() << "menu_personelManagement添加失败";
        return;
    }

    action_personelAdd = new QAction(QString("人员添加"), this);
    if (0 != action_personelAdd){
        action_personelAdd->setShortcut(QString("Ctrl+A"));
        //action_personelAdd->setIcon(QIcon(QString(""))); //添加图标
        connect(action_personelAdd, &QAction::triggered, this, &AdministratorView::slot_personelAdd);
        menu_personelManagement->addAction(action_personelAdd);
    }

    action_personelView = new QAction(QString("人员查看"), this);
    if (0 != action_personelView){
        action_personelView->setShortcut(QString("Ctrl+V"));
        //action_personelAdd->setIcon(QIcon(QString(""))); //添加图标
        connect(action_personelView, &QAction::triggered, this, &AdministratorView::slot_personelView);
        menu_personelManagement->addAction(action_personelView);
    }

    action_personelModify = new QAction(QString("人员修改"), this);
    if (0 != action_personelModify){
        action_personelModify->setShortcut(QString("Ctrl+M"));
        //action_personelAdd->setIcon(QIcon(QString(""))); //添加图标
        connect(action_personelModify, &QAction::triggered, this, &AdministratorView::slot_personelModify);
        menu_personelManagement->addAction(action_personelModify);
    }
}

void AdministratorView::init_addtendenceManagementMenu()
{
    menu_attendenceManagement = menuBar()->addMenu(QString("考勤管理"));
    if (0 == menu_attendenceManagement){
        qDebug() << "menu_attendenceManagement添加失败";
        return;
    }

    action_fakeView = new QAction(QString("查看员工请假"), this);
    if (0 != action_fakeView){
        action_fakeView->setShortcut(QString("Ctrl+F+V"));
        connect(action_fakeView, &QAction::triggered, this, &AdministratorView::slot_fakeView);
        menu_attendenceManagement->addAction(action_fakeView);
    }

    action_EAA = new QAction(QString("员工请假审批"), this);
    if (0 != action_EAA){
        action_EAA->setShortcut(QString("Ctrl+F+V"));
        connect(action_EAA, &QAction::triggered, this, &AdministratorView::slot_EAA);
        menu_attendenceManagement->addAction(action_EAA);
    }

    action_attendenceView = new QAction(QString("查看员工出勤"), this);
    if (0 != action_attendenceView){
        action_attendenceView->setShortcut(QString("Ctrl+F+V"));
        connect(action_attendenceView, &QAction::triggered, this, &AdministratorView::slot_attendenceView);
        menu_attendenceManagement->addAction(action_attendenceView);
    }
}

void AdministratorView::init_tabWidget()
{
    label_welcome.setText(QString("欢迎进入智慧小区系统"));
    QFont font;
    font.setPointSize(30);
    font.setFamily("华文彩云");
    label_welcome.setFont(font);
    label_welcome.setAlignment(Qt::AlignCenter);
    tabWidget = new QTabWidget();
    tabWidget->addTab(&label_welcome, QString("欢迎"));

    tabWidget->addTab(&employeeRegisterWidget, QString("人员添加"));
    tabWidget->addTab(&employeeLookingWidget, QString("人员查看/修改"));
    tabWidget->addTab(&attendenceManagement, QString("请假管理"));
    tabWidget->addTab(&attendenceView, QString("出勤管理"));

    tabWidget->tabBar()->hide();

    hBoxLayout.addWidget(tabWidget);
    widget_tabWiget = new QWidget(this);
    widget_tabWiget->setLayout(&hBoxLayout);
    widget_tabWiget->resize(this->width(), this->height());
    widget_tabWiget->setGeometry(0, 20, this->width(), this->height()-20);
}

void AdministratorView::checkAskForLeave()
{
    DBHelper db;
    if (!db.open()){
        qDebug() << "数据库打开失败 AdministratorView::checkAskForLeave()";
        return;
    }
    QString sql = "select * from fakestrip where status = 0";
    qDebug() << sql;
    QSqlQuery query = db.getQuery();
    if (!query.exec(sql)){
        qDebug() << "执行失败 AdministratorView::checkAskForLeave()";
        db.close();
        return;
    }
    if (query.next()){
        QMessageBox::information(this, QString("待处理"), QString("您有假条未处理，请前往“员工请假审批”界面处理。"),
                                 QMessageBox::Ok);
    }
    db.close();
}

void AdministratorView::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, tr("退出程序"),
             QString(tr("是否返回登录界面？")),QMessageBox::Yes | QMessageBox::No);

    if (button == QMessageBox::No) {
        event->ignore();  //忽略退出信号，程序继续运行
    }
    else if (button == QMessageBox::Yes) {
        emit signal_quit();
        event->accept();  //接受退出信号，程序退出
    }
}

void AdministratorView::setUser(QString userName, int userId)
{
    this->userName = userName;
    this->userId = userId;
}

void AdministratorView::slot_personelAdd()
{
    qDebug() << "slot_personelAdd()";
    tabWidget->setCurrentIndex(1);
}

void AdministratorView::slot_personelView()
{
    qDebug() << "slot_personelView()";
    tabWidget->setCurrentIndex(2);
}

void AdministratorView::slot_personelModify()
{
    qDebug() << "slot_personelModify()";
    tabWidget->setCurrentIndex(2);
}

void AdministratorView::slot_fakeView()
{
    qDebug() << "slot_fakeView()";
    tabWidget->setCurrentIndex(3);
}

void AdministratorView::slot_EAA()
{
    qDebug() << "slot_EAA()";
    tabWidget->setCurrentIndex(3);
}

void AdministratorView::slot_attendenceView()
{
    qDebug() << "slot_attendenceView()";
    tabWidget->setCurrentIndex(4);
}
