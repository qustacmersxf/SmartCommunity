#ifndef EMPLOYEEATTENDENCEWIDGET_H
#define EMPLOYEEATTENDENCEWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QTableView>
#include <QPushButton>
#include <QVBoxLayout>

class EmployeeAttendenceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EmployeeAttendenceWidget(QWidget *parent = 0);

    void setUserId(int userID);

private:
    QSqlQueryModel queryModel;
    QTableView tableView;
    QPushButton pushButton_signIn, pushButton_query;
    QHBoxLayout hBoxLayout;
    QVBoxLayout layout;

    int userId;

signals:

public slots:
    void slot_signIn();
    void slot_query();
};

#endif // EMPLOYEEATTENDENCEWIDGET_H
