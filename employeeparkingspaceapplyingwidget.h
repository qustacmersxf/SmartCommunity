#ifndef EMPLOYEEPARKINGSPACEAPPLYINGWIDGET_H
#define EMPLOYEEPARKINGSPACEAPPLYINGWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlQueryModel>
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class EmployeeParkingSpaceApplyingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EmployeeParkingSpaceApplyingWidget(QWidget *parent = 0);

private:
    QSqlQueryModel queryModel;
    QTableView tableView;
    QPushButton pushButton_accept, pushButton_query;
    QHBoxLayout hBoxLayout;
    QVBoxLayout vBoxLayout;

signals:

public slots:
    void slot_accept();
    void slot_query();

    void slot_tableViewClicked(const QModelIndex index);
};

#endif // EMPLOYEEPARKINGSPACEAPPLYINGWIDGET_H
