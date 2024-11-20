#include "./pwm_func.h"

float pwm_clkdiv_calc(int32_t hz, uint16_t wrap)
{
    return PICO_PWM_DEFAULT_CLK / (hz * wrap);
}

uint16_t pwm_wrap_calc(int32_t hz, float clkdiv)
{
    return PICO_PWM_DEFAULT_CLK / (hz * clkdiv);
}