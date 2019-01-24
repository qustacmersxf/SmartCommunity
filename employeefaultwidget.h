#ifndef EMPLOYEEFAULTWIDGET_H
#define EMPLOYEEFAULTWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlQueryModel>
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class EmployeeFaultWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EmployeeFaultWidget(QWidget *parent = 0);

private:
    QSqlQueryModel queryModel;
    QTableView tableView;
    QPushButton pushButton_dealWith, pushButton_query;
    QHBoxLayout hBoxLayout;
    QVBoxLayout vBoxLayout;

signals:

public slots:
    void slot_dealWith();
    void slot_query();

    void slot_tableViewClicked(const QModelIndex index);
};

#endif // EMPLOYEEFAULTWIDGET_H
