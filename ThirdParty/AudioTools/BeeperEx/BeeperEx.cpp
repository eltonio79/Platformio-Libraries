#include "BeeperEx.h"
#include "Pitches.h"
#include <NewTone.h>

BeeperEx::~BeeperEx()
{
}

BeeperEx::BeeperEx(byte pin, unsigned long beepFrequency, unsigned long beepLength, unsigned long beepTone, bool isSwitchedOn) :
_pin(pin),
_beepFrequency(beepFrequency),
_beepLength(beepLength),
_beepTone(beepTone),
_isOn(isSwitchedOn),
_previousBeeperMillis(0)
{
}

void BeeperEx::reInit(unsigned long beepFrequency, unsigned long beepLength, unsigned long beepTone)
{
    _beepFrequency = beepFrequency;
    _beepLength = beepLength;
    _beepTone = beepTone;
}

bool BeeperEx::isSwitchedOn()
{
    return _isOn;
}

void BeeperEx::switchOn()
{
    _isOn = true;
}

void BeeperEx::switchOff()
{
    _isOn = false;
}

void BeeperEx::update()
{
    if (_isOn)
    {
        if (millis() - _previousBeeperMillis > _beepFrequency)
        {
            _previousBeeperMillis = millis();
            
             NewTone(_pin, /*_beep
                           Tone*/random(NOTE_C5, NOTE_C4), _beepLength);
        }
    }
}
