#include "qei.h"

QEI::QEI(uint8_t pin_a, uint8_t pin_b, int ppr)
{
    this->pin_a = pin_a;
    this->pin_b = pin_b;
    this->ppr = ppr;
}

QEI::~QEI()
{
    gpio_set_irq_enabled(this->pin_a, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, false);
    gpio_set_irq_enabled(this->pin_b, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, false);
    gpio_deinit(this->pin_a);
    gpio_deinit(this->pin_b);
}

void QEI::init()
{
    gpio_init(pin_a);
    gpio_set_dir(pin_a, GPIO_IN);
    gpio_set_irq_enabled(pin_a, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true);

    gpio_init(pin_b);
    gpio_set_dir(pin_b, GPIO_IN);
    gpio_set_irq_enabled(pin_b, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true);
}

void QEI::callback_register(uint gpio, uint32_t events)
{
    if (gpio == this->pin_a)
    {
        this->pin_a_irq(gpio, events);
    }
    else if (gpio == this->pin_b)
    {
        this->pin_b_irq(gpio, events);
    }
}

void QEI::pin_a_irq(uint gpio, uint32_t events)
{
    if (events & GPIO_IRQ_EDGE_RISE)
    {
        if (gpio_get(this->pin_b))
        {
            this->counts++;
        }
        else
        {
            this->counts--;
        }
    }
    else if (events & GPIO_IRQ_EDGE_FALL)
    {
        if (gpio_get(this->pin_b))
        {
            this->counts--;
        }
        else
        {
            this->counts++;
        }
    }
}

void QEI::pin_b_irq(uint gpio, uint32_t events)
{
    if (events & GPIO_IRQ_EDGE_RISE)
    {
        if (gpio_get(this->pin_a))
        {
            this->counts--;
        }
        else
        {
            this->counts++;
        }
    }
    else if (events & GPIO_IRQ_EDGE_FALL)
    {
        if (gpio_get(this->pin_a))
        {
            this->counts++;
        }
        else
        {
            this->counts--;
        }
    }
}

int QEI::get_counts()
{
    return this->counts;
}

int QEI::get_ppr()
{
    return this->ppr;
}

int QEI::get_cpr()
{
    return this->ppr * 4;
}

double QEI::get_rotations()
{
    return (double)this->counts / (double)this->get_cpr();
}

double QEI::get_radians()
{
    return this->get_rotations() * 2 * PI;
}

void QEI::reset()
{
    this->counts = 0;
}

void QEI::set_rotations(double rotations)
{
    this->counts = (int)(rotations * this->get_cpr());
}

void QEI::set_radians(double radians)
{
    this->set_rotations(radians / (2 * PI));
}