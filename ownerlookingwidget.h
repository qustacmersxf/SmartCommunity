#ifndef OWNERLOOKINGWIDGET_H
#define OWNERLOOKINGWIDGET_H

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

#include "ownermodifywidget.h"

namespace Ui {
class OwnerLookingWidget;
}

class OwnerLookingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OwnerLookingWidget(QWidget *parent = 0);
    ~OwnerLookingWidget();

private:
    Ui::OwnerLookingWidget *ui;
    QLabel label_condition, label_result ,label_name, label_role, label_phone, label_homeAddress;
    QLineEdit lineEdit_name, lineEdit_role, lineEdit_phone, lineEdit_homeAddress;
    QPushButton pushButton_query, pushButton_delete;
    QHBoxLayout leftHBoxLayout[4], wholeHBoxLayout, rightHBoxLayout;
    QVBoxLayout leftVBoxLayout, rightVBoxLayout;
    QSqlQueryModel queryModel;
    QTableView tableView;

    OwnerModifyWidget ownerModifyWidget;

public slots:
    void slot_query();
    void slot_tableViewDoubleClicked(const QModelIndex index);
    void slot_tableViewClicked(const QModelIndex index);
    void slot_submitSuccess();
    void slot_delete();
};

#endif // OWNERLOOKINGWIDGET_H
