#ifndef AUDIOCONFIGTEENSY3_12BIT_H
#define AUDIOCONFIGTEENSY3_12BIT_H
#include "mozzi_config_defines.h"


/** @ingroup core
*/
/* Used internally to put the 0-biased generated audio into the centre of the output range (12 bits on Teensy 3) */
#define AUDIO_BIAS ((uint16_t) 2048)
#define AUDIO_BITS 12

#if !defined(AUDIO_CHANNEL_1_PIN) && defined(__arm__) && defined(CORE_TEENSY)
#if defined(__MKL26Z64__)
#define AUDIO_CHANNEL_1_PIN A12
#elif defined(__MK20DX128__) || defined(__MK20DX256__)
#define AUDIO_CHANNEL_1_PIN A14
#elif defined(__MK64FX512__) || defined(__MK66FX1M0__)
#define AUDIO_CHANNEL_1_PIN A21
#else
#error "Unknown Teensy"
#endif
#endif

// Default ouput implementation class
#define PLATFORM_OUTPUT_CLASS PlatformTeensy3
#define ADC_AVERAGING 16

#endif        //  #ifndef AUDIOCONFIGTEENSY3_12BIT_H

