#include "Beeper.h"

Beeper::~Beeper()
{
}

Beeper::Beeper(byte pin) :
_pin(pin),
_isOn(false),
_bTone(false),
_previousBeeperMillis(0),
_beepDelayOn(0),
_beepDelayOff(0)
{
}

bool Beeper::isOn()
{
    return _isOn;
}

void Beeper::init(bool bOn, unsigned long beepDelayOn, unsigned long beepDelayOff)
{
    _isOn = bOn;
    _beepDelayOn = beepDelayOn;
    _beepDelayOff = beepDelayOff;
}

void Beeper::switchOn()
{
    _isOn = true;
}

void Beeper::switchOff()
{
    _isOn = false;
}

void Beeper::update()
{
    if (_isOn)
    {
        if (millis() - _previousBeeperMillis > (_bTone ? _beepDelayOn : _beepDelayOff))
        {
            _previousBeeperMillis = millis();
            _bTone = !_bTone;

            analogWrite(_pin, _bTone ? 3 : 0); // 255 = very loud
        }
    }
    else
    {
        analogWrite(_pin, 0);
    }
}