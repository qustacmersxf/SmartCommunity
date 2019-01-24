#ifndef OWNERFAULTAPPLYINGREMARKWIDGET_H
#define OWNERFAULTAPPLYINGREMARKWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class OwnerFaultApplyingRemarkWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OwnerFaultApplyingRemarkWidget(QWidget *parent = 0);

    void setUser(QString userName, int userId);
    void setFaultAccountId(int id);

private:
    QLabel label;
    QTextEdit textEdit_remark;
    QPushButton pushButton_submit;
    QHBoxLayout hBoxLayout;
    QVBoxLayout vBoxLayout;

    QString userName;
    int userId;
    int faultaccountId;


signals:
    signal_remarked();

public slots:
    void slot_submit();
};

#endif // OWNERFAULTAPPLYINGREMARKWIDGET_H
