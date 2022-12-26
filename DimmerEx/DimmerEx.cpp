#include "DimmerEx.h"

#define UNUSED(argument) (void) (argument)

// Implementation of DimmerEx class

byte DimmerEx::VALUE_MIN = 0;
byte DimmerEx::VALUE_MAX = 100;
unsigned long DimmerEx::FADE_DURATION_OFF = 0;
unsigned long DimmerEx::FADE_DURATION_MIN = 15;        // ma wp�yw na p�ynno�� �ciemniania (15 = 66.6 klatek na sekund�)
unsigned long DimmerEx::FADE_DURATION_MAX = 86400000;  // 1 day (for sanity checks)

DimmerEx::DimmerEx(byte defaultVal) :
    _value(defaultVal),
    _lastValue(DimmerEx::VALUE_MAX / 2), // last value has to be from 1 to 99 %
    _fadeFromValue(_value),
    _fadeToValue(_value),
    _fadeDuration(DimmerEx::FADE_DURATION_OFF),
    _fadeInterval(0),
    _fadeLastStepTime(0),
    _mySensorId(0)
{
}

DimmerEx::DimmerEx(const DimmerEx& other)
{
    CopyFrom(other);
}

DimmerEx::~DimmerEx()
{
}

DimmerEx& DimmerEx::operator=(const DimmerEx& other)
{
    if (&other == this)
        return *this;

    CopyFrom(other);

    return *this;
}

void DimmerEx::CopyFrom(const DimmerEx& other)
{
    _value = other._value;
    _lastValue = other._lastValue;
    _fadeFromValue = other._fadeFromValue;
    _fadeToValue = other._fadeToValue;
    _fadeDuration = other._fadeDuration;
    _fadeInterval = other._fadeInterval;
    _fadeLastStepTime = other._fadeLastStepTime;
    _mySensorId = other._mySensorId;
}

void DimmerEx::setValue(byte value)
{
    // sanity checks
    if (value > DimmerEx::VALUE_MAX)
        value = DimmerEx::VALUE_MAX;
    if (value < DimmerEx::VALUE_MIN)
        value = DimmerEx::VALUE_MIN;

    if (value != _value)
    {
        // last value should be always in the dimming range excluding ON and OFF states
        if (!isFading() && (_value > DimmerEx::VALUE_MIN) && (_value < DimmerEx::VALUE_MAX))
            _lastValue = _value;

        _value = value;
    }
}

byte DimmerEx::getValue() const
{
    return _value;
}

unsigned int DimmerEx::getValueRaw() const
{
    return static_cast<unsigned int>(getValue());
}

bool DimmerEx::isSwitchedOn() const
{
    return _value > DimmerEx::VALUE_MIN;
}

void DimmerEx::switchOn()
{
    setValue(DimmerEx::VALUE_MAX);
    stopFade();
};

void DimmerEx::switchLast()
{
    setValue(_lastValue);
    stopFade();
};

void DimmerEx::switchOff()
{
    setValue(DimmerEx::VALUE_MIN);
    stopFade();
};

void DimmerEx::switchToggle(bool threeStateMode)
{
    if (_value == DimmerEx::VALUE_MAX || (_value > DimmerEx::VALUE_MIN && !threeStateMode))
        switchOff();
    else if (_value == DimmerEx::VALUE_MIN && threeStateMode)
        switchLast();
    else
        switchOn();
};

void DimmerEx::switchToggleOn()
{
    if (_value == DimmerEx::VALUE_MAX)
        switchLast();
    else
        switchOn();
}

bool DimmerEx::isFading() const
{
    return _fadeDuration > DimmerEx::FADE_DURATION_OFF;
}

void DimmerEx::startFade(byte fadeToValue, unsigned long fadeDuration)
{
    // sanity checks
    if (fadeToValue > DimmerEx::VALUE_MAX)
        fadeToValue = DimmerEx::VALUE_MAX;

    if (fadeDuration > DimmerEx::FADE_DURATION_MAX)
        fadeDuration = DimmerEx::FADE_DURATION_MAX;

    if (fadeDuration < DimmerEx::FADE_DURATION_MIN)
        return;

    stopFade();

    _fadeDuration = fadeDuration;
    _fadeFromValue = _value;
    _fadeToValue = fadeToValue;

    // Figure out what the interval should be so that we're chaning the color by at least 1 each cycle
    // Minimum fade interval is FADE_DURATION_MIN
    float fadeDiff = abs(_value - _fadeToValue);

    if (fadeDiff == 0.0f) // division by ZERO protection
        fadeDiff = 1.0f;

    _fadeInterval = round(static_cast<float>(fadeDuration) / fadeDiff);

    if (_fadeInterval < FADE_DURATION_MIN)
        _fadeInterval = FADE_DURATION_MIN;

    _fadeLastStepTime = millis();
};

void DimmerEx::stopFade()
{
    _fadeDuration = DimmerEx::FADE_DURATION_OFF;
}

byte DimmerEx::getFadeProgress() const
{
    // check if fading is in progress
    if (isFading())
        return map(_value, _fadeFromValue, _fadeToValue, DimmerEx::VALUE_MIN, DimmerEx::VALUE_MAX);
    else
        return DimmerEx::VALUE_MAX; // just return 100 % (fading done)
}

// function has to be called in every processor tick
// it is used to non-blocking lights up / down fade effect
void DimmerEx::update()
{
    // no fade - so here is nothing to do
    if (!isFading())
        return;

    unsigned long timeDiff = millis() - _fadeLastStepTime;

    // Interval hasn't passed yet
    if (timeDiff < _fadeInterval)
        return;

    // How far along have we gone since last update (0 - 1)
    float percent = static_cast<float>(timeDiff) / static_cast<float>(_fadeDuration);

    // We've hit 100 % (percent == 1), set lights level to the final value
    if (percent >= 1)
    {
        stopFade();
        setValue(_fadeToValue);
        return;
    }

    // change _value to where it should be
    float fadeDiff = _fadeToValue - _value;
    int increment = round(fadeDiff * percent);

    setValue(_value + increment);

    // Update time and finish
    _fadeDuration -= timeDiff;
    _fadeLastStepTime = millis();

    return;
}

void DimmerEx::setMySensorId(byte value)
{
    _mySensorId = value;
};

byte DimmerEx::getMySensorId() const
{
    return _mySensorId;
};