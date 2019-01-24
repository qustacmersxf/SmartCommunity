#ifndef OWNERVIEW_H
#define OWNERVIEW_H

#include <QMainWindow>
#include <QLabel>
#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QTabWidget>
#include <QVBoxLayout>
#include "ownerapplyparkingspacewidget.h"
#include "ownerparkingspaceapplyingwidget.h"
#include "ownerapplyfaultwidget.h"
#include "ownerfaultapplyingwidget.h"
#include "ownercostwidget.h"

namespace Ui {
class OwnerView;
}

class OwnerView : public QMainWindow
{
    Q_OBJECT

public:
    explicit OwnerView(QWidget *parent = 0);
    ~OwnerView();

    void init_addParkingSpaceManagementMenu();
    void init_addFautlManagementMenu();
    void init_tabWidget();

    void closeEvent(QCloseEvent *event);

    void setUser(QString userName, int userId);

signals:
    void signal_quit();

private:
    Ui::OwnerView *ui;
    QMenu *menu_parkingSpaceManagement;
    QAction *action_applyParkingSpace, *action_myParkingSpaceApplying;
    QMenu *menu_faultManage;
    QAction *action_applyFault, *action_myFaultApplying;
    QAction *action_cost;
    QLabel label_welcome;
    QTabWidget tabWidget;
    QVBoxLayout vBoxLayout;
    QWidget *widget_tabWiget;

    OwnerApplyParkingSpaceWidget ownerApplyParkingSpaceWidget;
    OwnerParkingSpaceApplyingWidget myParkingSpaceApplyingWidget;
    OwnerApplyFaultWidget ownerApplyFaultWidget;
    OwnerFaultApplyingWidget ownerFaultApplyingWidget;
    OwnerCostWidget ownerCoastWidget;

    QString userName;
    int userId;

public slots:
    void slot_applyParkingSpace();
    void slot_myParkingSpaceApplying();
    void slot_applyFault();
    void slot_myFaultApplying();
    void slot_cost();

    void slot_login();
};

#endif // OWNERVIEW_H
