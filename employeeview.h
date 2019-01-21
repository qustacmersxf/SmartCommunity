#ifndef EMPLOYEEVIEW_H
#define EMPLOYEEVIEW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include "ownerlookingwidget.h"
#include "ownerregisterwidget.h"

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

    void init_addOwnerMagementMenu();
    void init_tabWidget();
    void setUser(QString userName, int userId);

private:
    Ui::EmployeeView *ui;
    QMenu *menu_ownerManagement;
    QAction *action_ownerAdd, *action_ownerView, *action_ownerModify;
    QTabWidget *tabWidget;
    QLabel label_welcome;
    QHBoxLayout hBoxLayout;
    QWidget *widget_tabWiget;
    OwnerRegisterWidget ownerRegisterWidget;
    OwnerLookingWidget ownerLookingWidget;

    QString userName;
    int userId;

signals:
    void signal_quit();

public slots:
    void slot_ownerAdd();
    void slot_ownerView();
    void slot_ownerModify();
};

#endif // EMPLOYEEVIEW_H
