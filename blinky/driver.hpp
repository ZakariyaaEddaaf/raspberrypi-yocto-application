#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <string>

class GPIO {
public:
  GPIO(const std::string &pin);
  ~GPIO();
  void set_direction(const std::string &direction);
  void set_value(const std::string &value);

private:
  std::string gpio_pin;
  void write_value_file(const std::string &path, const std::string &value);
};

#endif // DRIVER_HPP
