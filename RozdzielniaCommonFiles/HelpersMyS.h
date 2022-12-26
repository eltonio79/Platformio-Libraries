#ifndef HelperMyS_h
#define HelperMyS_h

#include <Arduino.h>

// helper stuff to reduce redundant code in receive() function

extern MyMessage commonMyMessage;

template <class T>
void sendAnyToController(T value, byte mySensorId, mysensors_data_t mySensorData)
{
    send(commonMyMessage.setSensor(mySensorId).setType(mySensorData).set(value));
}

template <>
void sendAnyToController<float>(float value, byte mySensorId, mysensors_data_t mySensorData)
{
    send(commonMyMessage.setSensor(mySensorId).setType(mySensorData).set(value, 2));
}

template <class T>
T getAnyPayload(const MyMessage& message)
{
    return static_cast<T>(message.getCustom());
}

template <>
double getAnyPayload<double>(const MyMessage& message)
{
    return static_cast<double>(message.getFloat());
}

template <>
float getAnyPayload<float>(const MyMessage& message)
{
    return message.getFloat();
}

template <>
bool getAnyPayload<bool>(const MyMessage& message)
{
    return message.getBool();
}

template <>
unsigned char getAnyPayload<unsigned char>(const MyMessage& message)
{
    return message.getByte();
}

template <>
int getAnyPayload<int>(const MyMessage& message)
{
    return message.getInt();
}

template <>
unsigned int getAnyPayload<unsigned int>(const MyMessage& message)
{
    return message.getUInt();
}

template <>
long getAnyPayload<long>(const MyMessage& message)
{
    return message.getLong();
}

template <>
unsigned long getAnyPayload<unsigned long>(const MyMessage& message)
{
    return message.getULong();
}

void receiveTreatmentDimmer(const MyMessage& message, uint8_t command, byte mySensorsId, DimmerEx& dimmer)
{
    if (message.sensor == mySensorsId)
    {
        if (command == C_SET)
        {
            if (initializationPhase)
            {
                ++incomingMessagesCounter;
            }

            dimmer.setValue(getAnyPayload<byte>(message));
        }
        else if (command == C_REQ)
        {
            sendAnyToController(dimmer.getValue(), message.sensor, static_cast<mysensors_data_t>(message.type));
        }
    }
}

template <class T>
void receiveTreatmentRelay(const MyMessage& message, uint8_t command, byte mySensorsId, T& relay)
{
    if (message.sensor == mySensorsId)
    {
        if (command == C_SET)
        {
            if (initializationPhase)
            {
                ++incomingMessagesCounter;
            }

            if (getAnyPayload<bool>(message))
            {
                relay.switchOn();
            }
            else
            {
                relay.switchOff();
            }
        }
        else if (command == C_REQ)
        {
            sendAnyToController(relay.isSwitchedOn(), message.sensor, static_cast<mysensors_data_t>(message.type));
        }
    }
}

template <class T>
void receiveTreatmentAny(const MyMessage& message, uint8_t command, byte mySensorsId, T& value)
{
    if (message.sensor == mySensorsId)
    {
        if (command == C_SET)
        {
            if (initializationPhase)
            {
                ++incomingMessagesCounter;
            }

            value = getAnyPayload<T>(message);
        }
        else if (command == C_REQ)
        {
            sendAnyToController(value, message.sensor, static_cast<mysensors_data_t>(message.type));
        }
    }
}

template <class T, class A>
void receiveTreatmentAutomation(const MyMessage& message, uint8_t command, byte mySensorsId, T& value, A* acutatorFirst = nullptr, A* acutatorSecond = nullptr)
{
    receiveTreatmentAny(message, command, mySensorsId, value);

    if (message.sensor == mySensorsId && command == C_SET)
    {
        // turn off related acutators only when setting automation is ON
        if (value)
        {
            if (acutatorFirst != nullptr)
            {
                acutatorFirst->switchOff();
            }
            if (acutatorSecond != nullptr)
            {
                acutatorSecond->switchOff();
            }
        }
    }
}

#endif // HelperMyS_h
