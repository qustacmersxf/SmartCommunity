#ifndef ATTENDENCEMANAGEMENT_H
#define ATTENDENCEMANAGEMENT_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
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
    QLabel label_condition, label_result, label_name;
    QLineEdit lineEdit_name;
    QVBoxLayout leftVBoxLayout, rightVBoxLayout;
    QHBoxLayout leftHBoxLayout[3], wholeBoxLayout;
    QRadioButton radioButton[2];
    QButtonGroup buttonGroup;
    QPushButton pushButton_fakeStrip;
    QSqlQueryModel queryModel;
    QTableView tableView;


signals:

public slots:
    void slot_fakeStrip();
    void slot_tableViewDoubleClicked(const QModelIndex inde);
    void slot_tableViewClicked(const QModelIndex index);
};

#endif // ATTENDENCEMANAGEMENT_H
