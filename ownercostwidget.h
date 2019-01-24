#ifndef OWNERCOSTWIDGET_H
#define OWNERCOSTWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class OwnerCostWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OwnerCostWidget(QWidget *parent = 0);

    void setUser(QString userName, int userId);

private:
    QSqlQueryModel queryModel;
    QTableView tableView;
    QPushButton pushButton_pay, pushButton_query;
    QHBoxLayout hBoxLayout;
    QVBoxLayout vBoxLayout;

    QString userName;
    int userId;

signals:

public slots:
    void slot_pay();
    void slot_query();

    void slot_tableViewClicked(const QModelIndex index);
};

#endif // OWNERCOSTWIDGET_H
