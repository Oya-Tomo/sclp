#pragma once

#include "pico/stdlib.h"

class QEI
{
    const double PI = 3.1415926535;
public:
    QEI(
        uint8_t pin_a,
        uint8_t pin_b,
        int ppr
    );

    ~QEI();

    void init();

    void callback_register(uint gpio, uint32_t events);

    int get_counts();
    int get_ppr();
    int get_cpr();

    double get_rotations();
    double get_radians();

    void reset();

    void set_rotations(double rotations);
    void set_radians(double radians);

private:
    uint8_t pin_a;
    uint8_t pin_b;

    int ppr;
    int counts;

    void pin_a_irq(uint gpio, uint32_t events);
    void pin_b_irq(uint gpio, uint32_t events);
};