#ifndef DIMMERTLC_H_
#define DIMMERTLC_H_

#include "DimmerEx.h"

class MyMessage;

class DimmerTLC : public DimmerEx
{
private:
    static unsigned int RAW_VALUE_MIN;      // minimum RAW value (normally 0)
    static unsigned int RAW_VALUE_MAX;      // maximum RAW value (normally 4095)

#if defined(MYSENSORS_INTEGRATION)
    static MyMessage* MYMESSAGE_ACCESSOR;   // reference to global message to controller, used to construct messages "on the fly"
#endif

public:
    DimmerTLC(byte pin, byte defaultVal);
    DimmerTLC(const DimmerTLC& other);
    virtual ~DimmerTLC();
    DimmerTLC& operator=(const DimmerTLC& other);

    // Member setters / getters
    virtual void setValue(byte value);

    // Calculates RAW dimming value (acceptable by hardware, derived dimmer)
    virtual unsigned int getValueRaw() const;

    void setPin(byte pin);
    byte getPin() const;

    // MySensors message interface
#if defined(MYSENSORS_INTEGRATION)
    static void setMyMessageAccessor(MyMessage* myMessageAccessor);
    static MyMessage* getMyMessageAccessor();
#endif

private:
    void CopyFrom(const DimmerTLC& other);
    
#if defined(MYSENSORS_INTEGRATION)
    void sendMessage_Controller(byte type, byte command);
#endif

    // pin number on TLC device
    byte _pin;
};

#endif // DIMMERTLC_H_
