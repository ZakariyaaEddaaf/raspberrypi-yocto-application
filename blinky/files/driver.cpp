#include "driver.hpp"
#include <fstream>
#include <iostream>
#include <unistd.h>

GPIO::GPIO(const std::string &gpio_pin) : gpio_pin(gpio_pin) {
  write_value_file("/sys/class/gpio/export", gpio_pin);
}

GPIO::~GPIO() { write_value_file("/sys/class/gpio/unexport", gpio_pin); }

void GPIO::set_direction(const std::string &direction) {
  write_value_file(
      "/sys/devices/platform/soc/fe200000.gpio/gpiochip0/gpio/gpio" + gpio_pin +
          "/direction",
      direction);
}

void GPIO::set_value(const std::string &value) {
  write_value_file(
      "/sys/devices/platform/soc/fe200000.gpio/gpiochip0/gpio/gpio" + gpio_pin +
          "/value",
      value);
}

void GPIO::write_value_file(const std::string &path, const std::string &value) {
  std::ofstream fs(path);
  if (!fs) {
    std::cerr << "Error opening file: " << path << std::endl;
    exit(EXIT_FAILURE);
  }
  fs << value;
  fs.close();
}
