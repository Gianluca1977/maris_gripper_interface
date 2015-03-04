#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcpinterface.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    counter = 0;

    const QString str = QString("sizeof(SystemRequest_2) =  %1, sizeof(SystemStatus) = %2").arg(QString::number(sizeof(SystemRequest_2)),QString::number(sizeof(SystemStatus)));

    ui->statusBar->showMessage(str);
}

MainWindow::~MainWindow()
{    
    delete ui;
}

void MainWindow::refresh()
{

    if(!connected)
    {
        closeConnection();
        return;
    }

    counter++;
    ui->lcdNumber->display(counter);

    ui->motor0_State->display(Status.State[0]);
    ui->motor1_State->display(Status.State[1]);
    ui->motor2_State->display(Status.State[2]);

    ui->motor0_Current->display((double)Status.Current[0]);
    ui->motor1_Current->display((double)Status.Current[1]);
    ui->motor2_Current->display((double)Status.Current[2]);

    ui->motor0_Position->display(Status.PositionGrad[0]);
    ui->motor1_Position->display(Status.PositionGrad[1]);
    ui->motor2_Position->display(Status.PositionGrad[2]);

    ui->motor0_Velocity->display((double)Status.Velocity[0]);
    ui->motor1_Velocity->display((double)Status.Velocity[1]);
    ui->motor2_Velocity->display((double)Status.Velocity[2]);

}

void MainWindow::openConnection()
{
    if(!connected)
    {
        connectTo(ui->ip_lineEdit->text().toLocal8Bit().data(),ui->port_lineEdit->text().toInt());

        if(connected)
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
       closeConnection();
    }

}

void MainWindow::closeConnection()
{
    disconnectFrom();
    ui->connectButton->setText("Connect");
    ui->statusBar->showMessage("Disconnected from control application");
}

void MainWindow::on_Preshape_pushButton_released()
{
    Request.command = PRESHAPE;
    Request.preshape = (uint32_t) ui->Preshape_lineEdit->text().toUInt();
    for( int i = 0; i < NUM_MOT; i++){
        Request.req_pos[i] = 0;
        //Request.req_vel[i] = i;
    }
    sendRequest();

    const QString str = QString("Preshape request  %1").arg(QString::number(Request.preshape));

    ui->statusBar->showMessage(str);
}

void MainWindow::on_Emergency_pushButton_released()
{
    Request.command = RECOVER;
    sendRequest();
}


void MainWindow::on_Velocity_pushButton_released()
{
    Request.command = GO_VELOCITY;
    Request.req_vel[0] = (int64_t) ui->Velocity_lineEdit->text().toInt();
    for( int i = 1; i < NUM_MOT; i++){
        //Request.req_pos[i] = 0;
        Request.req_vel[i] = ui->Velocity_lineEdit->text().toInt();
    }
    sendRequest();
}
