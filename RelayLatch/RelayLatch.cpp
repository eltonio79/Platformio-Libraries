#include "RelayLatch.h"
#include <PCF8574.h>

// define static class members
const byte RelayLatch::_switchingOffsetTimeMillis = 15;

RelayLatch::RelayLatch(PCF8574& expander, byte pinA, byte pinB, bool defaultVal) :
RelayEx(0, defaultVal), // better to call it instead of implicite call..
_expander(expander),
_pinA(pinA),
_pinB(pinB)
{
    // nie dzia�a tu _expander.write(...) - wiesza MySensors / system !
}

RelayLatch::RelayLatch(const RelayLatch& other) :
RelayEx(other),
_expander(other._expander),
_pinA(other._pinA),
_pinB(other._pinB)
{
}

RelayLatch::~RelayLatch()
{
}

RelayLatch& RelayLatch::operator=(const RelayLatch& other)
{
    if (&other == this)
        return *this;

    RelayEx::operator=(other);

    _expander = other._expander;
    _pinA = other._pinA;
    _pinB = other._pinB;

    return *this;
}

void RelayLatch::On()
{
    _expander.write(_pinA, LOW);
    _expander.write(_pinB, HIGH);
    delay(RelayLatch::_switchingOffsetTimeMillis);
    _expander.write(_pinA, LOW);
    _expander.write(_pinB, LOW);

    RelayEx::On();
}

void RelayLatch::Off()
{
    _expander.write(_pinA, HIGH);
    _expander.write(_pinB, LOW);
    delay(RelayLatch::_switchingOffsetTimeMillis);
    _expander.write(_pinA, LOW);
    _expander.write(_pinB, LOW);

    RelayEx::Off();
}