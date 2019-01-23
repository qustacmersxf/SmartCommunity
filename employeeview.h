#ifndef EMPLOYEEVIEW_H
#define EMPLOYEEVIEW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include "ownerlookingwidget.h"
#include "ownerregisterwidget.h"
#include "employeeaskforleaveWidget.h"
#include "employeeattendencewidget.h"
#include "employeeparkingspacewidget.h"
#include "employeeparkingspaceapplyingwidget.h"

namespace Ui {
class EmployeeView;
}

class EmployeeView : public QMainWindow
{
    Q_OBJECT

public:
    explicit EmployeeView(QWidget *parent = 0);
    ~EmployeeView();

    void closeEvent(QCloseEvent *event);

    void init_addOwnerManagementMenu();
    void init_addPersonalAttendenceManagementMenu();
    void init_addParkingSpaceManagementMenu();
    void init_tabWidget();
    void setUser(QString userName, int userId);

private:
    Ui::EmployeeView *ui;
    QMenu *menu_ownerManagement, *menu_personalAttendenceManagement;
    QMenu *menu_parkingSpaceManagement;
    QAction *action_ownerAdd, *action_ownerView, *action_ownerModify;
    QAction *action_askForLeave, *action_terminateLeave, *action_attendence;
    QAction *action_addParkingSpace, *action_dealWithParkingSpaceApply;
    QTabWidget *tabWidget;
    QLabel label_welcome;
    QHBoxLayout hBoxLayout;
    QWidget *widget_tabWiget;

    OwnerRegisterWidget ownerRegisterWidget;
    OwnerLookingWidget ownerLookingWidget;
    EmployeeAskForLeaveWidget employeeAskForLeaveWidget;
    EmployeeAttendenceWidget employeeAttendenceWidget;
    EmployeeParkingSpaceWidget employeeParkingSpaceWidget;
    EmployeeParkingSpaceApplyingWidget employeeParkingSpaceApplyingWidget;

    QString userName;
    int userId;

signals:
    void signal_quit();

public slots:
    void slot_ownerAdd();
    void slot_ownerView();
    void slot_ownerModify();
    void slot_askForLeave();
    void slot_terminateLeave();
    void slot_attendence();
    void slot_addParkingSpace();
    void slot_dealWithParkingSpaceApply();

    void slot_login();
};

#endif // EMPLOYEEVIEW_H
