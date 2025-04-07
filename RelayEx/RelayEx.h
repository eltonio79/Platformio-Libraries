#ifndef RelayEx_H_
#define RelayEx_H_

#include "Arduino.h"
#include <Relay.h>

#if defined(MYSENSORS_INTEGRATION)
class MyMessage;
#endif

class RelayEx : public Relay
{
#if defined(MYSENSORS_INTEGRATION)
private:
    static MyMessage* MYMESSAGE_ACCESSOR;   // reference to global message to controller, used to construct messages "on the fly"
#endif

public:
    RelayEx(unsigned long minToggleMillis, bool defaultVal);
    RelayEx(const RelayEx& other);
    virtual ~RelayEx();
    RelayEx& operator=(const RelayEx& other);

    // Sequence number in the dimmers array (group ID)
    virtual void setMySensorId(byte value);
    virtual byte getMySensorId() const;

#if defined(MYSENSORS_INTEGRATION)
    // MySensors message interface
    static void setMyMessageAccessor(MyMessage* myMessageAccessor);
    static MyMessage* getMyMessageAccessor();
#endif

protected:
    virtual void On();
    virtual void Off();

private:
    void CopyFrom(const RelayEx& other);

#if defined(MYSENSORS_INTEGRATION)
    void sendMessage_Controller(byte type, byte command);
#endif

    // this identifier helps to hide implementation of manage MySensors auto acknowledgement
    byte _mySensorId;
};

#endif // RelayEx_H_