#include "md.h"

#include "hardware/pwm.h"

MotorDriver3Pins::MotorDriver3Pins(uint8_t pin_pwm, uint8_t pin_dir)
{
    this->pin_pwm = pin_pwm;
    this->pin_dir = pin_dir;
    this->pwm_slice_num = 0;
}

MotorDriver3Pins::~MotorDriver3Pins()
{
    gpio_deinit(this->pin_pwm);
    gpio_deinit(this->pin_dir);
}

void MotorDriver3Pins::init()
{
    gpio_init(this->pin_pwm);
    gpio_set_function(this->pin_pwm, GPIO_FUNC_PWM);

    this->pwm_slice_num = pwm_gpio_to_slice_num(this->pin_pwm);
    this->pwm_config = pwm_get_default_config();

    pwm_init(this->pwm_slice_num, &this->pwm_config, true);
    pwm_set_gpio_level(this->pin_pwm, 0);

    gpio_init(this->pin_dir);
    gpio_set_dir(this->pin_dir, GPIO_OUT);
}

void MotorDriver3Pins::set_duty_cycle(double percentage)
{
    pwm_set_gpio_level(this->pin_pwm, this->pwm_config.top * percentage);
}

void MotorDriver3Pins::set_direction(bool clockwise)
{
    gpio_put(this->pin_dir, clockwise);
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

    this->pwm_slice_num = pwm_gpio_to_slice_num(this->pin_pwm);
    this->pwm_config = pwm_get_default_config();

    pwm_init(this->pwm_slice_num, &this->pwm_config, true);
    pwm_set_gpio_level(this->pin_pwm, 0);

    gpio_init(this->pin_dir1);
    gpio_set_dir(this->pin_dir1, GPIO_OUT);

    gpio_init(this->pin_dir2);
    gpio_set_dir(this->pin_dir2, GPIO_OUT);
}

void MotorDriver4Pins::set_duty_cycle(double percentage)
{
    pwm_set_gpio_level(this->pin_pwm, this->pwm_config.top * percentage);
}

void MotorDriver4Pins::set_direction(bool clockwise)
{
    gpio_put(this->pin_dir1, clockwise);
    gpio_put(this->pin_dir2, !clockwise);
}

void MotorDriver4Pins::set_high_brake()
{
    gpio_put(this->pin_dir1, true);
    gpio_put(this->pin_dir2, true);
}
