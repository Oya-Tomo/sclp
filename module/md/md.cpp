#include "md.h"

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

void MotorDriver3Pins::init()
{
    gpio_init(this->pin_pwm);
    gpio_set_dir(this->pin_pwm, GPIO_OUT);

    gpio_init(this->pin_dir);
    gpio_set_dir(this->pin_dir, GPIO_OUT);
}

void MotorDriver3Pins::set_duty_cycle(double percentage)
{
}

void MotorDriver3Pins::set_direction(bool clockwise)
{
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

void MotorDriver4Pins::init()
{
    gpio_init(this->pin_pwm);
    gpio_set_dir(this->pin_pwm, GPIO_OUT);

    gpio_init(this->pin_dir1);
    gpio_set_dir(this->pin_dir1, GPIO_OUT);

    gpio_init(this->pin_dir2);
    gpio_set_dir(this->pin_dir2, GPIO_OUT);
}

void MotorDriver4Pins::set_duty_cycle(double percentage)
{
}

void MotorDriver4Pins::set_direction(bool clockwise)
{
}
