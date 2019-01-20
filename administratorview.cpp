#include "administratorview.h"
#include "ui_administratorview.h"
#include <QMenuBar>
#include <QDebug>
#include <QFont>
#include <QMainWindow>
#include <QDialog>

AdministratorView::AdministratorView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdministratorView)
{
    ui->setupUi(this);

    init_addPersonelMagementMenu();
    init_tabWidget();

    setFixedSize(this->width(), this->height());
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

    //tabWidget->tabBar()->hide();

    hBoxLayout.addWidget(tabWidget);
    widget_tabWiget = new QWidget(this);
    widget_tabWiget->setLayout(&hBoxLayout);
    widget_tabWiget->resize(this->width(), this->height());
    widget_tabWiget->setGeometry(0, 20, this->width(), this->height()-20);
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
