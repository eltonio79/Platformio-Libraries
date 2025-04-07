#include "Relay.h"

Relay::Relay(unsigned long minToggleMillis, bool defaultVal) :
_isOn(defaultVal),
_isTiming(false),
_triggerStartMillis(0),
_triggerDelayMillis(0),
_minToggleMillis(minToggleMillis)
{
}

Relay::Relay(const Relay& other)
{
    CopyFrom(other);
}

Relay::~Relay()
{
}

Relay& Relay::operator=(const Relay& other)
{
    if (&other == this)
        return *this;

    CopyFrom(other);

    return *this;
}

void Relay::CopyFrom(const Relay& other)
{
    _isOn = other._isOn;
    _isTiming = other._isTiming;
    _triggerStartMillis = other._triggerStartMillis;
    _triggerDelayMillis = other._triggerDelayMillis;
    _minToggleMillis = other._minToggleMillis;
}

bool Relay::isSwitchedOn()
{
    return isOnImpl();
}

bool Relay::switchOn(unsigned long milliSeconds)
{
    return switchOnImpl(milliSeconds);
}

bool Relay::switchOff(unsigned long milliSeconds)
{
    return switchOffImpl(milliSeconds);
}

bool Relay::switchOn()
{
    return switchOnImpl();
}

bool Relay::switchOff()
{
    return switchOffImpl();
}

bool Relay::switchToggle()
{
    return switchToggleImpl();
}

void Relay::update()
{
    updateImpl();
}

bool Relay::isOnImpl()
{
    return _isOn;
}

bool Relay::switchOnImpl(unsigned long milliSeconds)
{
    if (_isTiming || _isOn)
        return false;

    bool bSwitched = switchOnImpl();

    if (bSwitched)
    {
        _triggerDelayMillis = milliSeconds;
        _isTiming = true;
    }

    return bSwitched;
}

bool Relay::switchOffImpl(unsigned long milliSeconds)
{
    if (_isTiming || !_isOn)
        return false;

    bool bSwitched = switchOffImpl();

    if (bSwitched)
    {
        _triggerDelayMillis = milliSeconds;
        _isTiming = true;
    }

    return bSwitched;
}

bool Relay::switchOnImpl()
{
    if (_isTiming || _isOn)
        return false;

    if (_triggerStartMillis == 0 || millis() - _triggerStartMillis > _minToggleMillis)
    {
        _triggerStartMillis = millis();
        _isOn = true;

        On(); // relay-type dependant virtual function

        return true;
    }
    else
    {
        return false;
    }
}

bool Relay::switchOffImpl()
{
    if (_isTiming || !_isOn)
        return false;

    if (_triggerStartMillis == 0 || millis() - _triggerStartMillis > _minToggleMillis)
    {
        _triggerStartMillis = millis();
        _isOn = false;

        Off(); // relay-type dependant virtual function

        return true;
    }
    else
    {
        return false;
    }
}

bool Relay::switchToggleImpl()
{
    if (_isTiming)
        return false;

    return _isOn ? switchOff() : switchOn();
}

void Relay::updateImpl()
{
    if (_isTiming)
    {
        if (millis() - _triggerStartMillis > _triggerDelayMillis)
        {
            _triggerStartMillis = 0;
            _triggerDelayMillis = 0;
            _isTiming = false;

            switchToggle();
        }
    }
}
