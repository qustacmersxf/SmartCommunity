#-------------------------------------------------
#
# Project created by QtCreator 2019-01-15T21:27:10
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartCommunity
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    loginview.cpp \
    dbhelper.cpp \
    administratorview.cpp \
    employeeregisterwidget.cpp \
    employeelookingwidget.cpp \
    employeemodifywidget.cpp \
    employeeview.cpp \
    ownerlookingwidget.cpp \
    ownerregisterwidget.cpp \
    ownermodifywidget.cpp \
    attendencemanagement.cpp \
    attendenceview.cpp \
    employeeaskforleaveWidget.cpp \
    employeeattendencewidget.cpp \
    employeeparkingspacewidget.cpp \
    ownerview.cpp \
    ownercostwidget.cpp \
    employeeparkingspaceapplyingwidget.cpp \
    ownerapplyparkingspacewidget.cpp \
    ownerparkingspaceapplyingwidget.cpp \
    ownerapplyfaultwidget.cpp \
    ownerfaultapplyingwidget.cpp \
    ownerfaultapplyingremarkwidget.cpp \
    employeefaultwidget.cpp \
    employeecostwidget.cpp

HEADERS  += mainwindow.h \
    loginview.h \
    dbhelper.h \
    administratorview.h \
    employeeregisterwidget.h \
    employeelookingwidget.h \
    employeemodifywidget.h \
    employeeview.h \
    ownerlookingwidget.h \
    ownerregisterwidget.h \
    ownermodifywidget.h \
    attendencemanagement.h \
    attendenceview.h \
    employeeaskforleaveWidget.h \
    employeeattendencewidget.h \
    employeeparkingspacewidget.h \
    ownerview.h \
    ownercostwidget.h \
    employeeparkingspaceapplyingwidget.h \
    ownerapplyparkingspacewidget.h \
    ownerparkingspaceapplyingwidget.h \
    ownerapplyfaultwidget.h \
    ownerfaultapplyingwidget.h \
    ownerfaultapplyingremarkwidget.h \
    employeefaultwidget.h \
    employeecostwidget.h

FORMS    += mainwindow.ui \
    loginview.ui \
    administratorview.ui \
    employeeregisterwidget.ui \
    employeelookingwidget.ui \
    employeeview.ui \
    ownerregisterview.ui \
    ownerlookingwidget.ui \
    ownermodifywidget.ui \
    ownerview.ui
