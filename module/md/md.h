#pragma once

#include "pico/stdlib.h"
#include "hardware/pwm.h"

class MotorDriver3Pins
{
public:
    MotorDriver3Pins(
        uint8_t pin_pwm,
        uint8_t pin_dir);
    ~MotorDriver3Pins();

    typedef struct
    {
        uint32_t pwm_clkdiv;
        uint32_t pwm_wrap;
    } config_t;

    void configure(config_t config);

    void set_duty_ratio(double ratio);

private:
    uint8_t pin_pwm;
    uint8_t pin_dir;

    config_t config;

    uint32_t pwm_slice;
    uint32_t pwm_channel;
};

class MotorDriver4Pins
{
public:
    MotorDriver4Pins(
        uint8_t pin_pwm,
        uint8_t pin_dir1,
        uint8_t pin_dir2);
    ~MotorDriver4Pins();

    typedef struct
    {
        uint32_t pwm_clkdiv;
        uint32_t pwm_wrap;
    } config_t;

    void configure(config_t config);

    void set_duty_ratio(double ratio);

private:
    uint8_t pin_pwm;
    uint8_t pin_dir1;
    uint8_t pin_dir2;

    config_t config;

    uint32_t pwm_slice;
    uint32_t pwm_channel;
};
