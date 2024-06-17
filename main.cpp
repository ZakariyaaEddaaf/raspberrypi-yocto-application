#include "transmission-control-protocol/server.hpp"

int main()
{
    const std::string server_address = "192.168.0.2";
    int server_port = 5000;
    const std::string serial_port = "/dev/ttyACM0";
    uint32_t baud_rate = 115200;

    Server server(server_address, server_port, serial_port, baud_rate);

    if (!server.start_server())
    {
        std::cerr << "Failed to start server." << std::endl;
        return -1;
    }

    return 0;
}
