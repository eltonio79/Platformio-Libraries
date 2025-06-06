#pragma once

#include "AudioTools/AudioTypes.h"
#include "Print.h"
#include "opus.h"

#ifndef OPUS_MAX_BUFFER_SIZE
#define OPUS_MAX_BUFFER_SIZE (5760)
#endif

namespace audio_tools {

/**
 * @brief Setting for Opus Decoder
 * @author Phil Schatzmann
 * @copyright GPLv3
 */
struct OpusSettings : public AudioBaseInfo {
  OpusSettings() {
    /// 8000,12000,16000 ,24000,48000
    sample_rate = 48000;
    /// 1 or 2
    channels = 2;
    /// must be 16!
    bits_per_sample = 16;
  }
  int max_buffer_size = OPUS_MAX_BUFFER_SIZE;
};

/**
 * @brief Setting for Opus Encoder where the following values are valid:
 * -1 indicates that the default value should be used and that this codec is not
setting the value.
 *
  int channels[2] = {1, 2};<br>
  int applications[3] = {OPUS_APPLICATION_AUDIO, OPUS_APPLICATION_VOIP,
                         OPUS_APPLICATION_RESTRICTED_LOWDELAY};<br>

  int sample_rates[] = {8000,12000,16000 ,24000,48000}<br>

  int bitrates[11] = {6000,  12000, 16000,  24000,     32000,           48000,
                      64000, 96000, 510000, OPUS_AUTO, OPUS_BITRATE_MAX};<br>
  int force_channels[4] = {OPUS_AUTO, OPUS_AUTO, 1, 2};<br>
  int use_vbr[3] = {0, 1, 1};<br>
  int vbr_constraints[3] = {0, 1, 1};<br>
  int complexities[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};<br>
  int max_bandwidths[6] = {
      OPUS_BANDWIDTH_NARROWBAND, OPUS_BANDWIDTH_MEDIUMBAND,
      OPUS_BANDWIDTH_WIDEBAND,   OPUS_BANDWIDTH_SUPERWIDEBAND,
      OPUS_BANDWIDTH_FULLBAND,   OPUS_BANDWIDTH_FULLBAND};<br>

  int signals[4] = {OPUS_AUTO, OPUS_AUTO, OPUS_SIGNAL_VOICE,
OPUS_SIGNAL_MUSIC};<br> int inband_fecs[3] = {0, 0, 1};<br> int
packet_loss_perc[4] = {0, 1, 2, 5};<br> int lsb_depths[2] = {8, 24};<br> int
prediction_disabled[3] = {0, 0, 1};<br> int use_dtx[2] = {0, 1};<br> int
frame_sizes_ms_x2[9] = {5,   10,  20,  40, 80, 120, 160, 200, 240}; /* x2 to
avoid 2.5 ms <br>
 * @author Phil Schatzmann
 * @copyright GPLv3
**/

struct OpusEncoderSettings : public OpusSettings {
  OpusEncoderSettings() : OpusSettings() {}
  /// Default is 5760
  int max_buffer_size = OPUS_MAX_BUFFER_SIZE;
  /// OPUS_APPLICATION_AUDIO, OPUS_APPLICATION_VOIP,
  /// OPUS_APPLICATION_RESTRICTED_LOWDELAY
  int application = OPUS_APPLICATION_AUDIO;
  /// 6000,  12000, 16000,  24000, 32000, 48000,  64000, 96000, 510000,
  /// OPUS_AUTO, OPUS_BITRATE_MAX
  int bitrate = -1;
  /// OPUS_AUTO, OPUS_AUTO, 1, 2
  int force_channel = -1;
  /// 0, 1
  int vbr = -1;
  /// 0, 1
  int vbr_constraint = -1;
  /// 0 to 10
  int complexity = -1;
  /// OPUS_BANDWIDTH_NARROWBAND,
  /// OPUS_BANDWIDTH_MEDIUMBAND,OPUS_BANDWIDTH_WIDEBAND,
  /// OPUS_BANDWIDTH_SUPERWIDEBAND, OPUS_BANDWIDTH_FULLBAND,
  /// OPUS_BANDWIDTH_FULLBAND
  int max_bandwidth = -1;
  /// OPUS_AUTO, OPUS_AUTO, OPUS_SIGNAL_VOICE, OPUS_SIGNAL_MUSIC
  int singal = -1;
  ///  0, 1
  int inband_fec = -1;
  /// 0, 1, 2, 5
  int packet_loss_perc = -1;
  /// 8, 24
  int lsb_depth = -1;
  /// 0, 1
  int prediction_disabled = -1;
  /// 0, 1
  int use_dtx = -1;
  /// 5,   10,  20,  40, 80, 120, 160, 200, 240
  int frame_sizes_ms_x2 = -1; /* x2 to avoid 2.5 ms */
};

/**
 * @brief OpusDecoder
 * @author Phil Schatzmann
 * @copyright GPLv3
 */
class OpusAudioDecoder : public AudioDecoder {
 public:
  /**
   * @brief Construct a new OpusDecoder object
   */
  OpusAudioDecoder() { LOGD(LOG_METHOD); }

