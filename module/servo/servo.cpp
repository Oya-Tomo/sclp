#include "servo.h"

Servo::Servo(uint8_t pin_pwm)
{
    this->pin_pwm = pin_pwm;
    this->angle = 0.0;
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
}

void Servo::set_angle(double angle)
{
}

double Servo::get_angle()
{
    return 0.0;
}
