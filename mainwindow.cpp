#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcpinterface.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    counter = 0;

    const QString str = QString("sizeof(SystemRequest) =  %1, sizeof(SystemStatus) = %2").arg(QString::number(sizeof(SystemRequest)),QString::number(sizeof(SystemStatus)));

    ui->statusBar->showMessage(str);
    myInterface = new TcpInterface(Status,Request);
}

MainWindow::~MainWindow()
{
    delete myInterface;
    delete ui;
}

void MainWindow::counter_increase()
{
    counter++;
    ui->lcdNumber->display(counter);
}

void MainWindow::on_MainWindow_destroyed()
{
    //GLOBALSTOP = true;
}


void MainWindow::openConnection()
{
    if(!myInterface->connected)
    {
        myInterface->connectTo(ui->lineEdit->text().toLocal8Bit().data());

        if(myInterface->connected)
        {
            ui->connectButton->setText("Disconnect");
            ui->statusBar->showMessage("Connected to control application");
        }
        else
        {
            ui->statusBar->showMessage("Connecton refused");
        }

    }
    else
    {
        myInterface->disconnect();
        ui->connectButton->setText("Connect");
        ui->statusBar->showMessage("Disconnected from control application");
    }

}

