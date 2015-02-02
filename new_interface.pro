#-------------------------------------------------
#
# Project created by QtCreator 2015-01-22T11:20:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = new_interface
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        rt_thread.cpp \
    tcpinterface.cpp

HEADERS  += mainwindow.h \
    ../interface_data.h \
    interface_data.h\
    rt_thread.h \
    tcpinterface.h

FORMS    += mainwindow.ui
