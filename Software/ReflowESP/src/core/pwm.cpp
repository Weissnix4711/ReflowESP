#include "pwm.h"

#include <Arduino.h>

namespace pwm {

void PWMOutput::set_output_state_(bool new_state) {
  if (new_state != this->current_state_) {
    this->current_state_ = new_state;
    digitalWrite(this->pin_, new_state);
    Serial.printf("Setting state %s\n", new_state ? "on" : "off");
  }
}

void PWMOutput::loop() {
  uint32_t now = millis();
  float scaled_state = this->state_ * this->period_;

  this->set_output_state_(scaled_state > now - this->period_start_time_);

  if (now - this->period_start_time_ >= this->period_) {
    this->period_start_time_ += this->period_;
  }
}

} // namespace pwm
