#include "employeemodifywidget.h"
#include "ui_employeemodifywidget.h"

EmployeeModifyWidget::EmployeeModifyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmployeeModifyWidget)
{
    ui->setupUi(this);
}

EmployeeModifyWidget::~EmployeeModifyWidget()
{
    delete ui;
}
