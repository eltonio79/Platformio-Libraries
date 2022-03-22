/* THREE STATE, UNIVERSAL, NOT-BLOCKING, DIMMER BASE CLASS */

#ifndef DIMMEREX_H_
#define DIMMEREX_H_

#include <Arduino.h>

class DimmerEx
{
protected:
    static byte VALUE_MIN;
    static byte VALUE_MAX;

public:
    static unsigned long FADE_DURATION_OFF;
    static unsigned long FADE_DURATION_MIN;
    static unsigned long FADE_DURATION_MAX;

    DimmerEx(byte defaultVal);
    DimmerEx(const DimmerEx& other);
    virtual ~DimmerEx();
    DimmerEx& operator=(const DimmerEx& other);

    // Member setters / getters
    virtual void setValue(byte value); // accepted values from 0 to 100 (percent of the light)
    byte getValue() const;

    // Calculates RAW dimming value (acceptable by hardware, derived dimmer)
    virtual unsigned int getValueRaw() const;

    // Three-state functionality
    bool isSwitchedOn() const;

    void switchOn();
    void switchToggleOn();
    void switchLast();
    void switchOff();
    void switchToggle(bool threeStateMode);

    // Dimming functionality
    bool isFading() const;
    byte getFadeProgress() const; // returns current dimming progress in percentage ( 0 - 100 % )

    void startFade(byte fadeValue, unsigned long duration);
    void stopFade();

    // This function has to be called in every processor tick / in the loop(s).
    // It is used to deliver non-code-blocking fade effect.
    void update();

    // Sequence number in the dimmers array (group ID)
    virtual void setMySensorId(byte value);
    virtual byte getMySensorId() const;

private:
    void CopyFrom(const DimmerEx& other);

protected:
    // STATE MEMBERS
    byte _value;
    byte _lastValue;
    // NO-DELAY FADING MEMBERS
    byte _fadeFromValue;
    byte _fadeToValue;
    unsigned long _fadeDuration;
    unsigned long _fadeInterval;
    unsigned long _fadeLastStepTime;
    // this identifier helps to hide implementation of comunicate with external things (MySensors)
    byte _mySensorId;
};

#endif // DIMMEREX_H_