#ifndef ADMINISTRATORVIEW_H
#define ADMINISTRATORVIEW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>

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

private:
    Ui::AdministratorView *ui;
    QMenu *menu_personelManagement;
    QAction *action_personelAdd, *action_personelView, *action_personelModify;

public slots:
    void slot_personelAdd();
    void slot_personelView();
    void slot_personelModify();
};

#endif // ADMINISTRATORVIEW_H
