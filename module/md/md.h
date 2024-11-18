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

    void init();

    void set_duty_cycle(double percentage);
    void set_direction(bool clockwise);

private:
    uint8_t pin_pwm;
    uint8_t pin_dir;

    uint32_t pwm_slice_num;
    pwm_config pwm_slice_config;
};

class MotorDriver4Pins
{
public:
    MotorDriver4Pins(
        uint8_t pin_pwm,
        uint8_t pin_dir1,
        uint8_t pin_dir2);
    ~MotorDriver4Pins();

    void init();

    void set_duty_cycle(double percentage);
    void set_direction(bool clockwise);
    void set_high_brake();

private:
    uint8_t pin_pwm;
    uint8_t pin_dir1;
    uint8_t pin_dir2;

    uint32_t pwm_slice_num;
    pwm_config pwm_slice_config;
};
