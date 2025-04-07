/*
 Name:		Statistics.cpp
 Created:	11/19/2019 8:34:27 PM
 Author:	Eltonio
 Editor:	http://www.visualmicro.com
*/

#include "Statistics.h"

// z trudem wystrugana klaska.. - todo: zrob klase bazowa dla EC i PH a moze tez CO2 i Turbidity?
namespace Statistics
{
    float getMediana(uint16_t* readings, byte probesCount, byte dropProbesCount)
    {
        int temporaryReading = 0;

        // Sort measures
        for (int i = 0; i < probesCount - 1; ++i)
        {
            for (int j = i + 1; j < probesCount; ++j)
            {
                if (readings[i] > readings[j])
                {
                    temporaryReading = readings[i];
                    readings[i] = readings[j];
                    readings[j] = temporaryReading;
                }
            }
        }

        // Calculate average measures sum, excluding extremity probes to drop variable
        float avgValue = 0.f;
        for (int i = dropProbesCount; i < probesCount - dropProbesCount; ++i)
        {
            avgValue += readings[i];
        }

        // Corrected average
        return avgValue / (probesCount - (2 * dropProbesCount));
    }

    float getPinMedianaReadingWaspmote(byte pin, uint16_t* readings, byte probesCount) // from https://github.com/Libelium/waspmoteapi
    {
        // Initilize temporary outpt buffer
        uint16_t outputBuffer[50] = { 0 };

        // Get measures
        for (int i = 0; i < probesCount; ++i)
        {
            analogRead(pin); // Dummy analogRead() call (solution taken from some Arduino forum thread..)
            readings[i] = analogRead(pin);
        }

        // Reset all readings
        for (int probeIndex = 0; probeIndex < probesCount; ++probeIndex)
        {
            outputBuffer[probeIndex] = -10000;
        }

        // Set only first reading from the input buffer
        outputBuffer[0] = readings[0];

        // Ordering of the sensor from lower to higher value
        for (int probeIndexInput = 1; probeIndexInput < probesCount; ++probeIndexInput)
        {
            for (int probeIndexOutput = 0; probeIndexOutput < probeIndexInput + 1; ++probeIndexOutput)
            {
                if (readings[probeIndexInput] > outputBuffer[probeIndexOutput])
                {
                    for (int index = probesCount - 1; index > probeIndexOutput; --index)
                    {
                        outputBuffer[index] = outputBuffer[index - 1];
                    }

                    outputBuffer[probeIndexOutput] = readings[probeIndexInput];
                    probeIndexOutput = probeIndexInput + 1;

                    continue;
                }
            }
        }

        // The value in the central position of the array is returned
        return outputBuffer[static_cast<int>(probesCount / 2)];
    }

    float getStandardDeviation(uint16_t* readings, byte probesCount)
    {
        // Calculate analog pin RAW readings Average & Standard Deviation
        float dataSum = 0.0f;
        float diffSum = 0.0f;

        for (int i = 0; i < probesCount; ++i)
        {
            dataSum += readings[i];
        }

        float averagedReading = dataSum / probesCount;

        for (int i = 0; i < probesCount; ++i)
        {
            diffSum += ((readings[i] - averagedReading) * (readings[i] - averagedReading));
        }

        float variance = diffSum / (probesCount - 1);
        float standardDeviation = sqrt(variance);

        // Recalculate Corrected Average only using data within range +/- 2 standard deviations of RAW Average
        if (standardDeviation != 0) // Avoid divide by zero error if standardDeviation == 0
        {
            float newSum = 0.0f; // Sum of readings within acceptable range
            float newLen = 0.0f; // Number of readings within acceptable range

            for (int i = 0; i < probesCount; ++i)
            {
                if ((readings[i] < (averagedReading + (standardDeviation * 1))) && (readings[i] > (averagedReading - (standardDeviation * 1))))
                {
                    newSum += readings[i];
                    ++newLen;
                }
            }

            averagedReading = newSum / newLen; // Corrected Average
        }

        return averagedReading;
    }

    float getResistance(float measure)
    {
        float resistance = 0.0f;

        if (measure <= 11.f)
        {
            resistance = measure / 0.050f;
        }
        else if ((measure > 11.f) && (measure <= 23.f))
        {
            resistance = ((measure - 0.44f) / 0.0480f);
        }
        else if ((measure > 23.f) && (measure <= 47.f))
        {
            resistance = ((measure - 1.7170f) / 0.0453f);
        }
        else if ((measure > 47.f) && (measure <= 94.f))
        {
            resistance = ((measure - 7.8333f) / 0.0392f);
        }
        else if ((measure > 94.f) && (measure <= 162.f))
        {
            resistance = ((measure - 34.16f) / 0.0272f);
        }
        else if ((measure > 162.f) && (measure <= 186.f))
        {
            resistance = ((measure - 36.667f) / 0.0267f);
        }
        else if ((measure > 186.f) && (measure <= 259.f))
        {
            resistance = ((measure - 93.0909f) / 0.0161f);
        }
        else if ((measure > 259.f) && (measure <= 310.f))
        {
            resistance = ((measure - 157.0f) / 0.0102f);
        }
        else if ((measure > 310.f) && (measure <= 358.f))
        {
            resistance = ((measure - 207.1429f) / 0.0069f);
        }
        else if ((measure > 358.f) && (measure <= 401.f))
        {
            resistance = ((measure - 272.0f) / 0.0039f);
        }
        else if ((measure > 401.f) && (measure <= 432.f))
        {
            resistance = ((measure - 327.9286f) / 0.0022f);
        }
        else if ((measure > 432.f) && (measure <= 458.f))
        {
            resistance = ((measure - 373.8095f) / 0.0012f);
        }
        else if ((measure > 458.f) && (measure <= 479.f))
        {
            resistance = ((measure - 413.3750f) / 0.0007f);
        }
        else if ((measure > 479.f) && (measure <= 525.f))
        {
            resistance = ((measure - 473.8889f) / 0.0001f);
        }
        else if ((measure > 525.f))
        {
            resistance = ((measure - 525.7778f) / 0.00001f);
        }

        return resistance;
    }

    float getVoltage(int measure, float adcResolution, float adcReferenceVoltage)
    {
        return adcReferenceVoltage / adcResolution * measure;
    }

    float resistanceToConductivity(float resistance, float temperature, float ecPointLow, float resistancePointLow, float ecPointHigh, float resistancePointHigh, float temperatureCalibrationPoint)
    {
        // Calculates the cell factor of the conductivity sensor and the offset from the calibration values
        float cellFactor = ecPointLow * ecPointHigh * ((resistancePointLow - resistancePointHigh) / (ecPointHigh - ecPointLow));
        float offset = (ecPointLow * resistancePointLow - ecPointHigh * resistancePointHigh) / (ecPointHigh - ecPointLow);

        // Converts the resistance of the sensor into a conductivity value
        float electroConductivity = cellFactor * 1.f / (resistance + offset);

        // Calculate temperature coefficient factor
        float tempCoefficient = 1.f + 0.0185f * (temperature - temperatureCalibrationPoint);

        // Correct conductivity by temperature coefficient factor
        electroConductivity /= tempCoefficient;

        // Return results
        return electroConductivity;
    }
}
