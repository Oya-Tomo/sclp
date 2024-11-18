#include "pid.h"

PID::PID(PIDType type)
{
    _type = type;
    _unit = BaseUnit::Pico;
    reset();
}

PID::PID(PIDType type, BaseUnit unit)
{
    _type = type;
    _unit = unit;
    reset();
}

void PID::setGuard(double min, double max, bool guard)
{
    _min = min * _unit;
    _max = max * _unit;
    _guard = guard;
}

void PID::setGain(double Kp, double Ki, double Kd, double Kf)
{
    _Kp = Kp;
    _Ki = Ki;
    _Kd = Kd;
    _Kf = Kf;
}

void PID::reset()
{
    _error[0] = 0;
    _error[1] = 0;
    _error[2] = 0;
    _integral = 0;
    _output = 0;
    _target = 0;
    _value = 0;
}

double PID::calculate(double target, double current, double dt)
{
    switch (_type)
    {
    case PIDType::pPID:
        return (double)calculate_pPID(target * _unit, current * _unit, dt) / (double)_unit;
    case PIDType::sPID:
        return (double)calculate_sPID(target * _unit, current * _unit, dt) / (double)_unit;
    case PIDType::PI_D:
        return (double)calculate_PI_D(target * _unit, current * _unit, dt) / (double)_unit;
    case PIDType::I_PD:
        return (double)calculate_I_PD(target * _unit, current * _unit, dt) / (double)_unit;
    default:
        return 0;
    }
}

void PID::add_error(int64_t error)
{
    _error[2] = _error[1];
    _error[1] = _error[0];
    _error[0] = error;
}

int64_t PID::guard(int64_t value)
{
    return value > _max ? _max : (_min > value ? _min : value);
}

int64_t PID::calculate_pPID(int64_t target, int64_t current, double dt)
{
    add_error(target - current);
    _integral += (_error[0] + _error[1]) / 2 * dt;

    int64_t mp = _Kp * _error[0];
    int64_t mi = _Ki * _integral;
    int64_t md = _Kd * (_error[0] - _error[1]) / dt;

    _output = mp + mi + md;
    _output += _Kf * target; // Feed-Forward
    _output = _guard ? guard(_output) : _output;
    return _output;
}

int64_t PID::calculate_sPID(int64_t target, int64_t current, double dt)
{
    add_error(target - current);
    int64_t mp = _Kp * (_error[0] - _error[1]);
    int64_t mi = _Ki * _error[0] * dt;
    int64_t md = _Kd * (_error[0] - (2 * _error[1]) + _error[2]) / dt;

    _output += mp + mi + md;
    _output += _Kf * (target - _target) / dt; // Feed-Forward
    _target = target;
    return _guard ? guard(_output) : _output;
}

int64_t PID::calculate_PI_D(int64_t target, int64_t current, double dt)
{
    add_error(target - current);
    _integral += (_error[0] + _error[1]) / 2 * dt;

    int64_t mp = _Kp * _error[0];
    int64_t mi = _Ki * _integral;
    int64_t md = _Kd * (current - _value) / dt;

    _output = mp + mi - md;
    _output += _Kf * target;
    _output = _guard ? guard(_output) : _output;
    _value = current;
    return _output;
}

int64_t PID::calculate_I_PD(int64_t target, int64_t current, double dt)
{
    add_error(target - current);
    _integral += (_error[0] + _error[1]) / 2 * dt;

    double mp = _Kp * current;
    double mi = _Ki * _integral;
    double md = _Kd * (current - _value) / dt;

    _output = -mp + mi - md;
    _output += _Kf * target;
    _output = _guard ? guard(_output) : _output;
    _value = current;
    return _output;
}