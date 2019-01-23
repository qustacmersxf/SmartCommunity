#ifndef EMPLOYEEPERSONALATTENDENCEMANAGEMENT_H
#define EMPLOYEEPERSONALATTENDENCEMANAGEMENT_H

#include <QWidget>
#include <QLabel>
#include <QLine>
#include <QTextEdit>
#include <QPushButton>
#include <QDateEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>

class EmployeeAskForLeaveWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EmployeeAskForLeaveWidget(QWidget *parent = 0);

    void setUser(QString userName, int userId);

private:
    QLabel label_date, label_spliter, label_reason;
    QDateEdit dateEdit_start, dateEdit_end;
    QTextEdit textEdit_reason;
    QPushButton pushButton_submit, pushButton_cancel;
    QHBoxLayout hBoxLayout[3];
    QVBoxLayout vBoxLayout;

    QString userName;
    int userId;

signals:

public slots:
    void slot_submit();
    void slot_cancel();
};

#endif // EMPLOYEEPERSONALATTENDENCEMANAGEMENT_H
