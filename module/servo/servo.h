#pragma once

#include "pico/stdlib.h"

#include "hardware/pwm.h"

class Servo
{
public:
    Servo(
        uint8_t pin_pwm,
        uint16_t pulse_min_us,
        uint16_t pulse_max_us,
        uint32_t pwm_hz,
        float angle = 0.0f,
        float pwm_clkdiv = 125.0f);

    ~Servo();

    void init();

    void set_frequency(uint32_t pwm_hz, float pwm_clkdiv = 125.0f);

    void set_angle(double angle);
    double get_angle();

private:
    uint8_t pin_pwm;
    uint32_t pwm_hz;

    uint16_t pulse_min_us;
    uint16_t pulse_max_us;

    uint32_t pwm_slice;
    uint32_t pwm_channel;
    pwm_config pwm_slice_config;

    double angle;
};
