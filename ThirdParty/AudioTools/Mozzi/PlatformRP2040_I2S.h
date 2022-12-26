/*
 * PlatformRP2040.h
 * 
 * I2S Mozzi Support for the Rasperry Pico for the Arduino Kernels which provide the full Rasperry Pico API
 * ATTENTION: The standard Arduino implementation uses the ARM Mbed! So this would be the wrong place
  
 * Copyright 2021 Phil Schatzmann.
 * 
 * This file is part of Mozzi.
 *
 * Mozzi by Tim Barrass is licensed under a Creative Commons
 * Attribution-NonCommercial-ShareAlike 4.0 International License.
 *
 */


#pragma once
#include "hardware_and_config.h"

#if IS_RP2040() 

#include "PlatformCommon.h"
#include "AudioConfigRP2040.h"
#include <I2S.h>

/**
* @brief  Hardware specific implementation class for the Raspberry Pico API - Please note that the standard Arduino implementation is based on MBed and does not
* use this implementation. The following Default pins are used pinBCLK = 26; pinDOUT = 28; 
*/

class PlatformRP2040_I2S : public PlatformOutput {

  public:

    void setAudioRate(uint16_t rate){
       audio_rate = rate;
    }

    bool setBCLK(pin_size_t pin) {
      return I2S.setBCLK(pin);
    }

    bool setDOUT(pin_size_t pin){
      return I2S.setDOUT(pin);
    }

    void start(int control_rate_hz) {
      started = I2S.begin(audio_rate);
      setupADC();
    }

    void stop() {
      I2S.end();
      started = false;
    }

    static unsigned long audioTicks() {
      return time_us_64() / MICROS_PER_AUDIO_TICK; 
    }

    static unsigned long mozziMicros() { 
      return time_us_64();
    }

    static void audioHook()  {
      #if (USE_AUDIO_INPUT == true) 
        PlatformCommon::updateAudioInput();
      #endif
      PlatformCommon::advanceControlLoop();
      audioOutput(updateAudio());
    }

    const int channels() const {
        return 2;
    }

    bool write(const AudioOutput out){
      if (started){
        audioOutput(out);
      }
      return started;
    }

    bool canWrite(){
       return started && I2S.availableForWrite()>=2;
    }
   

#if USE_AUDIO_INPUT == true

    // Provides the analog value w/o delay
    static int getAudioInput() { 
      return PlatformCommon::getAudioInput();
    }

#endif

  protected:
    uint16_t audio_rate = AUDIO_RATE;
    bool started;
    PlatformCommon Common;

    //-----------------------------------------------------------------------------------------------------------------
    // Input
    //-----------------------------------------------------------------------------------------------------------------

    #if (USE_AUDIO_INPUT == true)

    void setupADC() {
      adc_init();

      // Make sure GPIO is high-impedance, no pullups etc
      adc_gpio_init(AUDIO_INPUT_PIN);
      // Select ADC input 0 (GPIO26)
      adc_select_input(AUDIO_CHANNEL_IN);
    }

    #elif (USE_AUDIO_INPUT == false)

    void setupADC(){ }

    #endif

    static void audioOutput(const AudioOutput value) {
      // blocking I2S write
      I2S.write(value[0]);
      if (AUDIO_CHANNELS==1){
        I2S.write(value[0]);
      } else {
        I2S.write(value[1]);
      }
    }

};


#endif  // IS_RP2040
