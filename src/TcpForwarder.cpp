#include "TcpForwarder.hpp"


TcpForwarder::TcpForwarder(){

    try {
        m_serverAddr.sin_family = AF_INET;
        m_serverAddr.sin_port = htons(8081);
        m_serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        inet_pton(AF_INET, "127.0.0.1", &(m_serverAddr.sin_addr));
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

void TcpForwarder::sendJsonData(const char* jsonString){
    
    try
    {
        if((m_tcpSocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) != -1) {

            if(connect(m_tcpSocket, reinterpret_cast<struct sockaddr*>(&m_serverAddr), sizeof(m_serverAddr)) != -1) {
                std::cout << "Connecting √" << std::endl;

                int bytes = send(m_tcpSocket, jsonString, strlen(jsonString), 0); 

                if(bytes == -1)
                    std::cerr << "[Error] Sending Failure" << std::endl;

                close(m_tcpSocket); 
            } 
            else std::cerr << "[Error] Connecting Failure" << std::endl;
        }
        else std::cerr << "[Error] Socket Failure"<< '\n';
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    
}