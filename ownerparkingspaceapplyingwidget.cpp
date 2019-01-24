#include <QDebug>
#include "ownerparkingspaceapplyingwidget.h"

OwnerParkingSpaceApplyingWidget::OwnerParkingSpaceApplyingWidget(QWidget *parent) : QWidget(parent)
{
    qDebug() << "OwnerParkingSpaceApplyingWidget::OwnerParkingSpaceApplyingWidget() 1";
    QFont font;
    font.setPointSize(18);

    tableView.setModel(&queryModel);
    connect(&tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_tableViewClicked(QModelIndex)));
    vBoxLayout.addWidget(&tableView);
    qDebug() << "OwnerParkingSpaceApplyingWidget::OwnerParkingSpaceApplyingWidget() 2";

    pushButton_query.setFont(font);
    pushButton_query.setText(QString("查询"));
    connect(&pushButton_query, SIGNAL(clicked(bool)), this, SLOT(slot_query()));
    hBoxLayout.addStretch();
    hBoxLayout.addWidget(&pushButton_query);
    vBoxLayout.addLayout(&hBoxLayout);
    setLayout(&vBoxLayout);
    qDebug() << "OwnerParkingSpaceApplyingWidget::OwnerParkingSpaceApplyingWidget() 4";
}

void OwnerParkingSpaceApplyingWidget::setUser(QString userName, int userId)
{
    this->userName = userName;
    this->userId = userId;
}

void OwnerParkingSpaceApplyingWidget::slot_query()
{
    QString sql = "select parkingSpaceAccount.id as 'ID', local as '位置', "
                  "price as '价格', width as '宽度', "
                  "height as '长度', status as '状态', ownerId as '业主ID', name as '业主姓名' "
                  "from parkingSpaceAccount join user on parkingSpaceAccount.ownerId = user.id "
                  "where ownerId = " + QString::number(this->userId);
    qDebug() << sql;
    queryModel.setQuery(sql);
}
