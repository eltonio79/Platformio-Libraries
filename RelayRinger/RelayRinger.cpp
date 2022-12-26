#include "RelayRinger.h"
#include <PCF8574.h>

RelayRinger::RelayRinger(PCF8574& expander, byte pinA, byte pinB, bool defaultVal) :
RelayEx(0, defaultVal), // better to call it instead of implicite call..
_expander(expander),
_pinA(pinA),
_pinB(pinB),
_previousDingDong(0),
_intervalDingDong(100)
{
    // nie dzia�a tu _expander.write(...) - wiesza MySensors / system !
}

RelayRinger::RelayRinger(const RelayRinger& other) :
RelayEx(other),
_expander(other._expander),
_pinA(other._pinA),
_pinB(other._pinB),
_previousDingDong(other._previousDingDong),
_intervalDingDong(other._intervalDingDong)
{
}

RelayRinger::~RelayRinger()
{
}

RelayRinger& RelayRinger::operator=(const RelayRinger& other)
{
    if (&other == this)
        return *this;

    RelayEx::operator=(other);

    _expander = other._expander;
    _pinA = other._pinA;
    _pinB = other._pinB;
    _previousDingDong = other._previousDingDong;
    _intervalDingDong = other._intervalDingDong;

    return *this;
}

void RelayRinger::update()
{
    static bool dingDong = true;

    if (this->isSwitchedOn())
    {
        if (millis() - _previousDingDong > _intervalDingDong)
        {
            _previousDingDong = millis();

            if (dingDong)
            {
                _expander.write(_pinA, LOW);
                _expander.write(_pinB, HIGH);
            }
            else
            {
                _expander.write(_pinA, LOW);
                _expander.write(_pinB, LOW);
            }

            dingDong = !dingDong;
        }
    }

    Relay::update();
}

void RelayRinger::On()
{
    RelayEx::On();
}

void RelayRinger::Off()
{
    RelayEx::Off();
}