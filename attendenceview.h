#ifndef ATTENDENCEVIEW_H
#define ATTENDENCEVIEW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPushButton>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QTableView>

class AttendenceView : public QWidget
{
    Q_OBJECT
public:
    explicit AttendenceView(QWidget *parent = 0);

private:
    void clearRedundentRecond();

private:
    QLabel label_condition, label_result, label_name, label_description;
    QLineEdit lineEdit_name;
    QPushButton pushButton_query;
    QHBoxLayout leftHBoxLayout[2], wholeBoxLayout;
    QVBoxLayout leftVBoxLayout, rightVBoxLayout;
    QSqlQueryModel queryModel;
    QTableView tableView;

signals:

public slots:
    void slot_query();
};

#endif // ATTENDENCEVIEW_H
