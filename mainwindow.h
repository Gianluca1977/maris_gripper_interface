#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui_mainwindow.h"
#include "tcpinterface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public TcpInterface
{
    Q_OBJECT

    //friend class TcpInterface;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openConnection();
    void closeConnection();

    void on_Preshape_pushButton_released();

    void on_Emergency_pushButton_released();

    void on_Velocity_pushButton_released();

signals:
    void counter_changed();

private:
    Ui::MainWindow *ui;

    void refresh(void);

    int counter;
};

#endif // MAINWINDOW_H
