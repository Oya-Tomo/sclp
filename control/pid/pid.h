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
    void configure(config_t config);
    void reset();
    double calculate(double target, double current, double dt);

private:
    void add_error(double error);
    double guard(double value);
    double calculate_pPID(double target, double current, double dt);
    double calculate_sPID(double target, double current, double dt);
    double calculate_PI_D(double target, double current, double dt);
    double calculate_I_PD(double target, double current, double dt);

    PIDType type;

    config_t config;

    double errors[3]; // current value, one previous, two previous
    double integral;
    double output;
    double target;
    double value;
};