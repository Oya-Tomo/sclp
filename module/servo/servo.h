#pragma once

#include "pico/stdlib.h"

#include "hardware/pwm.h"

class Servo
{
public:
    Servo(
        uint8_t pin_pwm);
    ~Servo();

    typedef struct
    {
        float pwm_clkdiv;
        uint16_t pwm_wrap;
        double min_pulse_us;
        double min_angle;
        double max_pulse_us;
        double max_angle;
    } config_t;

    void configure(config_t config);

    void set_angle(double angle);

private:
    uint8_t pin_pwm;

    config_t config;

    uint32_t pwm_slice;
    uint32_t pwm_channel;

    double guard(double value, double min, double max);
};
