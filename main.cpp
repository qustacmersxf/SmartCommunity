#include "mainwindow.h"
#include "loginview.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginView loginView;
    loginView.show();

    return a.exec();
}
