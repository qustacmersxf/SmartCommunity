#ifndef EMPLOYEELOOKINGWIDGET_H
#define EMPLOYEELOOKINGWIDGET_H

#include <QWidget>

namespace Ui {
class EmployeeLookingWidget;
}

class EmployeeLookingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EmployeeLookingWidget(QWidget *parent = 0);
    ~EmployeeLookingWidget();

private:
    Ui::EmployeeLookingWidget *ui;
};

#endif // EMPLOYEELOOKINGWIDGET_H
