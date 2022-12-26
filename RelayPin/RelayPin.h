#ifndef RelayPin_H_
#define RelayPin_H_

#include <Arduino.h>
#include <RelayEx.h>

class RelayPin : public RelayEx
{
    byte _pin;

public:
    RelayPin(byte pin, unsigned long minToggleMillis, bool defaultVal);
    RelayPin(const RelayPin& other);
    RelayPin& operator=(const RelayPin& other);
    virtual ~RelayPin();

protected:
    // relay type dependant methods
    virtual void On();
    virtual void Off();
};

#endif // RelayPin_H_
