#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <iostream>

#include "tcpinterface.h"

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

TcpInterface::TcpInterface()
{
    connected = false;

    resetRequest();
}

int TcpInterface::connectTo(char* addr, int port)
{
    int ret = 0;    

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    serv_addr.sin_addr.s_addr = inet_addr(addr);
    serv_addr.sin_port = htons(port);

    ret = connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));

    if (ret < 0)
    {
        perror("ERROR connecting");
    }
    else
    {        
        std::cout << "CONNECTED" << std::endl;
        resetRequest();
        //Request.tcpActive = true;
        write(sockfd,&Request,sizeof(SystemRequest_2));
        pthread_create(&if_thread, NULL, &thread_func, this);
        connected = true;
    }

    return ret;
}

void TcpInterface::rt_thread_handler(void)
{
    int ret;

    std::cout << "TcpInterface::rt_thread_handler created \n" << std::endl;

    while (connected){
        //bzero(sysStat,sizeof(SystemStatus));
        ret  = read(sockfd,&Status,sizeof(SystemStatus));

        returnValue = &ret;

        switch(ret){
        case -1:
            printf("ERROR: %s\n", strerror(errno));
            break;
        case 0:
            printf("0 byte read\n");
            disconnectFrom();
            break;
        case sizeof(SystemStatus):
            //std::cout << "Read performed correctly" << std::endl;
            break;
        default:
            std::cout << "ERROR: Wrong read dimension " << ret << std::endl;

        }

        refresh();
    }
}

int TcpInterface::sendRequest()
{
    if(connected)
    {
        int ret = write(sockfd,&Request,sizeof(SystemRequest_2));
        if(ret == sizeof(SystemRequest_2)){
           std::cout << "Request correctly sent" << std::endl;
        }
        else
        {
            std::cout << "Dimensione NON Corretta " << ret << std::endl;
            if(ret == 0)
            {
                std::cout << "EOF reached" << std::endl;
            }
            else if(ret<0)
            {
                std::cout << "read generated an error" << std::endl;
                perror("TcpReceive::rt_thread_handler");
            }
        }
    }
    else return -1;
}

void TcpInterface::refresh()
{
}

TcpInterface::~TcpInterface()
{
    if(connected) disconnectFrom();
}

void TcpInterface::disconnectFrom()
{
    resetRequest();
    sendRequest();

    connected = false;

    shutdown(sockfd,2);
    close(sockfd);

    pthread_join(if_thread,NULL);
}

void TcpInterface::resetRequest()
{
//    Request.emerg_stop = false;
//    Request.pos = false;
//    Request.setIniPos = false;
//    Request.setFinPos = false;
//    Request.goIniPos = false;
//    Request.goFinPos = false;
//    Request.manualHomeDone = false;
//    Request.repeat = 0;
//    Status.actCycle = 0;
//    Request.butNum = 0;
//    Request.parking = false;
//    Request.doHome = false;
//    Request.tcpActive = false;

    Request.command = DO_NOTHING;

    for(unsigned int i = 0; i < NUM_MOT; i++)
    {
        Request.req_vel[i] = 0;
        Request.req_pos[i] = 0;
    }
}
