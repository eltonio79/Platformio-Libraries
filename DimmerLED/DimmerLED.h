#ifndef DIMMERLED_H_
#define DIMMERLED_H_

// define if needed; TODO - move MySensors Logic into some template common class
// #define MYSENSORS_INTEGRATION

#include <Arduino.h>
#include <DimmerEx.h>

class MyMessage;

class DimmerLED : public DimmerEx
{
private:
#if defined(MYSENSORS_INTEGRATION)
    static MyMessage* MYMESSAGE_ACCESSOR;   // reference to global message to controller, used to construct messages "on the fly"
#endif

public:
    static byte RAW_VALUE_MIN; // minimum RAW value (normally 0)
    static byte RAW_VALUE_MAX; // minimum RAW value (normally 255)

    typedef uint8_t(*curveFunction)(uint8_t);

    // #param pins
    // #param minimumValue (0 - 255); dobiera� eksperymentalnie
    // #param maximumValue (0 - 255); dobiera� eksperymentalnie
    // #param defaultVal; default value
    DimmerLED(byte* pins,
              byte minimumValue,
              byte maximumValue,
              byte defaultVal);
    DimmerLED(byte pin, byte defaultVal);
    DimmerLED(const DimmerLED& other);
    virtual ~DimmerLED();
    DimmerLED& operator=(const DimmerLED& other);

    // Member setters / getters
    virtual void setValue(byte value);

    // Calculates RAW dimming value (acceptable by hardware, derived dimmer)
    virtual unsigned int getValueRaw() const;

    void setMinimumValue(byte value);
    byte getMinimumValue() const;

    void setMaximumValue(byte value);
    byte getMaximumValue() const;

    void setPinsActive(uint8_t pinsActive);
    uint8_t getPinsActive() const;

    // MySensors message interface
#if defined(MYSENSORS_INTEGRATION)
    static void setMyMessageAccessor(MyMessage* myMessageAccessor);
    static MyMessage* getMyMessageAccessor();
#endif

private:
    void CopyFrom(const DimmerLED& other);
    void setValueReal(byte value);

#if defined(MYSENSORS_INTEGRATION)
    void sendMessage_Controller(byte type, byte command);
#endif

    byte _minimumValue;
    byte _maximumValue;

    uint8_t* _pins;
    uint8_t  _pinsCount;
    uint8_t  _pinsActive;
};

#endif // DIMMERLED_H_
