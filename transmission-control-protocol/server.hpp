#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <chrono>
#include <thread>
#include "../utils/serial.hpp"
#include "../global-positioning-system/gnss.hpp"

class Server {
    public:
        Server(const std::string& addr, int port, const std::string& serial_port, uint32_t baud_rate);
        ~Server();
        
        bool start_server();
        bool stop_server();
    
    private:
        bool initialize_server();
        bool transmit_gnss(int client_socket);

        std::string server_addr;
        int server_port;
        int server_fd;
        
        Serial serial;
        GNSS gnss;
};

#endif // SERVER_HPP




