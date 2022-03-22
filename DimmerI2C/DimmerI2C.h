#ifndef DIMMERI2C_H_
#define DIMMERI2C_H_

#include <DimmerEx.h>

class MyMessage;

class DimmerI2C : public DimmerEx
{
private:
    static byte RAW_VALUE_MIN;              // minimum RAW value (normally 128)
    static byte RAW_VALUE_MAX;              // minimum RAW value (normally 0)

#if defined(MYSENSORS_INTEGRATION)
    static MyMessage* MYMESSAGE_ACCESSOR;   // reference to global message to controller, used to construct messages "on the fly"
#endif

public:
    // #param slaveI2CAddress adres sciemniacza I2C (Attiny85 AC DIMMER MODULE or whatever..)
    // #param minimumValue (0 - 128); dobiera� eksperymentalnie (per �ar�wka / triak)
    // #param maximumValue (0 - 128); dobiera� eksperymentalnie (per �ar�wka / triak)
    // #param defaultVal; domyślna wartość
    DimmerI2C(byte slaveI2CAddress, byte minimumValue, byte maximumValue, byte defaultVal);
    DimmerI2C(const DimmerI2C& other);
    virtual ~DimmerI2C();
    DimmerI2C& operator=(const DimmerI2C& other);

    // Member setters / getters
    virtual void setValue(byte value);

    // Calculates RAW dimming value (acceptable by hardware, derived dimmer)
    virtual unsigned int getValueRaw() const;

    void setMinimumValue(byte value);
    byte getMinimumValue() const;

    void setMaximumValue(byte value);
    byte getMaximumValue() const;

    void setSlaveI2CAddress(byte value);
    byte getSlaveI2CAddress() const;

    // MySensors message interface
#if defined(MYSENSORS_INTEGRATION)
    static void setMyMessageAccessor(MyMessage* myMessageAccessor);
    static MyMessage* getMyMessageAccessor();
#endif

private:
    void CopyFrom(const DimmerI2C& other);

    void sendMessage_I2C(byte message);
    
#if defined(MYSENSORS_INTEGRATION)
    void sendMessage_Controller(byte type, byte command);
#endif

    byte _minimumValue;
    byte _maximumValue;
    byte _slaveI2CAddress;
};

#endif // DIMMERI2C_H_
