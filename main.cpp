#include "mainwindow.h"
#include "loginview.h"
#include "administratorview.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AdministratorView administratorView;
    administratorView.show();

    return a.exec();
}
