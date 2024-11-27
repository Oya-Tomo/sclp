#include "md.h"
#include <stdlib.h>

MotorDriver3Pins::MotorDriver3Pins(uint8_t pin_pwm, uint8_t pin_dir)
{
    this->pin_pwm = pin_pwm;
    this->pin_dir = pin_dir;
}

MotorDriver3Pins::~MotorDriver3Pins()
{
    gpio_deinit(this->pin_pwm);
    gpio_deinit(this->pin_dir);
}

void MotorDriver3Pins::configure(MotorDriver3Pins::config_t config)
{
    this->config = config;

    gpio_init(this->pin_pwm);
    gpio_set_function(this->pin_pwm, GPIO_FUNC_PWM);
    this->pwm_slice = pwm_gpio_to_slice_num(this->pin_pwm);
    this->pwm_channel = pwm_gpio_to_channel(this->pin_pwm);

    pwm_set_clkdiv_mode(this->pwm_slice, PWM_DIV_FREE_RUNNING);
    pwm_set_clkdiv(this->pwm_slice, this->config.pwm_clkdiv);
    pwm_set_wrap(this->pwm_slice, this->config.pwm_wrap);
    pwm_set_chan_level(this->pwm_slice, this->pwm_channel, 0);
    pwm_set_enabled(this->pwm_slice, true);

    gpio_init(this->pin_dir);
    gpio_set_dir(this->pin_dir, GPIO_OUT);
}

void MotorDriver3Pins::set_duty_ratio(double ratio)
{
    if (this->config.reverse)
    {
        ratio = -ratio;
    }
    pwm_set_chan_level(this->pwm_slice, this->pwm_channel, abs(ratio) * this->config.pwm_wrap);
    gpio_put(this->pin_dir, ratio >= 0);
}

MotorDriver4Pins::MotorDriver4Pins(uint8_t pin_pwm, uint8_t pin_dir1, uint8_t pin_dir2)
{
    this->pin_pwm = pin_pwm;
    this->pin_dir1 = pin_dir1;
    this->pin_dir2 = pin_dir2;
}

MotorDriver4Pins::~MotorDriver4Pins()
{
    gpio_deinit(this->pin_pwm);
    gpio_deinit(this->pin_dir1);
    gpio_deinit(this->pin_dir2);
}

void MotorDriver4Pins::configure(MotorDriver4Pins::config_t config)
{
    this->config = config;

    gpio_init(this->pin_pwm);
    gpio_set_function(this->pin_pwm, GPIO_FUNC_PWM);
    this->pwm_slice = pwm_gpio_to_slice_num(this->pin_pwm);
    this->pwm_channel = pwm_gpio_to_channel(this->pin_pwm);

    pwm_set_clkdiv_mode(this->pwm_slice, PWM_DIV_FREE_RUNNING);
    pwm_set_clkdiv(this->pwm_slice, this->config.pwm_clkdiv);
    pwm_set_wrap(this->pwm_slice, this->config.pwm_wrap);
    pwm_set_chan_level(this->pwm_slice, this->pwm_channel, 0);
    pwm_set_enabled(this->pwm_slice, true);

    gpio_init(this->pin_dir1);
    gpio_set_dir(this->pin_dir1, GPIO_OUT);
    gpio_init(this->pin_dir2);
    gpio_set_dir(this->pin_dir2, GPIO_OUT);
}

void MotorDriver4Pins::set_duty_ratio(double ratio)
{
    pwm_set_chan_level(this->pwm_slice, this->pwm_channel, abs(ratio) * this->config.pwm_wrap);
    gpio_put(this->pin_dir1, ratio >= 0);
    gpio_put(this->pin_dir2, ratio <= 0);
}
