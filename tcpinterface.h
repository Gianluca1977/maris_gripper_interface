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

    int port;

    int sockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    SystemStatus& Status;
    SystemRequest& Request;

public:
    TcpInterface(SystemStatus& ext_Status, SystemRequest& ext_Request);
    ~TcpInterface();

    int connectTo(char* addr);
    void disconnect();

    int sendRequest();
    void refresh();

    bool connected;
};

#endif // TCPINTERFACE_H
