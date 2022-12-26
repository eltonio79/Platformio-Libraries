#ifndef RelayLatch_H_
#define RelayLatch_H_

#include <Arduino.h>
#include <RelayEx.h>

class PCF8574;

class RelayLatch : public RelayEx
{
    static const byte _switchingOffsetTimeMillis;

    PCF8574& _expander;
    byte _pinA;
    byte _pinB;

public:
    RelayLatch(PCF8574& expander, byte pinA, byte pinB, bool defaultVal);
    RelayLatch(const RelayLatch& other);
    RelayLatch& operator=(const RelayLatch& other);
    virtual ~RelayLatch();

protected:
    // relay type dependant methods
    virtual void On();
    virtual void Off();
};

#endif // RelayLatch_H_