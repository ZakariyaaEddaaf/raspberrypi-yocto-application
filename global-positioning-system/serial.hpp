#ifndef SERIAL_HPP
#define SERIAL_HPP

#include <string>
#include <iostream>
#include <fcntl.h> 
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <cstring> 

class Serial
{
public:
    Serial(const std::string& serial_port, uint32_t baud_rate);
    ~Serial();

    bool open_serial();
    bool close_serial();
    ssize_t read_serial(char* buffer, size_t size);
    ssize_t write_serial(const char* data, size_t size);

private:
    int serial_fd;
    uint32_t baud_rate;
    std::string serial_port;
    bool configure_serial();
};

#endif // SERIAL_HPP
