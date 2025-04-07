/*
 Name:		Statistics.h
 Created:	11/19/2019 8:34:27 PM
 Author:	Eltonio
 Editor:	http://www.visualmicro.com
*/

#ifndef _Statistics_h
#define _Statistics_h

#include "arduino.h"

#define DefaultTemperature 25.f

namespace Statistics
{
    float getMediana(uint16_t* readings, byte probesCount, byte dropProbesCount = 2);
    float getPinMedianaReadingWaspmote(byte pin, uint16_t* readings, byte probesCount);
    float getStandardDeviation(uint16_t* readings, byte probesCount);
    float getResistance(float measure);
    float getVoltage(int measure, float adcResolution, float adcReferenceVoltage);

    // Adjust EC for temperature variations
    // actual resistance
    // calibration value of the solution 1 in µS / cm
    // value measured in resistance with solution 1
    // calibration value of the solution 2 in µS / cm
    // value measured in resistance with solution 2
    // actual temperature
    float resistanceToConductivity(float resistance, float temperature, float ecPointLow, float resistancePointLow, float ecPointHigh, float resistancePointHigh, float temperatureCalibrationPoint = DefaultTemperature);
}

#endif
