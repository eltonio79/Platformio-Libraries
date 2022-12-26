#include "RelayEx.h"
#include <core\MyMessage.h>
#include <core\MySensorsCore.h>

MyMessage* RelayEx::MYMESSAGE_ACCESSOR = nullptr;   // reference to global message to controller, used to construct messages "on the fly"

RelayEx::RelayEx(unsigned long minToggleMillis, bool defaultVal) :
Relay(minToggleMillis, defaultVal),
_mySensorId(0)
{
}

RelayEx::RelayEx(const RelayEx& other):
Relay(other)
{
    CopyFrom(other);
}

RelayEx::~RelayEx()
{
}

RelayEx& RelayEx::operator=(const RelayEx& other)
{
    if (&other == this)
        return *this;

    Relay::operator=(other);

    CopyFrom(other);

    return *this;
}

void RelayEx::CopyFrom(const RelayEx& other)
{
    _mySensorId = other._mySensorId;
}

void RelayEx::setMySensorId(byte value)
{
    _mySensorId = value;
}

byte RelayEx::getMySensorId() const
{
    return _mySensorId;
}

void RelayEx::sendMessage_Controller(byte type, byte command)
{
    // send status to controller (if RelayEx::MYMESSAGE_ACCESSOR was set)
    if (RelayEx::MYMESSAGE_ACCESSOR != nullptr)
        send(RelayEx::MYMESSAGE_ACCESSOR->setSensor(_mySensorId).setType(type).set(command));
}

void RelayEx::On()
{
    // send actual relay status to controller
    sendMessage_Controller(V_STATUS, _isOn);
}

void RelayEx::Off()
{
    // send actual relay status to controller
    sendMessage_Controller(V_STATUS, _isOn);
}

// Static member functions

void RelayEx::setMyMessageAccessor(MyMessage* myMessageAccessor)
{
    RelayEx::MYMESSAGE_ACCESSOR = myMessageAccessor;
}

MyMessage* RelayEx::getMyMessageAccessor()
{
    return RelayEx::MYMESSAGE_ACCESSOR;
}
