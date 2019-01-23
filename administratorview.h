#ifndef ADMINISTRATORVIEW_H
#define ADMINISTRATORVIEW_H

#include <QMainWindow>
#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QTabWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QCloseEvent>
#include "dbhelper.h"
#include "employeeregisterwidget.h"
#include "employeelookingwidget.h"
#include "attendencemanagement.h"
#include "attendenceview.h"

namespace Ui {
class AdministratorView;
}

class AdministratorView : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdministratorView(QWidget *parent = 0);
    ~AdministratorView();

    void closeEvent(QCloseEvent *event);

    void init_addPersonelMagementMenu();
    void init_addtendenceManagementMenu();
    void init_tabWidget();

    void checkAskForLeave();

    void setUser(QString userName, int userId);

private:
    Ui::AdministratorView *ui;
    QMenu *menu_personelManagement, *menu_attendenceManagement;
    QAction *action_personelAdd, *action_personelView, *action_personelModify;
    QAction *action_fakeView, *action_EAA/*审批*/, *action_attendenceView;
    QTabWidget *tabWidget;
    QLabel label_welcome;
    QHBoxLayout hBoxLayout;
    QWidget *widget_tabWiget;

    EmployeeRegisterWidget employeeRegisterWidget;
    EmployeeLookingWidget employeeLookingWidget;
    AttendenceManagement attendenceManagement;
    AttendenceView attendenceView;

    QString userName;
    int userId;

signals:
    void signal_quit();

public slots:
    void slot_personelAdd();
    void slot_personelView();
    void slot_personelModify();
    void slot_fakeView();
    void slot_EAA();
    void slot_attendenceView();
};

#endif // ADMINISTRATORVIEW_H
