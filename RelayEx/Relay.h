#ifndef Relay_H_
#define Relay_H_

#include "Arduino.h"

class Relay
{
protected:
    bool _isOn;

private:
    void CopyFrom(const Relay& other);

    // internal members
    bool _isTiming;
    unsigned long _triggerStartMillis;
    unsigned long _triggerDelayMillis;
    unsigned long _minToggleMillis;

public:
    Relay(unsigned long minToggleMillis, bool defaultVal);
    Relay(const Relay& other);
    virtual ~Relay();
    Relay& operator=(const Relay& other);

    // Member setters / getters
    virtual bool isSwitchedOn();
    virtual bool switchOn(unsigned long milliSeconds);
    virtual bool switchOff(unsigned long milliSeconds);
    virtual bool switchOn();
    virtual bool switchOff();
    virtual bool switchToggle();

    // call it in the main loop
    virtual void update();

    // Sequence number in the dimmers array (group ID)
    virtual void setMySensorId(byte value) = 0;
    virtual byte getMySensorId() const = 0;

protected:
    // methods implementation to override
    virtual bool isOnImpl();
    virtual bool switchOnImpl(unsigned long milliSeconds);
    virtual bool switchOffImpl(unsigned long milliSeconds);
    virtual bool switchOnImpl();
    virtual bool switchOffImpl();
    virtual bool switchToggleImpl();

    virtual void updateImpl();

    // mandatory relay type dependant on / off methods to override
    virtual void On() = 0;
    virtual void Off() = 0;
};

#endif // Relay_H_