  /**
   * @brief Construct a new OpusDecoder object
   *
   * @param out_stream Output Stream to which we write the decoded result
   */
  OpusAudioDecoder(Print &out_stream) {
    LOGD(LOG_METHOD);
    setOutputStream(out_stream);
  }

  /// Defines the output Stream
  void setOutputStream(Print &out_stream) override { p_print = &out_stream; }

  void setNotifyAudioChange(AudioBaseInfoDependent &bi) override {
    this->bid = &bi;
  }

  AudioBaseInfo audioInfo() override { return cfg; }

  /// Provides access to the configuration
  OpusSettings &config() { return cfg; }

  void begin(OpusSettings info) {
    LOGD(LOG_METHOD);
    cfg = info;
    if (bid != nullptr) {
      bid->setAudioInfo(cfg);
    }
    begin();
  }

  void begin() override {
    LOGD(LOG_METHOD);
    outbuf.resize(cfg.max_buffer_size);
    int err;
    dec = opus_decoder_create(cfg.sample_rate, cfg.channels, &err);
    if (err != OPUS_OK) {
      LOGE("opus_decoder_create: %s for sample_rate: %d, channels:%d",
           opus_strerror(err), cfg.sample_rate, cfg.channels);
      return;
    }
    active = true;
  }

  void end() override {
    LOGD(LOG_METHOD);
    if (dec) {
      opus_decoder_destroy(dec);
      dec = nullptr;
    }
    active = false;
  }

  void setAudioInfo(AudioBaseInfo from) override {
    cfg.sample_rate = from.sample_rate;
    cfg.channels = from.channels;
    cfg.bits_per_sample = from.bits_per_sample;
  }

  size_t write(const void *in_ptr, size_t in_size) {
    if (!active || p_print == nullptr) return 0;
    // decode data
    LOGD("opus_decode - bytes: %d", in_size);
    int in_band_forware_error_correction = 0;
    int out_samples = opus_decode(
        dec, (uint8_t *)in_ptr, in_size, (opus_int16 *)outbuf.data(),
        cfg.max_buffer_size, in_band_forware_error_correction);
    if (out_samples < 0) {
      LOGE("opus_decode: %s", opus_strerror(out_samples));
    } else if (out_samples > 0) {
      // convert to little endian

      // write data to final destination
      int out_bytes = out_samples * cfg.channels * sizeof(int16_t);
      p_print->write(outbuf.data(), out_bytes);
    }
    return in_size;
  }

  operator boolean() override { return active; }

 protected:
  Print *p_print = nullptr;
  AudioBaseInfoDependent *bid = nullptr;
  OpusSettings cfg;
  ::OpusDecoder *dec;
  bool active;
  Vector<uint8_t> outbuf;
};

/**
 * @brief OpusDecoder - Actually this class does no encoding or decoding at
 * all. It just passes on the data.
 * @author Phil Schatzmann
 * @copyright GPLv3
 */
class OpusAudioEncoder : public AudioEncoder {
 public:
  // Empty Constructor - the output stream must be provided with begin()
  OpusAudioEncoder() {}

