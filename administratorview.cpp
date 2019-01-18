#include "administratorview.h"
#include "ui_administratorview.h"
#include <QMenuBar>
#include <QDebug>

AdministratorView::AdministratorView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdministratorView)
{
    ui->setupUi(this);
    setWindowTitle(QString("智慧小区-管理员：宋象飞"));//改为动态设置（可通过构造函数的参数来传递管理员姓名）
    qDebug() << "0";
    init_addPersonelMagementMenu();

    /*qDebug() << "1";
    tabWidget.addTab(new WelcomWidget, QString("欢迎"));
    qDebug() << "2";
    hBoxLayout.addWidget(&tabWidget);
    qDebug() << "3";
    setLayout(&hBoxLayout);
    qDebug() << "4";*/
}

AdministratorView::~AdministratorView()
{
    if (NULL != menu_personelManagement){
        delete menu_personelManagement;
        menu_personelManagement = NULL;
    }
    if (NULL != action_personelAdd){
        delete action_personelAdd;
        action_personelAdd = NULL;
    }
    if (NULL != action_personelView){
        delete action_personelView;
        action_personelView = NULL;
    }
    if (NULL != action_personelModify){
        delete action_personelModify;
        action_personelModify = NULL;
    }
    delete ui;
}

void AdministratorView::init_addPersonelMagementMenu()
{
    menu_personelManagement = menuBar()->addMenu(QString("人事管理"));
    if (NULL == menu_personelManagement){
        qDebug() << "menu_personelManagement添加失败";
        return;
    }

    action_personelAdd = new QAction(QString("人员添加"), this);
    action_personelAdd->setShortcut(QString("Ctrl+A"));
    //action_personelAdd->setIcon(QIcon(QString(""))); //添加图标
    connect(action_personelAdd, &QAction::triggered, this, &AdministratorView::slot_personelAdd);
    menu_personelManagement->addAction(action_personelAdd);

    action_personelView = new QAction(QString("人员查看"), this);
    action_personelView->setShortcut(QString("Ctrl+V"));
    //action_personelAdd->setIcon(QIcon(QString(""))); //添加图标
    connect(action_personelView, &QAction::triggered, this, &AdministratorView::slot_personelView);
    menu_personelManagement->addAction(action_personelView);

    action_personelModify = new QAction(QString("人员修改"), this);
    action_personelModify->setShortcut(QString("Ctrl+M"));
    //action_personelAdd->setIcon(QIcon(QString(""))); //添加图标
    connect(action_personelModify, &QAction::triggered, this, &AdministratorView::slot_personelModify);
    menu_personelManagement->addAction(action_personelModify);
}

void AdministratorView::slot_personelAdd()
{
    qDebug() << "slot_personelAdd()";
}

void AdministratorView::slot_personelView()
{
    qDebug() << "slot_personelView()";
}

void AdministratorView::slot_personelModify()
{
    qDebug() << "slot_personelModify()";
}
