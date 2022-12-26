#ifndef RelayRinger_H_
#define RelayRinger_H_

#include <Arduino.h>
#include <RelayEx.h>

class PCF8574;

class RelayRinger : public RelayEx
{
    PCF8574& _expander;
    byte _pinA;
    byte _pinB;

    unsigned long _previousDingDong;
    unsigned long _intervalDingDong;

public:
    RelayRinger(PCF8574& expander, byte pinA, byte pinB, bool defaultVal);
    RelayRinger(const RelayRinger& other);
    RelayRinger& operator=(const RelayRinger& other);
    virtual ~RelayRinger();

    virtual void update();
protected:
    // relay type dependant methods
    virtual void On();
    virtual void Off();
};

#endif // RelayRinger_H_