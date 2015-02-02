#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    int ret;

    ret = a.exec();

    /* chiusura e finalizzazione del software */


    return ret;
}
