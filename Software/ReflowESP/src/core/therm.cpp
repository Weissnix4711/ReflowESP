#include "therm.h"
#include <max6675.h>

namespace therm {

void Thermocouple::set_pins(uint8_t miso, uint8_t sck, uint8_t cs) {
  thermocouple_ = new MAX6675(sck, cs, miso);
}

void Thermocouple::loop() {
  uint32_t now = millis();
  if (now - this->last_update_ >= this->period_) {
    this->current_temp_ = thermocouple_->readCelsius();
  }
}

} // namespace therm
