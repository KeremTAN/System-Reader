#include "TcpForwarder.hpp"


TcpForwarder::TcpForwarder(){

    try {
        m_serverAddr.sin_family = AF_INET;
        m_serverAddr.sin_port = htons(8081);
        m_serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    
}

void TcpForwarder::sendJsonData(const char* jsonString){
    try
    {
        if(m_tcpSocket = socket(AF_INET, SOCK_STREAM, 0) > -1) {

            if(bind(m_tcpSocket, (struct sockaddr *)&m_serverAddr, sizeof(m_serverAddr)) != -1) {
                
                listen(m_tcpSocket, 3);
                m_addr_size = sizeof(m_clientAddr);

                m_newSocket = accept(m_tcpSocket, (struct sockaddr*)&m_clientAddr, &m_addr_size);

                if (m_newSocket != -1) {

                    std::cout << "Client connected" << std::endl;
                    send(m_newSocket, jsonString, strlen(jsonString), 0); 
                    close(m_newSocket); 
                } 
                else std::cerr << "Accept Error" << std::endl;

                close(m_tcpSocket); 
            }
            else std::cerr << "Binding Error" << std::endl;
        }
        else std::cerr << "Socket Error"<< '\n';
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    
}