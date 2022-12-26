#ifndef BeeperEx_H_
#define BeeperEx_H_

#include "Arduino.h"

class BeeperEx
{
private:
    byte _pin;
    unsigned long _previousBeeperMillis;
    unsigned long _beepFrequency;
    unsigned long _beepLength;
    unsigned long _beepTone;
    bool _isOn;

public:
    BeeperEx(byte pin, unsigned long beepFrequency, unsigned long beepLength, unsigned long beepTone, bool isSwitchedOn);
    ~BeeperEx();

    void reInit(unsigned long beepFrequency, unsigned long beepLength, unsigned long beepTone);

    bool isSwitchedOn();
    void switchOn();
    void switchOff();
    void update();
};

#endif // BeeperEx_H_