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

TcpInterface::TcpInterface(SystemStatus& ext_Status, SystemRequest& ext_Request) : Status(ext_Status), Request(ext_Request)
{
    connected = false;
    port = 9999;
}

int TcpInterface::connectTo(char* addr)
{
    int ret = 0;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    /* server = gethostbyname(addr.c_str());
     if (server == NULL) {
         fprintf(stderr,"ERROR, no such host\n");
         exit(0);
     }*/
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    /* bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
 */
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
        write(sockfd,&Request,sizeof(SystemRequest));
        pthread_create(&if_thread, NULL, &thread_func, this);
        connected = true;
    }

    return ret;
}

void TcpInterface::rt_thread_handler(void)
{
    /*
 * mailbox update joint states (control -> interface)
 */

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
            break;
        case sizeof(SystemStatus):
            //std::cout << "Read performed correctly" << std::endl;
            //printf("statusword_low 1: %d \n" ,sysStat->statusword_low[0]);
            break;
        default:
            std::cout << "ERROR: Wrong read dimension" << std::endl;

        }

        refresh();
    }
}

int TcpInterface::sendRequest()
{
    if(connected) return write(sockfd,&Request,sizeof(SystemRequest));
    else return -1;
}

void TcpInterface::refresh()
{

}

TcpInterface::~TcpInterface()
{
    if(connected) disconnect();
}

void TcpInterface::disconnect()
{
    connected = false;

    shutdown(sockfd,2);
    close(sockfd);

    pthread_join(if_thread,NULL);
}
