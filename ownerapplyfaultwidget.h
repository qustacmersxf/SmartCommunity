#ifndef OWNERFAULTWIDGET_H
#define OWNERFAULTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class OwnerApplyFaultWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OwnerApplyFaultWidget(QWidget *parent = 0);

    void setUser(QString userName, int userId);

private:
    QTextEdit textEdit_fault;
    QPushButton pushButton_submit;
    QHBoxLayout hBoxLayout;
    QVBoxLayout vBoxLayout;

    QString userName;
    int userId;

signals:

public slots:
    void slot_submit();
};

#endif // OWNERFAULTWIDGET_H
