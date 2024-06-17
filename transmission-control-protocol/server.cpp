#include "server.hpp"

Server::Server(const std::string& addr, int port, const std::string& serial_port, uint32_t baud_rate) 
    : server_addr(addr), server_port(port), server_fd(-1), serial(serial_port, baud_rate) {}

Server::~Server()
{
    if (server_fd != -1)
        close(server_fd);
    serial.close_serial();
}

bool Server::start_server()
{
    if (!initialize_server())
    {
        std::cerr << "Failed to initialize server." << std::endl;
        return false;
    }

    if (!serial.open_serial() || !serial.configure_serial())
    {
        std::cerr << "Failed to initialize serial connection." << std::endl;
        return false;
    }

    std::cout << "Server running on port " << server_port << std::endl;

    while (true)
    {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        int client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0)
        {
            std::cerr << "Failed to accept client connection." << std::endl;
            continue;
        }

        std::cout << "Client connected"<< std::endl;

        while (true)
        {
            if (!transmit_gnss(client_socket))
            {
                std::cerr << "Failed to send data to client. Closing connection." << std::endl;
                break;
            }
        }

        close(client_socket);
        std::cout << "Client disconnected" << std::endl;
    }

    return true;
}

bool Server::stop_server()
{
    if (server_fd != -1)
    {
        close(server_fd);
        server_fd = -1;
    }
    return true;
}

bool Server::initialize_server()
{
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        std::cerr << "Failed to create socket." << std::endl;
        return false;
    }

    struct sockaddr_in server_addr_in;
    memset(&server_addr_in, 0, sizeof(server_addr_in));
    server_addr_in.sin_family = AF_INET;
    server_addr_in.sin_port = htons(server_port);

    if (inet_pton(AF_INET, server_addr.c_str(), &server_addr_in.sin_addr) <= 0)
    {
        std::cerr << "Invalid address: " << server_addr << std::endl;
        close(server_fd);
        server_fd = -1;
        return false;
    }

    if (bind(server_fd, (struct sockaddr *)&server_addr_in, sizeof(server_addr_in)) < 0)
    {
        std::cerr << "Failed to bind socket to address." << std::endl;
        close(server_fd);
        server_fd = -1;
        return false;
    }

    if (listen(server_fd, 5) < 0)
    {
        std::cerr << "Failed to listen on socket." << std::endl;
        close(server_fd);
        server_fd = -1;
        return false;
    }

    return true;
}

bool Server::transmit_gnss(int client_socket)
{
    char buffer[1024];
    ssize_t bytes_read = serial.read_serial(buffer, sizeof(buffer) - 1);
    if (bytes_read < 0)
    {
        std::cerr << "Failed to read from serial port." << std::endl;
        return false;
    }

    buffer[bytes_read] = '\0';
    std::string gps_data(buffer);

    std::string gpgga_sentence = gnss.catch_gpgga_gngga(gps_data);
    gpgga_sentence += "\n";
    if (!gpgga_sentence.empty()){
        
        int bytes_sent = send(client_socket, gpgga_sentence.c_str(), gpgga_sentence.length(), 0);
        if (bytes_sent != gpgga_sentence.length())
        {
            std::cerr << "Failed to send complete message to client." << std::endl;
            return false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return true;
}

