#ifndef PID_H
#define PID_H

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

    PID(PIDType type);
    PID(PIDType type, BaseUnit unit);
    void setGuard(double min, double max, bool guard);
    void setGain(double Kp, double Ki, double Kd, double Kf);
    void reset();
    double calculate(double target, double current, double dt);

private:
    void add_error(int64_t error);
    int64_t guard(int64_t value);
    int64_t calculate_pPID(int64_t target, int64_t current, double dt);
    int64_t calculate_sPID(int64_t target, int64_t current, double dt);
    int64_t calculate_PI_D(int64_t target, int64_t current, double dt);
    int64_t calculate_I_PD(int64_t target, int64_t current, double dt);

    PIDType _type;
    BaseUnit _unit;

    double _Kp;
    double _Ki;
    double _Kd;
    double _Kf;

    int64_t _min;
    int64_t _max;
    bool _guard;

    int64_t _error[3]; // current value, one previous, two previous
    int64_t _integral;
    int64_t _output;
    int64_t _target;
    int64_t _value;
};

#endif