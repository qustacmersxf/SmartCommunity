#ifndef OWNERFAULTAPPLYINGWIDGET_H
#define OWNERFAULTAPPLYINGWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "ownerfaultapplyingremarkwidget.h"

class OwnerFaultApplyingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OwnerFaultApplyingWidget(QWidget *parent = 0);

    void setUser(QString userName, int userId);

private:
    QSqlQueryModel queryModel;
    QTableView tableView;
    QPushButton pushButton_query, pushButton_remark;
    QHBoxLayout hBoxLayout;
    QVBoxLayout vBoxLayout;

    OwnerFaultApplyingRemarkWidget remarkWisget;

    QString userName;
    int userId;

signals:

public slots:
    void slot_query();
    void slot_remark();

    void slot_tableViewClicked(const QModelIndex index);
};

#endif // OWNERFAULTAPPLYINGWIDGET_H
