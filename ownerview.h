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
    void init_tabWidget();

    void closeEvent(QCloseEvent *event);

    void setUser(QString userName, int userId);

signals:
    void signal_quit();

private:
    Ui::OwnerView *ui;
    QMenu *menu_parkingSpaceManagement;
    QAction *action_applyParkingSpace, *action_myParkingSpaceApplying;
    QLabel label_welcome;
    QTabWidget tabWidget;
    QVBoxLayout vBoxLayout;
    QWidget *widget_tabWiget;

    OwnerApplyParkingSpaceWidget ownerApplyParkingSpaceWidget;
    OwnerParkingSpaceApplyingWidget myParkingSpaceApplyingWidget;

    QString userName;
    int userId;

public slots:
    void slot_applyParkingSpace();
    void slot_myParkingSpaceApplying();
};

#endif // OWNERVIEW_H