  // Constructor providing the output stream
  OpusAudioEncoder(Print &out) { setOutputStream(out); }

  /// Defines the output Stream
  void setOutputStream(Print &out_stream) override { p_print = &out_stream; }

  /// Provides "audio/pcm"
  const char *mime() { return "audio/opus"; }

  /// We actually do nothing with this
  void setAudioInfo(AudioBaseInfo from) override {
    cfg.sample_rate = from.sample_rate;
    cfg.channels = from.channels;
    cfg.bits_per_sample = from.bits_per_sample;
  }

  /// starts the processing using the actual OpusAudioInfo
  void begin() override {
    int err;
    packet.resize(cfg.max_buffer_size);
    frame.resize(getFrameSizeSamples(cfg.sample_rate) * 2);
    assert(frame.data() != nullptr);
    assert(packet.data() != nullptr);

    enc = opus_encoder_create(cfg.sample_rate, cfg.channels, cfg.application,
                              &err);
    if (err != OPUS_OK) {
      LOGE("opus_encoder_create: %s for sample_rate: %d, channels:%d",
           opus_strerror(err), cfg.sample_rate, cfg.channels);
      return;
    }
    is_open = settings();
  }

  /// Provides access to the configuration
  OpusEncoderSettings &config() { return cfg; }

  void begin(OpusEncoderSettings settings) {
    cfg = settings;
    begin();
  }

  /// stops the processing
  void end() override {
    // flush buffered data
    encodeFrame(frame_pos);
    // release memory
    opus_encoder_destroy(enc);
    is_open = false;
  }

  /// Writes PCM data to be encoded as Opus
  size_t write(const void *in_ptr, size_t in_size) {
    if (!is_open || p_print == nullptr) return 0;

    uint8_t *p_byte = (uint8_t *)in_ptr;
    for (int j = 0; j < in_size; j++) {
      encodeByte(p_byte[j]);
    }
    return in_size;
  }

  operator boolean() override { return is_open; }

  bool isOpen() { return is_open; }

 protected:
  Print *p_print = nullptr;
  ::OpusEncoder *enc = nullptr;
  OpusEncoderSettings cfg;
  bool is_open = false;
  Vector<uint8_t> packet;
  Vector<uint8_t> frame;
  int frame_pos = 0;

  void encodeByte(uint8_t data) {
    // add byte to frame
    frame[frame_pos++] = data;

    // if frame is complete -> encode
    int frame_size = frame.size();
    if (frame_pos >= frame_size) {
      encodeFrame(frame_size);
      frame_pos = 0;
    }
  }

  void encodeFrame(int lenBytes) {
    if (lenBytes > 0) {
      int frames = lenBytes / cfg.channels / sizeof(int16_t);
      LOGD("opus_encode - frame_size: %d", frames);
      int len = opus_encode(enc, (opus_int16 *)frame.data(), frames,
                            packet.data(), cfg.max_buffer_size);
      if (len < 0) {
        LOGE("opus_encode: %s", opus_strerror(len));
      } else if (len > 0 && len <= cfg.max_buffer_size) {
        p_print->write(packet.data(), len);
      }
    }
  }

  /// Returns the frame size in samples
  int getFrameSizeSamples(int sampling_rate) {
    switch (cfg.frame_sizes_ms_x2) {
      case OPUS_FRAMESIZE_2_5_MS:
        return sampling_rate / 400;
      case OPUS_FRAMESIZE_5_MS:
        return sampling_rate / 200;
      case OPUS_FRAMESIZE_10_MS:
        return sampling_rate / 100;
      case OPUS_FRAMESIZE_20_MS:
        return sampling_rate / 50;
      case OPUS_FRAMESIZE_40_MS:
        return sampling_rate / 25;
      case OPUS_FRAMESIZE_60_MS:
        return 3 * sampling_rate / 50;
      case OPUS_FRAMESIZE_80_MS:
        return 4 * sampling_rate / 50;
      case OPUS_FRAMESIZE_100_MS:
        return 5 * sampling_rate / 50;
      case OPUS_FRAMESIZE_120_MS:
        return 6 * sampling_rate / 50;
    }
    return sampling_rate / 100;
  }

