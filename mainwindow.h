#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui_mainwindow.h"
#include "tcpinterface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openConnection();
    void counter_increase();
    void on_MainWindow_destroyed();

signals:
    void counter_changed();

private:
    Ui::MainWindow *ui;

    TcpInterface* myInterface;

    SystemStatus Status;
    SystemRequest Request;

    int counter;
};

#endif // MAINWINDOW_H
