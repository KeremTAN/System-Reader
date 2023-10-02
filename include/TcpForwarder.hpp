#ifndef UDPFORWARDER_HPP
#define UDPFORWARDER_HPP

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

class TcpForwarder {
public:
    TcpForwarder();
    ~TcpForwarder() = default;

    void sendJsonData(const char*);

private:
    int m_tcpSocket{};
    struct sockaddr_in m_serverAddr{};
    socklen_t m_addr_size{};
};

#endif