#include <QDebug>
#include <QApplication>
#include <QTextCodec>
#include "mainwindow.h"
#include "loginview.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));

    QApplication a(argc, argv);
    LoginView loginView;
    loginView.show();

    return a.exec();
}
