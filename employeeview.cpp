#include "employeeview.h"
#include "ui_employeeview.h"
#include <QDebug>
#include <QCloseEvent>

EmployeeView::EmployeeView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EmployeeView)
{
    ui->setupUi(this);

    init_addOwnerMagementMenu();
    init_tabWidget();

    setFixedSize(this->width(), this->height());
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
    delete ui;
}

void EmployeeView::init_addOwnerMagementMenu()
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

    tabWidget->tabBar()->hide();

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
