#include "pico/stdlib.h"

class Servo
{
public:
    Servo(uint8_t pin_pwm);

    ~Servo();

    void init();

    void set_angle(double angle);
    double get_angle();

private:
    uint8_t pin_pwm;
    double angle;
};
