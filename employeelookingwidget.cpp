#include "employeelookingwidget.h"
#include "ui_employeelookingwidget.h"

EmployeeLookingWidget::EmployeeLookingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmployeeLookingWidget)
{
    ui->setupUi(this);
}

EmployeeLookingWidget::~EmployeeLookingWidget()
{
    delete ui;
}
