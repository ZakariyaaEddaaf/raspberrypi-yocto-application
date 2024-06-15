#include "serial.hpp"

Serial::Serial(const std::string& serial_port, uint32_t baud_rate)
    : serial_port(serial_port), baud_rate(baud_rate), serial_fd(-1)
{
}

Serial::~Serial()
{
    close_serial();
}

bool Serial::open_serial()
{
    serial_fd = open(serial_port.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    if (serial_fd < 0)
    {
        std::cerr << "Error opening serial port: " << strerror(errno) << std::endl;
        return false;
    }
    return true;
}

bool Serial::close_serial()
{
    if (serial_fd >= 0)
    {
        close(serial_fd);
        serial_fd = -1;
    }
    return true;
}

bool Serial::configure_serial()
{
    struct termios tty;
    if (tcgetattr(serial_fd, &tty) != 0)
    {
        std::cerr << "Error getting terminal attributes: " << strerror(errno) << std::endl;
        return false;
    }

    speed_t speed;
    switch (baud_rate)
    {
        case 9600: speed = B9600; break;
        case 19200: speed = B19200; break;
        case 38400: speed = B38400; break;
        case 57600: speed = B57600; break;
        case 115200: speed = B115200; break;
        default: speed = B9600; break;  // Default baud rate
    }

    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;  // 8-bit chars
    tty.c_iflag &= ~IGNBRK;                      // Disable break processing
    tty.c_lflag = 0;                             // No signaling chars, no echo, no canonical processing
    tty.c_oflag = 0;                             // No remapping, no delays
    tty.c_cc[VMIN]  = 0;                         // Read doesn't block
    tty.c_cc[VTIME] = 5;                         // 0.5 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);      // Shut off xon/xoff ctrl
    tty.c_cflag |= (CLOCAL | CREAD);             // Ignore modem controls, enable reading
    tty.c_cflag &= ~(PARENB | PARODD);           // No parity
    tty.c_cflag &= ~CSTOPB;                      // 1 stop bit
    tty.c_cflag &= ~CRTSCTS;                     // No hardware flow control

    if (tcsetattr(serial_fd, TCSANOW, &tty) != 0)
    {
        std::cerr << "Error setting terminal attributes: " << strerror(errno) << std::endl;
        return false;
    }
    return true;
}

ssize_t Serial::read_serial(char* buffer, size_t size)
{
    return read(serial_fd, buffer, size);
}

ssize_t Serial::write_serial(const char* data, size_t size)
{
    return write(serial_fd, data, size);
}
