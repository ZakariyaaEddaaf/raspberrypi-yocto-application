#include "led.hpp"

const int DELAY_MS = 500;

int main() {
  LED led("2");
  led.blink_led(DELAY_MS);
  return 0;
}
