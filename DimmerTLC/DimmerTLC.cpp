#include "DimmerTLC.h"
#include <Tlc5940.h>

#define FADE_LED_PWM_BITS 12
#include "GammaCorrection.h"

#if defined(MYSENSORS_INTEGRATION)
#include <core\MyMessage.h>
#include <core\MySensorsCore.h>
#endif

// Implementation of DimmerTLC class

unsigned int DimmerTLC::RAW_VALUE_MIN = 0;    // full OFF
unsigned int DimmerTLC::RAW_VALUE_MAX = 4095; // full ON

#if defined(MYSENSORS_INTEGRATION)
MyMessage* DimmerTLC::MYMESSAGE_ACCESSOR = nullptr;   // reference to global message to controller, used to construct messages "on the fly"
#endif

DimmerTLC::DimmerTLC(byte pin, byte defaultVal):
    DimmerEx(defaultVal),
    _pin(pin)
{
}

DimmerTLC::DimmerTLC(const DimmerTLC& other):
DimmerEx(other)
{
    CopyFrom(other);
}

DimmerTLC::~DimmerTLC()
{
}

DimmerTLC& DimmerTLC::operator=(const DimmerTLC& other)
{
    if (&other == this)
        return *this;

    DimmerEx::operator=(other);

    CopyFrom(other);

    return *this;
}

void DimmerTLC::CopyFrom(const DimmerTLC& other)
{
    _pin = other._pin;
}

void DimmerTLC::setValue(byte value)
{
    DimmerEx::setValue(value);

    Tlc.set(_pin, getValueRaw()); // gamma corrected value
    Tlc.update();

#if defined(MYSENSORS_INTEGRATION)
    sendMessage_Controller(V_PERCENTAGE, getValue());
#endif
}

unsigned int DimmerTLC::getValueRaw() const
{
    unsigned int rawValueMap = map(_value,
        DimmerEx::VALUE_MIN,
        DimmerEx::VALUE_MAX,
        DimmerTLC::RAW_VALUE_MIN,
        DimmerTLC::RAW_VALUE_MAX);
    //Serial.print("From map: ");
    //Serial.println(rawValueMap);

    //unsigned int rawValueTab = FadeLedGammaTable[_value];
    //Serial.print("From tab: ");
    //Serial.println(rawValueTab);

    // TODO - compare rawValueMap with rawValueTab (and potentially make return value parametrized)
    return rawValueMap;
}

void DimmerTLC::setPin(byte pin)
{
    _pin = pin;
}

byte DimmerTLC::getPin() const
{
    return _pin;
}

#if defined(MYSENSORS_INTEGRATION)

void DimmerTLC::sendMessage_Controller(byte type, byte command)
{
    // send actual light status to controller (if DimmerTLC::MYMESSAGE_ACCESSOR was set)
    if (DimmerTLC::MYMESSAGE_ACCESSOR != NULL)
        send(DimmerTLC::MYMESSAGE_ACCESSOR->setSensor(_mySensorId).setType(type).set(command));
}

// Static member functions

void DimmerTLC::setMyMessageAccessor(MyMessage* myMessageAccessor)
{
    DimmerTLC::MYMESSAGE_ACCESSOR = myMessageAccessor;
};

MyMessage* DimmerTLC::getMyMessageAccessor()
{
    return DimmerTLC::MYMESSAGE_ACCESSOR;
};

#endif
