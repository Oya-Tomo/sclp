#include <stdio.h>

#include "pid.h"

PID::PID(PIDType type)
{
    type = type;
    reset();
}

void PID::configure(config_t config)
{
    this->config = config;
}

void PID::reset()
{
    errors[0] = 0.0;
    errors[1] = 0.0;
    errors[2] = 0.0;
    integral = 0.0;
    output = 0.0;
    target = 0.0;
    value = 0.0;
}

double PID::calculate(double target, double current, double dt)
{

    switch (type)
    {
    case PIDType::pPID:
        return calculate_pPID(target, current, dt);
    case PIDType::sPID:
        return calculate_sPID(target, current, dt);
    case PIDType::PI_D:
        return calculate_PI_D(target, current, dt);
    case PIDType::I_PD:
        return calculate_I_PD(target, current, dt);
    default:
        return 0;
    }
}

void PID::add_error(double error)
{
    errors[2] = errors[1];
    errors[1] = errors[0];
    errors[0] = error;
}

double PID::guard(double value)
{
    double min = this->config.min;
    double max = this->config.max;
    return value > max ? max : (min > value ? min : value);
}

double PID::calculate_pPID(double target, double current, double dt)
{
    add_error(target - current);

    integral += (errors[0] + errors[1]) / 2 * dt;

    double mp = this->config.Kp * errors[0];
    double mi = this->config.Ki * integral;
    double md = this->config.Kd * (errors[0] - errors[1]) / dt;

    output = mp + mi + md;
    output += this->config.Kf * target; // Feed-Forward
    output = this->config.guard ? guard(output) : output;

    return output;
}

double PID::calculate_sPID(double target, double current, double dt)
{
    add_error(target - current);
    double mp = this->config.Kp * (errors[0] - errors[1]);
    double mi = this->config.Ki * errors[0] * dt;
    double md = this->config.Kd * (errors[0] - (2 * errors[1]) + errors[2]) / dt;

    output += mp + mi + md;
    output += this->config.Kf * (target - target) / dt; // Feed-Forward
    target = target;
    return this->config.guard ? guard(output) : output;
}

double PID::calculate_PI_D(double target, double current, double dt)
{
    add_error(target - current);
    integral += (errors[0] + errors[1]) / 2 * dt;

    double mp = this->config.Kp * errors[0];
    double mi = this->config.Ki * integral;
    double md = this->config.Kd * (current - value) / dt;

    output = mp + mi - md;
    output += this->config.Kf * target;
    output = this->config.guard ? guard(output) : output;
    value = current;
    return output;
}

double PID::calculate_I_PD(double target, double current, double dt)
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