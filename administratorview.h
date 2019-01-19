#ifndef ADMINISTRATORVIEW_H
#define ADMINISTRATORVIEW_H

#include <QMainWindow>
#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QTabWidget>
#include <QLabel>
#include <QHBoxLayout>
#include "employeeregisterwidget.h"

namespace Ui {
class AdministratorView;
}

class AdministratorView : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdministratorView(QWidget *parent = 0);
    ~AdministratorView();

    void init_addPersonelMagementMenu();
    void init_tabWidget();

private:
    Ui::AdministratorView *ui;
    QMenu *menu_personelManagement;
    QAction *action_personelAdd, *action_personelView, *action_personelModify;
    QTabWidget *tabWidget;
    QLabel label_welcome;
    QHBoxLayout hBoxLayout;
    QWidget *widget_tabWiget;
    EmployeeRegisterWidget employeeRegisterWidget;

public slots:
    void slot_personelAdd();
    void slot_personelView();
    void slot_personelModify();
};

#endif // ADMINISTRATORVIEW_H
