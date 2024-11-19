#include "servo.h"

#include "hardware/pwm.h"

Servo::Servo(
    uint8_t pin_pwm,
    uint16_t pulse_min_us,
    uint16_t pulse_max_us,
    uint32_t pwm_hz,
    float angle,
    float pwm_clkdiv)
{
    this->pin_pwm = pin_pwm;
    this->pwm_hz = pwm_hz;

    this->pwm_slice_config = pwm_get_default_config();

    this->pulse_min_us = pulse_min_us;
    this->pulse_max_us = pulse_max_us;

    this->angle = angle;
}

Servo::~Servo()
{
    gpio_deinit(this->pin_pwm);
}

void Servo::init()
{
    gpio_init(this->pin_pwm);
    gpio_set_dir(this->pin_pwm, GPIO_OUT);
    gpio_set_function(this->pin_pwm, GPIO_FUNC_PWM);

    this->pwm_slice = pwm_gpio_to_slice_num(this->pin_pwm);
    this->pwm_channel = pwm_gpio_to_channel(this->pin_pwm);

    pwm_config_set_clkdiv_mode(&this->pwm_slice_config, PWM_DIV_FREE_RUNNING);

    this->set_frequency(this->pwm_hz);
    this->set_angle(this->angle);

    pwm_init(this->pwm_slice, &this->pwm_slice_config, true);
    pwm_set_enabled(this->pwm_slice, true);
}

void Servo::set_frequency(uint32_t pwm_hz, float pwm_clkdiv)
{
    this->pwm_hz = pwm_hz;

    pwm_config_set_clkdiv_mode(&this->pwm_slice_config, PWM_DIV_FREE_RUNNING);
    pwm_config_set_clkdiv(&this->pwm_slice_config, pwm_clkdiv);

    pwm_config_set_wrap(&this->pwm_slice_config, 125000000.0 / pwm_clkdiv / pwm_hz);
}

void Servo::set_angle(double angle)
{
    this->angle = angle;

    double pulse_width_us = 1.0 / this->pwm_hz * 1000000.0;
    double pulse_high_width_us = this->pulse_min_us + (this->pulse_max_us - this->pulse_min_us) * angle;

    double duty_cycle = pulse_high_width_us / pulse_width_us;

    pwm_set_chan_level(this->pwm_slice, this->pwm_channel, this->pwm_slice_config.top * duty_cycle);
}

double Servo::get_angle()
{
    return this->angle;
}
