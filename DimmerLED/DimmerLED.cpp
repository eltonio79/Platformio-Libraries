#include "DimmerLED.h"

#define FADE_LED_PWM_BITS 8
#include "GammaCorrection.h"

#if defined(MYSENSORS_INTEGRATION)
#include <core\MyMessage.h>
#include <core\MySensorsCore.h>
#endif

// Implementation of DimmerLED class

byte DimmerLED::RAW_VALUE_MIN = 0;   // full OFF
byte DimmerLED::RAW_VALUE_MAX = 255; // full ON

#if defined(MYSENSORS_INTEGRATION)
MyMessage* DimmerLED::MYMESSAGE_ACCESSOR = nullptr;   // reference to global message to controller, used to construct messages "on the fly"
#endif

DimmerLED::DimmerLED(byte* pins, byte minimumValue, byte maximumValue, byte defaultVal) :
    DimmerEx(defaultVal),
    _minimumValue(minimumValue),
    _maximumValue(maximumValue),
    _pins(pins),
    _pinsCount(sizeof(*pins) / sizeof(byte)),
    _pinsActive(_pinsCount)
{
}

DimmerLED::DimmerLED(byte pin, byte defaultVal) :
    DimmerEx(defaultVal),
    _minimumValue(RAW_VALUE_MIN),
    _maximumValue(RAW_VALUE_MAX),
    _pins(new byte(pin)),
    _pinsCount(sizeof(*_pins) / sizeof(byte)),
    _pinsActive(_pinsCount)
{
}

DimmerLED::DimmerLED(const DimmerLED& other) :
    DimmerEx(other)
{
    CopyFrom(other);
}

DimmerLED::~DimmerLED()
{
}

DimmerLED& DimmerLED::operator=(const DimmerLED& other)
{
    if (&other == this)
        return *this;

    DimmerEx::operator=(other);

    CopyFrom(other);

    return *this;
}

void DimmerLED::CopyFrom(const DimmerLED& other)
{
    if(_pins != nullptr)
        delete _pins;
    _pins = new byte(other._pinsCount);
    memcpy(_pins, other._pins, other._pinsCount);
    _pinsCount = other._pinsCount;
    _pinsActive = other._pinsActive;
    _minimumValue = other._minimumValue;
    _maximumValue = other._maximumValue;
}

void DimmerLED::setValueReal(byte value)
{
    unsigned int rawValue = getValueRaw();

    for (uint8_t i = 0; i < _pinsActive; ++i)
        analogWrite(_pins[i], rawValue);
}

void DimmerLED::setValue(byte value)
{
    if (_pins == NULL || _pinsActive == 0)
        return;

    DimmerEx::setValue(value);

    setValueReal(value);

#if defined(MYSENSORS_INTEGRATION)
    sendMessage_Controller(V_PERCENTAGE, getValue());
#endif
}

unsigned int DimmerLED::getValueRaw() const
{
    // calculate RAW dimming value
    unsigned int valueRaw = DimmerLED::RAW_VALUE_MIN;

    if (_value <= DimmerEx::VALUE_MIN)
        valueRaw = DimmerLED::RAW_VALUE_MIN; // turn OFF
    else if (_value >= DimmerEx::VALUE_MAX)
        valueRaw = DimmerLED::RAW_VALUE_MAX;  // turn ON
    else
        valueRaw = FadeLedGammaTable[_value]; // gamma corrected value
        //valueRaw = map(_value, 1, DimmerEx::VALUE_MAX, _minimumValue, _maximumValue); // DIM message (inside allowed range)

    return valueRaw;
}

void DimmerLED::setMinimumValue(byte value)
{
    if (value > DimmerLED::RAW_VALUE_MAX)
        value = DimmerLED::RAW_VALUE_MAX;
    if (value < DimmerLED::RAW_VALUE_MIN)
        value = DimmerLED::RAW_VALUE_MIN;

    _minimumValue = value;
};

byte DimmerLED::getMinimumValue() const
{
    return _minimumValue;
};

void DimmerLED::setMaximumValue(byte value)
{
    if (value > DimmerLED::RAW_VALUE_MAX)
        value = DimmerLED::RAW_VALUE_MAX;
    if (value < DimmerLED::RAW_VALUE_MIN)
        value = DimmerLED::RAW_VALUE_MIN;

    _maximumValue = value;
};

byte DimmerLED::getMaximumValue() const
{
    return _maximumValue;
};

void DimmerLED::setPinsActive(uint8_t pinsActive)
{
    if (pinsActive <= _pinsCount)
    {
        // turn off higher leds if neccessary
        if (pinsActive < _pinsActive)
        {
            for (uint8_t i = pinsActive; i < _pinsCount; ++i)
                analogWrite(_pins[i], LOW);
        }

        _pinsActive = pinsActive;
    }
}

uint8_t DimmerLED::getPinsActive() const
{
    return _pinsActive;
}

#if defined(MYSENSORS_INTEGRATION)

void DimmerLED::sendMessage_Controller(byte type, byte command)
{
    // send actual light status to controller (if DimmerLED::MYMESSAGE_ACCESSOR was set)
    if (DimmerLED::MYMESSAGE_ACCESSOR != nullptr)
    {
        send(DimmerLED::MYMESSAGE_ACCESSOR->setSensor(_mySensorId).setType(type).set(command));
    }
}

// Static member functions

void DimmerLED::setMyMessageAccessor(MyMessage* myMessageAccessor)
{
    DimmerLED::MYMESSAGE_ACCESSOR = myMessageAccessor;
};

MyMessage* DimmerLED::getMyMessageAccessor()
{
    return DimmerLED::MYMESSAGE_ACCESSOR;
};

#endif
