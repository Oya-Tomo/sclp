#pragma once

#include "pico/stdlib.h"

class PID
{
public:
    enum PIDType
    {
        pPID = 0,
        sPID = 1,
        PI_D = 2,
        I_PD = 3,
    };

    enum BaseUnit : int64_t
    {
        Mili = 1000,
        Micro = 1000000,
        Nano = 1000000000,
        Pico = 1000000000000,
        Femto = 1000000000000000,
    };

    typedef struct
    {
        double Kp;
        double Ki;
        double Kd;
        double Kf;
        bool guard;
        double min;
        double max;
    } config_t;

    PID(PIDType type);
    PID(PIDType type, BaseUnit unit);
    void configure(config_t config);
    void reset();
    double calculate(double target, double current, double dt);

private:
    void add_error(int64_t error);
    int64_t guard(int64_t value);
    int64_t calculate_pPID(int64_t target, int64_t current, double dt);
    int64_t calculate_sPID(int64_t target, int64_t current, double dt);
    int64_t calculate_PI_D(int64_t target, int64_t current, double dt);
    int64_t calculate_I_PD(int64_t target, int64_t current, double dt);

    PIDType type;
    BaseUnit unit;

    config_t config;

    int64_t errors[3]; // current value, one previous, two previous
    int64_t integral;
    int64_t output;
    int64_t target;
    int64_t value;
};