#include "RelayPin.h"

RelayPin::RelayPin(byte pin, unsigned long minToggleMillis, bool defaultVal) :
RelayEx(minToggleMillis, defaultVal),
_pin(pin)
{
}

RelayPin::RelayPin(const RelayPin& other) :
RelayEx(other),
_pin(other._pin)
{
}

RelayPin::~RelayPin()
{
}

RelayPin& RelayPin::operator=(const RelayPin& other)
{
    if (&other == this)
        return *this;

    RelayEx::operator=(other);

    _pin = other._pin;

    return *this;
}

void RelayPin::On()
{
    digitalWrite(_pin, HIGH);

    RelayEx::On();
}

void RelayPin::Off()
{
    digitalWrite(_pin, LOW);

    RelayEx::Off();
}
