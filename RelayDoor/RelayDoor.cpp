#include "RelayDoor.h"
#include <PCF8574.h>

// define static class members
RelayDoor::RelayDoor(PCF8574& expander, byte pinA, byte pinB, bool defaultVal) :
RelayEx(0, defaultVal), // better to call it instead of implicite call..
_expander(expander),
_pinA(pinA),
_pinB(pinB),
_maximumOnTime(7000) // bo tak
{
    // nie dzia�a tu _expander.write(...) - wiesza MySensors / system !
}

RelayDoor::RelayDoor(const RelayDoor& other) :
RelayEx(other),
_expander(other._expander),
_pinA(other._pinA),
_pinB(other._pinB),
_maximumOnTime(other._maximumOnTime)
{
}

RelayDoor::~RelayDoor()
{
}

RelayDoor& RelayDoor::operator=(const RelayDoor& other)
{
    if (&other == this)
        return *this;

    RelayEx::operator=(other);

    _expander = other._expander;
    _pinA = other._pinA;
    _pinB = other._pinB;
    _maximumOnTime = other._maximumOnTime;

    return *this;
}

void RelayDoor::setOpenPeriod(int openPeriod)
{
    _maximumOnTime = openPeriod;
}

int RelayDoor::getOpenPeriod() const
{
    return _maximumOnTime;
}

bool RelayDoor::switchOn(unsigned long seconds)
{
    return Relay::switchOnImpl(seconds > _maximumOnTime ? _maximumOnTime : seconds);
}

bool RelayDoor::switchOff(unsigned long seconds)
{
    return Relay::switchOffImpl();
}

bool RelayDoor::switchOn()
{
    return Relay::switchOnImpl(_maximumOnTime);
}

bool RelayDoor::switchOff()
{
    return Relay::switchOffImpl();
}

void RelayDoor::On()
{
    _expander.write(_pinA, LOW);
    _expander.write(_pinB, HIGH);

    RelayEx::On();
}

void RelayDoor::Off()
{
    _expander.write(_pinA, LOW);
    _expander.write(_pinB, LOW);

    RelayEx::Off();
}