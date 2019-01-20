#include <QDebug>
#include <QApplication>
#include "mainwindow.h"
#include "loginview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginView loginView;
    loginView.show();

    return a.exec();
}
