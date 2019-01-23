#ifndef OWNERPARKINGSPACEWIDGET_H
#define OWNERPARKINGSPACEWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class OwnerApplyParkingSpaceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OwnerApplyParkingSpaceWidget(QWidget *parent = 0);

    void setUser(QString userName, int userId);

private:
    QSqlQueryModel queryModel;
    QTableView tableView;
    QPushButton pushButton_apply, pushButton_query;
    QHBoxLayout hBoxLayout;
    QVBoxLayout vBoxLayout;

    QString userName;
    int userId;

signals:

public slots:
    void slot_apply();
    void slot_query();

    void slot_tableViewClicked(const QModelIndex index);
};

#endif // OWNERPARKINGSPACEWIDGET_H
