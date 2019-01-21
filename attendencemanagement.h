#ifndef ATTENDENCEMANAGEMENT_H
#define ATTENDENCEMANAGEMENT_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QTableView>
#include <QRadioButton>
#include <QButtonGroup>

class AttendenceManagement : public QWidget
{
    Q_OBJECT
public:
    explicit AttendenceManagement(QWidget *parent = 0);

private:
    QLabel label_condition, label_result;
    QVBoxLayout leftVBoxLayout[2];
    QVBoxLayout rightVBoxLayout;
    QRadioButton radioButton_[4];
    QPushButton pushButton_fakeStrip, pushButton_attendence;
    QSqlQueryModel queryModel;
    QTableView tableView;

signals:

public slots:
};

#endif // ATTENDENCEMANAGEMENT_H
