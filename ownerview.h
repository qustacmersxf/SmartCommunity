#ifndef OWNERVIEW_H
#define OWNERVIEW_H

#include <QMainWindow>
#include <QTabWidget>

namespace Ui {
class OwnerView;
}

class OwnerView : public QMainWindow
{
    Q_OBJECT

public:
    explicit OwnerView(QWidget *parent = 0);
    ~OwnerView();

    void closeEvent(QCloseEvent *event);

    void setUser(QString userName, int userId);

signals:
    void signal_quit();

private:
    QTabWidget tabWidget;

    QString userName;
    int userId;

private:
    Ui::OwnerView *ui;
};

#endif // OWNERVIEW_H
