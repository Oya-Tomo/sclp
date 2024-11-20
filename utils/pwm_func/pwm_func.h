#pragma once

#include "pico/stdlib.h"

const double PICO_PWM_DEFAULT_CLK = 125000000.0;

float pwm_clkdiv_calc(int32_t hz, uint16_t wrap);

uint16_t pwm_wrap_calc(int32_t hz, float clkdiv);