  bool settings() {
    bool ok = true;
    if (cfg.bitrate >= 0 &&
        opus_encoder_ctl(enc, OPUS_SET_BITRATE(cfg.bitrate)) != OPUS_OK) {
      LOGE("invalid bitrate: %d", cfg.bitrate);
      ok = false;
    }
    if (cfg.force_channel >= 0 &&
        opus_encoder_ctl(enc, OPUS_SET_FORCE_CHANNELS(cfg.force_channel)) !=
            OPUS_OK) {
      LOGE("invalid force_channel: %d", cfg.force_channel);
      ok = false;
    };
    if (cfg.vbr >= 0 &&
        opus_encoder_ctl(enc, OPUS_SET_VBR(cfg.vbr)) != OPUS_OK) {
      LOGE("invalid vbr: %d", cfg.vbr);
      ok = false;
    }
    if (cfg.vbr_constraint >= 0 &&
        opus_encoder_ctl(enc, OPUS_SET_VBR_CONSTRAINT(cfg.vbr_constraint)) !=
            OPUS_OK) {
      LOGE("invalid vbr_constraint: %d", cfg.vbr_constraint);
      ok = false;
    }
    if (cfg.complexity >= 0 &&
        opus_encoder_ctl(enc, OPUS_SET_COMPLEXITY(cfg.complexity)) != OPUS_OK) {
      LOGE("invalid complexity: %d", cfg.complexity);
      ok = false;
    }
    if (cfg.max_bandwidth >= 0 &&
        opus_encoder_ctl(enc, OPUS_SET_MAX_BANDWIDTH(cfg.max_bandwidth)) !=
            OPUS_OK) {
      LOGE("invalid max_bandwidth: %d", cfg.max_bandwidth);
      ok = false;
    }
    if (cfg.singal >= 0 &&
        opus_encoder_ctl(enc, OPUS_SET_SIGNAL(cfg.singal)) != OPUS_OK) {
      LOGE("invalid singal: %d", cfg.singal);
      ok = false;
    }
    if (cfg.inband_fec >= 0 &&
        opus_encoder_ctl(enc, OPUS_SET_INBAND_FEC(cfg.inband_fec)) != OPUS_OK) {
      LOGE("invalid inband_fec: %d", cfg.inband_fec);
      ok = false;
    }
    if (cfg.packet_loss_perc >= 0 &&
        opus_encoder_ctl(
            enc, OPUS_SET_PACKET_LOSS_PERC(cfg.packet_loss_perc)) != OPUS_OK) {
      LOGE("invalid pkt_loss: %d", cfg.packet_loss_perc);
      ok = false;
    }
    if (cfg.lsb_depth >= 0 &&
        opus_encoder_ctl(enc, OPUS_SET_LSB_DEPTH(cfg.lsb_depth)) != OPUS_OK) {
      LOGE("invalid lsb_depth: %d", cfg.lsb_depth);
      ok = false;
    }
    if (cfg.prediction_disabled >= 0 &&
        opus_encoder_ctl(enc, OPUS_SET_PREDICTION_DISABLED(
                                  cfg.prediction_disabled)) != OPUS_OK) {
      LOGE("invalid pred_disabled: %d", cfg.prediction_disabled);
      ok = false;
    }
    if (cfg.use_dtx >= 0 &&
        opus_encoder_ctl(enc, OPUS_SET_DTX(cfg.use_dtx)) != OPUS_OK) {
      LOGE("invalid use_dtx: %d", cfg.use_dtx);
      ok = false;
    }
    if (cfg.frame_sizes_ms_x2 > 0 &&
        opus_encoder_ctl(enc, OPUS_SET_EXPERT_FRAME_DURATION(
                                  cfg.frame_sizes_ms_x2)) != OPUS_OK) {
      LOGE("invalid frame_sizes_ms_x2: %d", cfg.frame_sizes_ms_x2);
      ok = false;
    }
    return ok;
  }
};

}  // namespace audio_tools