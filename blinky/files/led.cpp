#include "led.hpp"
#include <unistd.h>
const int DELAY_FACTOR = 1000;
LED::LED(const std::string &pin) : gpio(pin) { gpio.set_direction("out"); }
void LED::turn_led_on() { gpio.set_value("1"); }
void LED::turn_led_off() { gpio.set_value("0"); }
void LED::blink_led(int delay_ms) {
  while (true) {
    gpio.set_value("1");
    usleep(delay_ms * DELAY_FACTOR);
    gpio.set_value("0");
    usleep(delay_ms * DELAY_FACTOR);
  }
}
