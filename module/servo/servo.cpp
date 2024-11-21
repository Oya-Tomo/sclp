#include "servo.h"
#include "../../constants.h"

#include "hardware/pwm.h"

Servo::Servo(
    uint8_t pin_pwm)
{

    this->pin_pwm = pin_pwm;
}

Servo::~Servo()
{
    gpio_deinit(this->pin_pwm);
}

void Servo::configure(config_t config)
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
}

void Servo::set_angle(double angle)
{
    double pwm_hz = PICO_PWM_CLK / (this->config.pwm_clkdiv * this->config.pwm_wrap);
    double angle_ratio = (angle - this->config.min_angle) / (this->config.max_angle - this->config.min_angle);
    double pulse_us = 1.0 / (pwm_hz * 1000000.0);
    double pulse_high_us = this->config.min_pulse_us + (this->config.max_pulse_us - this->config.min_pulse_us) * angle_ratio;

    double duty_cycle = pulse_high_us / pulse_us;

    pwm_set_chan_level(this->pwm_slice, this->pwm_channel, this->config.pwm_wrap * duty_cycle);
}

double Servo::guard(double value, double min, double max)
{
    return value < min ? min : (value > max ? max : value);
}