#ifndef LED_HPP
#define LED_HPP

#include "driver.hpp"

class LED {
public:
  LED(const std::string &gpio_pin);
  void turn_led_on();
  void turn_led_off();
  void blink_led(int delay_ms);

private:
  GPIO gpio;
};

#endif // LED_HPP
