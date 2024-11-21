#include "pid.h"

PID::PID(PIDType type)
{
    type = type;
    unit = BaseUnit::Pico;
    reset();
}

PID::PID(PIDType type, BaseUnit unit)
{
    type = type;
    unit = unit;
    reset();
}

void PID::configure(config_t config)
{
    this->config = config;
}

void PID::reset()
{
    errors[0] = 0;
    errors[1] = 0;
    errors[2] = 0;
    integral = 0;
    output = 0;
    target = 0;
    value = 0;
}

double PID::calculate(double target, double current, double dt)
{
    switch (type)
    {
    case PIDType::pPID:
        return (double)calculate_pPID(target * unit, current * unit, dt) / (double)unit;
    case PIDType::sPID:
        return (double)calculate_sPID(target * unit, current * unit, dt) / (double)unit;
    case PIDType::PI_D:
        return (double)calculate_PI_D(target * unit, current * unit, dt) / (double)unit;
    case PIDType::I_PD:
        return (double)calculate_I_PD(target * unit, current * unit, dt) / (double)unit;
    default:
        return 0;
    }
}

void PID::add_error(int64_t error)
{
    errors[2] = errors[1];
    errors[1] = errors[0];
    errors[0] = error;
}

int64_t PID::guard(int64_t value)
{
    int64_t min = this->config.min * unit;
    int64_t max = this->config.max * unit;
    return value > max ? max : (min > value ? min : value);
}

int64_t PID::calculate_pPID(int64_t target, int64_t current, double dt)
{
    add_error(target - current);
    integral += (errors[0] + errors[1]) / 2 * dt;

    int64_t mp = this->config.Kp * errors[0];
    int64_t mi = this->config.Ki * integral;
    int64_t md = this->config.Kd * (errors[0] - errors[1]) / dt;

    output = mp + mi + md;
    output += this->config.Kf * target; // Feed-Forward
    output = this->config.guard ? guard(output) : output;
    return output;
}

int64_t PID::calculate_sPID(int64_t target, int64_t current, double dt)
{
    add_error(target - current);
    int64_t mp = this->config.Kp * (errors[0] - errors[1]);
    int64_t mi = this->config.Ki * errors[0] * dt;
    int64_t md = this->config.Kd * (errors[0] - (2 * errors[1]) + errors[2]) / dt;

    output += mp + mi + md;
    output += this->config.Kf * (target - target) / dt; // Feed-Forward
    target = target;
    return this->config.guard ? guard(output) : output;
}

int64_t PID::calculate_PI_D(int64_t target, int64_t current, double dt)
{
    add_error(target - current);
    integral += (errors[0] + errors[1]) / 2 * dt;

    int64_t mp = this->config.Kp * errors[0];
    int64_t mi = this->config.Ki * integral;
    int64_t md = this->config.Kd * (current - value) / dt;

    output = mp + mi - md;
    output += this->config.Kf * target;
    output = this->config.guard ? guard(output) : output;
    value = current;
    return output;
}

int64_t PID::calculate_I_PD(int64_t target, int64_t current, double dt)
{
    add_error(target - current);
    integral += (errors[0] + errors[1]) / 2 * dt;

    double mp = this->config.Kp * current;
    double mi = this->config.Ki * integral;
    double md = this->config.Kd * (current - value) / dt;

    output = -mp + mi - md;
    output += this->config.Kf * target;
    output = this->config.guard ? guard(output) : output;
    value = current;
    return output;
}