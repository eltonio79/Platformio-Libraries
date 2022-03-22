#ifndef RelayDoor_H_
#define RelayDoor_H_

#include <Arduino.h>
#include <RelayEx.h>

class PCF8574;

class RelayDoor : public RelayEx
{
    PCF8574& _expander;
    byte _pinA;
    byte _pinB;

    unsigned long _maximumOnTime;

public:
    RelayDoor(PCF8574& expander, byte pinA, byte pinB, bool defaultVal);
    RelayDoor(const RelayDoor& other);
    RelayDoor& operator=(const RelayDoor& other);
    virtual ~RelayDoor();

    virtual bool switchOn(unsigned long seconds);
    virtual bool switchOff(unsigned long seconds);
    virtual bool switchOn();
    virtual bool switchOff();

    void setOpenPeriod(int openPeriod);
    int getOpenPeriod() const;

protected:
    // relay type dependant methods
    virtual void On();
    virtual void Off();
};

#endif // RelayDoor_H_