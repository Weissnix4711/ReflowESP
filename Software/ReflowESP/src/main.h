#pragma once

#include "core/pwm.h"
#include "core/therm.h"

extern int pwmPeriodSec;

extern float pwmState;

extern pwm::PWMOutput pwmout;
extern therm::Thermocouple thermocouple;
