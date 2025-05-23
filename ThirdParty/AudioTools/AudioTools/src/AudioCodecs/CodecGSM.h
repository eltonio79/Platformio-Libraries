/**
 * @file CodecGSM.h
 * @author Phil Schatzmann
 * @brief GSM Codec using  https://github.com/pschatzmann/arduino-libgsm
 * @version 0.1
 * @date 2022-04-24
 */

#pragma once

#include "AudioTools/AudioTypes.h"
#include "gsm.h"

namespace audio_tools {

/**
 * @brief Decoder for GSM. Depends on
 * https://github.com/pschatzmann/arduino-libgsm.
 * Inspired by gsmdec.c
 * @author Phil Schatzmann
 * @copyright GPLv3
 */
class GSMDecoder : public AudioDecoder {
 public:
  GSMDecoder() {
    cfg.sample_rate = 8000;
    cfg.channels = 1;
  }

  virtual void setAudioInfo(AudioBaseInfo cfg) { this->cfg = cfg; }

  virtual AudioBaseInfo audioInfo() { return cfg; }

  virtual void begin(AudioBaseInfo cfg) {
    setAudioInfo(cfg);
    begin();
  }

  virtual void begin() {
    LOGI(LOG_METHOD);
    // 160 13-bit samples
    result_buffer.resize(160 * sizeof(int16_t));
    // gsm_frame of 33 bytes
    input_buffer.resize(33);

    v_gsm = gsm_create();
    if (p_notify!=nullptr){
      p_notify->setAudioInfo(cfg);
    }
    is_active = true;
  }

  virtual void end() {
    LOGI(LOG_METHOD);
    gsm_destroy(v_gsm);
    is_active = false;
  }

  virtual void setNotifyAudioChange(AudioBaseInfoDependent &bi) {
    p_notify = &bi;
  }

  virtual void setOutputStream(Print &out_stream) { p_print = &out_stream; }

  operator boolean() { return is_active; }

  virtual size_t write(const void *data, size_t length) {
    LOGD("write: %d", length);
    if (!is_active) {
      LOGE("inactive");
      return 0;
    }

    uint8_t *p_byte = (uint8_t *) data;
    for (int j = 0; j < length; j++) {
      processByte(p_byte[j]);
    }

    return length;
  }

 protected:
  Print *p_print = nullptr;
  gsm v_gsm;
  AudioBaseInfo cfg;
  AudioBaseInfoDependent *p_notify = nullptr;
  bool is_active = false;
  Vector<uint8_t> input_buffer;
  Vector<uint8_t> result_buffer;
  int input_pos = 0;

  /// Build decoding buffer and decode when frame is full
  void processByte(uint8_t byte) {
    // add byte to buffer
    input_buffer[input_pos++] = byte;

    // decode if buffer is full
    if (input_pos >= input_buffer.size()) {
      if (gsm_decode(v_gsm, input_buffer.data(), (gsm_signal*)result_buffer.data())!=0){
        LOGE("gsm_decode");
      }

      // scale to 13 to 16-bit samples
      int16_t *pt16 = (int16_t *)input_buffer.data();
      for (int j = 0; j < input_buffer.size() / 2; j++) {
        pt16[j] = pt16[j] * 8;
      }

      p_print->write(result_buffer.data(), result_buffer.size());
      input_pos = 0;
    }
  }
};

/**
 * @brief Encoder for GSM - Depends on
 * https://github.com/pschatzmann/arduino-libgsm.
 * Inspired by gsmenc.c
 * @author Phil Schatzmann
 * @copyright GPLv3
 */
class GSMEncoder : public AudioEncoder {
 public:
  GSMEncoder() {
    cfg.sample_rate = 8000;
    cfg.channels = 1;
  }

  void begin(AudioBaseInfo bi) {
    setAudioInfo(bi);
    begin();
  }

  void begin() {
    LOGI(LOG_METHOD);

    if (cfg.sample_rate != 8000) {
      LOGW("Sample rate is supposed to be 8000 - it was %d", cfg.sample_rate);
    }
    if (cfg.channels != 1) {
      LOGW("channels is supposed to be 1 - it was %d", cfg.channels);
    }

    v_gsm = gsm_create();
    // 160 13-bit samples
    input_buffer.resize(160 * sizeof(int16_t));
    // gsm_frame of 33 bytes
    result_buffer.resize(33);
    is_active = true;
  }

  virtual void end() {
    LOGI(LOG_METHOD);
    gsm_destroy(v_gsm);
    is_active = false;
  }

  virtual const char *mime() { return "audio/gsm"; }

  virtual void setAudioInfo(AudioBaseInfo cfg) { this->cfg = cfg; }

  virtual void setOutputStream(Print &out_stream) { p_print = &out_stream; }

  operator boolean() { return is_active; }

  virtual size_t write(const void *in_ptr, size_t in_size) {
    LOGD("write: %d", in_size);
    if (!is_active) {
      LOGE("inactive");
      return 0;
    }
    // encode bytes
    uint8_t *p_byte = (uint8_t *) in_ptr;
    for (int j = 0; j < in_size; j++) {
      processByte(p_byte[j]);
    }
    return in_size;
  }

 protected:
  AudioBaseInfo cfg;
  Print *p_print = nullptr;
  gsm v_gsm;
  bool is_active = false;
  int buffer_pos = 0;
  Vector<uint8_t> input_buffer;
  Vector<uint8_t> result_buffer;

  // add byte to decoding buffer and decode if buffer is full
  void processByte(uint8_t byte) {
    input_buffer[buffer_pos++] = byte;
    if (buffer_pos >= input_buffer.size()) {
      // scale to 16 to 13-bit samples
      int16_t *pt16 = (int16_t *)input_buffer.data();
      for (int j = 0; j < input_buffer.size() / 2; j++) {
        pt16[j] = pt16[j] / 8;
      }
      // encode
      gsm_encode(v_gsm, (gsm_signal*)input_buffer.data(), result_buffer.data());
      p_print->write(result_buffer.data(), result_buffer.size());
      buffer_pos = 0;
    }
  }
};

}  // namespace audio_tools