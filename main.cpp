#include "utils/serial.hpp"
#include "global-positioning-system/gnss.hpp"
#include <iostream>
#include <thread>
#include <sstream>

int main()
{
    // Create an instance of the Serial class
    Serial serial("/dev/ttyACM0", 115200);
    // Create an instance of the GNSS class
    GNSS gnss;

    // Open the serial port
    if (!serial.open_serial())
    {
        std::cerr << "Failed to open serial port." << std::endl;
        return 1;
    }

    // Buffer to store GPS data
    char buffer[1024];

    while (true)
    {
        // Read data from the serial port
        ssize_t n = serial.read_serial(buffer, sizeof(buffer) - 1);
        if (n < 0)
        {
            std::cerr << "Failed to read from serial port." << std::endl;
            break;
        }

        buffer[n] = '\0'; // Null-terminate the string
        std::string data(buffer);

        // Find GNGGA sentence from the data
        std::string gga_sentence = gnss.catch_gpgga_gngga(data);

        // Check if a valid GGA sentence is found
        if (!gga_sentence.empty())
        {
            //std::cout << gga_sentence << std::endl;
            gnss.parse_gpgga_gngga(gga_sentence);
            std::cout<<gnss.get_hdop()<<std::endl;

        }

    }

    // Close the serial port
    serial.close_serial();

    return 0;
}
