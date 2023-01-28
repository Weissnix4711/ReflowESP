#pragma once
#include <Arduino.h>
#include "../config/Config.h"

#ifdef HAS_MAX6675
#include <max6675.h>
#elif defined HAS_MAX31855
//includes
#endif

namespace therm {

class Thermocouple {
 public:
  void set_pins(uint8_t miso, uint8_t sck, uint8_t cs);
  void set_period(uint32_t period) { period_ = period; }
  float read() { return current_temp_; }
  void poll() { loop(); }
 protected:
  void loop();
  uint8_t pin_miso_;
  uint8_t pin_sck_;
  uint8_t pin_cs_;
  float current_temp_;
  #ifdef HAS_MAX6675
  MAX6675* thermocouple_;
  #endif
  uint32_t last_update_{0};
  uint32_t period_;
};

} // namespace therm
