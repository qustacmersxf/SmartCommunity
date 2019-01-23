#ifndef OWNERPARKINGSPACEAPPLYINGWIDGET_H
#define OWNERPARKINGSPACEAPPLYINGWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class OwnerParkingSpaceApplyingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OwnerParkingSpaceApplyingWidget(QWidget *parent = 0);

    void setUser(QString userName, int userId);

private:
    QSqlQueryModel queryModel;
    QTableView tableView;
    QPushButton pushButton_query;
    QHBoxLayout hBoxLayout;
    QVBoxLayout vBoxLayout;

    QString userName;
    int userId;

signals:

public slots:
    void slot_query();
};

#endif // OWNERPARKINGSPACEAPPLYINGWIDGET_H
