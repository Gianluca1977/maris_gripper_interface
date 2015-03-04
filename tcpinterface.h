#ifndef TCPINTERFACE_H
#define TCPINTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "interface_data.h"
#include "rt_thread.h"

class TcpInterface : private rt_thread
{
    void rt_thread_handler(void);

    int sockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

public:
    TcpInterface();
    ~TcpInterface();

    virtual void refresh();

    int connectTo(char* addr, int port);
    void disconnectFrom();

    void resetRequest();
    int sendRequest();

    SystemStatus Status;
    SystemRequest_2 Request;

    bool connected;
};

#endif // TCPINTERFACE_H
