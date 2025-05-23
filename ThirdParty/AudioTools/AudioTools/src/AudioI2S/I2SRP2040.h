#pragma once

#if defined(ARDUINO_ARCH_RP2040) && !defined(ARDUINO_ARCH_MBED_RP2040)
#include "AudioI2S/I2SConfig.h"
//#include "Experiments/I2SBitBangRP2040.h"
#include <I2S.h>
namespace audio_tools {

class I2SBasePIO;
#if USE_I2S==2
typedef RP2040BitBangI2SCore1 I2SBase;
#elif USE_I2S==3
typedef RP2040BitBangI2SWithInterrupts I2SBase;
#else
typedef I2SBasePIO I2SBase;
#endif


/**
 * @brief Basic I2S API - for the ...
 * @author Phil Schatzmann
 * @copyright GPLv3
 */
class I2SBasePIO {
  friend class I2SStream;

  public:

    /// Provides the default configuration
    I2SConfig defaultConfig(RxTxMode mode) {
        I2SConfig c(mode);
        return c;
    }

    /// starts the DAC with the default config in TX Mode
    bool begin(RxTxMode mode = TX_MODE)  {
      LOGD(LOG_METHOD);
      return begin(defaultConfig(mode));
    }

    /// starts the DAC 
    bool begin(I2SConfig cfg) {
      LOGI(LOG_METHOD);
      cfg.logInfo();
      if (cfg.rx_tx_mode != TX_MODE ){
          LOGE("Unsupported mode: only TX_MODE is supported");
          return false;
      }
      if (!I2S.setBCLK(cfg.pin_bck)){
          LOGE("Could not set bck pin: %d", cfg.pin_bck);
          return false;
      }
      if (!I2S.setDOUT(cfg.pin_data)){
          LOGE("Could not set data pin: %d", cfg.pin_data);
          return false;
      }
      if (cfg.bits_per_sample != 16){
          LOGE("Unsupported bits_per_sample: %d", cfg.bits_per_sample);
          return false;
      }

      if (cfg.channels < 1 || cfg.channels > 2 ){
          LOGE("Unsupported channels: '%d' - only 2 is supported", cfg.channels);
          return false;
      }

      int rate = cfg.sample_rate; 
      if (cfg.channels==1){
        rate = rate /2;
      } 

      if (!I2S.begin(rate)){
          LOGE("Could not start I2S");
          return false;
      }
      return true;
    }

    /// stops the I2C and unistalls the driver
    void end()  {
      I2S.end();
    }

    /// provides the actual configuration
    I2SConfig config() {
      return cfg;
    }

    /// writes the data to the I2S interface 
    size_t writeBytes(const void *src, size_t size_bytes)  {
      LOGD(LOG_METHOD);
      size_t result = 0;
      int16_t *p16 = (int16_t *)src;
      
      if (cfg.channels==1){
        int samples = size_bytes/2;
        // multiply 1 channel into 2
        int16_t buffer[samples*2]; // from 1 byte to 2 bytes
        for (int j=0;j<samples;j++){
          buffer[j*2]= p16[j];
          buffer[j*2+1]= p16[j];
        } 
        result = I2S.write((const uint8_t*)buffer, size_bytes*2)*2;
      } else if (cfg.channels==2){
        result = I2S.write((const uint8_t*)src, size_bytes)*4;
      } 
      return result;
    }

    size_t readBytes(void *dest, size_t size_bytes)  {
      LOGE(LOG_METHOD);
      size_t result = 0;
      return result;
    }

    int availableForWrite()  {
      int result = 0;
      if (cfg.channels == 1){
        // it should be a multiple of 2
        result = I2S.availableForWrite()/2*2;
        // return half of it because we double when writing
        result = result / 2;
      } else {
        // it should be a multiple of 4
        result = I2S.availableForWrite()/4*4;
      } 
      if (result<4){
        result = 0;
      }
      return result;
    }

    int available()  {
      return 0;
    }

    void flush()   {
      return I2S.flush();
    }

  protected:
    I2SConfig cfg;

    // blocking write
    void writeSample(int16_t sample){
        int written = I2S.write(sample);
        while (!written) {
          delay(5);
          LOGW("written: %d ", written);
          written = I2S.write(sample);
        }
    }

    int writeSamples(int samples, int16_t* values){
        int result=0;
        for (int j=0;j<samples;j++){
          int16_t sample = values[j];
          writeSample(sample);
          writeSample(sample);
          result++;
        }
        return result;
    }
    
};

}

#endif
