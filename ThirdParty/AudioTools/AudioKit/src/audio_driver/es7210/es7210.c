/*
 * ESPRESSIF MIT License
 *
 * Copyright (c) 2021 <ESPRESSIF SYSTEMS (SHANGHAI) CO., LTD>
 *
 * Permission is hereby granted for use on all ESPRESSIF SYSTEMS products, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <string.h>
#include "audio_hal/audiokit_logger.h"
#include "audio_hal/audiokit_board.h"
#include "audio_hal/i2c_bus.h"
#include "es7210.h"

#define  I2S_DSP_MODE   0
#define  MCLK_DIV_FRE   256
#define TAG_ES7210 "ES7210"

/* ES7210 address*/
#define ES7210_ADDR                   ES7210_AD1_AD0_00
#define ES7210_MCLK_SOURCE            FROM_CLOCK_DOUBLE_PIN                            /* In master mode, 0 : MCLK from pad    1 : MCLK from clock doubler */
#define FROM_PAD_PIN                  0
#define FROM_CLOCK_DOUBLE_PIN         1

/*
 * Operate function of ADC
 */
audio_hal_func_t AUDIO_CODEC_ES7210_DEFAULT_HANDLE = {
    .audio_codec_initialize = es7210_adc_init,
    .audio_codec_deinitialize = es7210_adc_deinit,
    .audio_codec_ctrl = es7210_adc_ctrl_state,
    .audio_codec_config_iface = es7210_adc_config_i2s,
    .audio_codec_set_mute = es7210_set_mute,
    .audio_codec_set_volume = es7210_adc_set_volume,
    .audio_hal_lock = NULL,
    .handle = NULL,
};

/*
 * Clock coefficient structer
 */
struct _coeff_div {
    uint32_t mclk;            /* mclk frequency */
    uint32_t lrck;            /* lrck */
    uint8_t  ss_ds;
    uint8_t  adc_div;         /* adcclk divider */
    uint8_t  dll;             /* dll_bypass */
    uint8_t  doubler;         /* doubler enable */
    uint8_t  osr;             /* adc osr */
    uint8_t  mclk_src;        /* select mclk  source */
    uint32_t lrck_h;          /* The high 4 bits of lrck */
    uint32_t lrck_l;          /* The low 8 bits of lrck */
};

static i2c_bus_handle_t i2c_handle;
static es7210_input_mics_t mic_select = ES7210_INPUT_MIC1 | ES7210_INPUT_MIC2;         /* Number of microphones */

/* Codec hifi mclk clock divider coefficients
 *           MEMBER      REG
 *           mclk:       0x03
 *           lrck:       standard
 *           ss_ds:      --
 *           adc_div:    0x02
 *           dll:        0x06
 *           doubler:    0x02
 *           osr:        0x07
 *           mclk_src:   0x03
 *           lrckh:      0x04
 *           lrckl:      0x05
*/
static const struct _coeff_div coeff_div[] = {
    //mclk      lrck    ss_ds adc_div  dll  doubler osr  mclk_src  lrckh   lrckl
    /* 8k */
    {12288000,  8000 ,  0x00,  0x03,  0x01,  0x00,  0x20,  0x00,    0x06,  0x00},
    {16384000,  8000 ,  0x00,  0x04,  0x01,  0x00,  0x20,  0x00,    0x08,  0x00},
    {19200000,  8000 ,  0x00,  0x1e,  0x00,  0x01,  0x28,  0x00,    0x09,  0x60},
    {4096000,   8000 ,  0x00,  0x01,  0x01,  0x00,  0x20,  0x00,    0x02,  0x00},

    /* 11.025k */
    {11289600,  11025,  0x00,  0x02,  0x01,  0x00,  0x20,  0x00,    0x01,  0x00},

    /* 12k */
    {12288000,  12000,  0x00,  0x02,  0x01,  0x00,  0x20,  0x00,    0x04,  0x00},
    {19200000,  12000,  0x00,  0x14,  0x00,  0x01,  0x28,  0x00,    0x06,  0x40},

    /* 16k */
    {4096000,   16000,  0x00,  0x01,  0x01,  0x01,  0x20,  0x00,    0x01,  0x00},
    {19200000,  16000,  0x00,  0x0a,  0x00,  0x00,  0x1e,  0x00,    0x04,  0x80},
    {16384000,  16000,  0x00,  0x02,  0x01,  0x00,  0x20,  0x00,    0x04,  0x00},
    {12288000,  16000,  0x00,  0x03,  0x01,  0x01,  0x20,  0x00,    0x03,  0x00},

    /* 22.05k */
    {11289600,  22050,  0x00,  0x01,  0x01,  0x00,  0x20,  0x00,    0x02,  0x00},

    /* 24k */
    {12288000,  24000,  0x00,  0x01,  0x01,  0x00,  0x20,  0x00,    0x02,  0x00},
    {19200000,  24000,  0x00,  0x0a,  0x00,  0x01,  0x28,  0x00,    0x03,  0x20},

    /* 32k */
    {12288000,  32000,  0x00,  0x03,  0x00,  0x00,  0x20,  0x00,    0x01,  0x80},
    {16384000,  32000,  0x00,  0x01,  0x01,  0x00,  0x20,  0x00,    0x02,  0x00},
    {19200000,  32000,  0x00,  0x05,  0x00,  0x00,  0x1e,  0x00,    0x02,  0x58},

    /* 44.1k */
    {11289600,  44100,  0x00,  0x01,  0x01,  0x01,  0x20,  0x00,    0x01,  0x00},

    /* 48k */
    {12288000,  48000,  0x00,  0x01,  0x01,  0x01,  0x20,  0x00,    0x01,  0x00},
    {19200000,  48000,  0x00,  0x05,  0x00,  0x01,  0x28,  0x00,    0x01,  0x90},

    /* 64k */
    {16384000,  64000,  0x01,  0x01,  0x01,  0x00,  0x20,  0x00,    0x01,  0x00},
    {19200000,  64000,  0x00,  0x05,  0x00,  0x01,  0x1e,  0x00,    0x01,  0x2c},

    /* 88.2k */
    {11289600,  88200,  0x01,  0x01,  0x01,  0x01,  0x20,  0x00,    0x00,  0x80},

    /* 96k */
    {12288000,  96000,  0x01,  0x01,  0x01,  0x01,  0x20,  0x00,    0x00,  0x80},
    {19200000,  96000,  0x01,  0x05,  0x00,  0x01,  0x28,  0x00,    0x00,  0xc8},
};

static esp_err_t es7210_write_reg(uint8_t reg_addr, uint8_t data)
{
    return i2c_bus_write_bytes(i2c_handle, ES7210_ADDR, &reg_addr, sizeof(reg_addr), &data, sizeof(data));
}

static esp_err_t es7210_update_reg_bit(uint8_t reg_addr, uint8_t update_bits, uint8_t data)
{
    uint8_t regv;
    regv = es7210_read_reg(reg_addr);
    regv = (regv & (~update_bits)) | (update_bits & data);
    return es7210_write_reg(reg_addr, regv);
}

static int i2c_init()
{
    int ret = 0;
    i2c_config_t es_i2c_cfg = {
        .mode = I2C_MODE_MASTER,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000,
    };
    ret = get_i2c_pins(I2C_NUM_0, &es_i2c_cfg);
    AUDIO_CHECK(TAG_ES7210, !ret, return ESP_FAIL;, "getting i2c pins error");
    i2c_handle = i2c_bus_create(I2C_NUM_0, &es_i2c_cfg);
    return ret;
}

static int get_coeff(uint32_t mclk, uint32_t lrck)
{
    for (int i = 0; i < (sizeof(coeff_div) / sizeof(coeff_div[0])); i++) {
        if (coeff_div[i].lrck == lrck && coeff_div[i].mclk == mclk)
            return i;
    }
    return -1;
}

int8_t get_es7210_mclk_src(void)
{
    return ES7210_MCLK_SOURCE;
}

int es7210_read_reg(uint8_t reg_addr)
{
    uint8_t data;
    i2c_bus_read_bytes(i2c_handle, ES7210_ADDR, &reg_addr, sizeof(reg_addr), &data, sizeof(data));
    return (int)data;
}

esp_err_t es7210_config_sample(audio_hal_iface_samples_t sample)
{
    uint8_t regv;
    int coeff;
    int sample_fre = 0;
    int mclk_fre = 0;
    esp_err_t ret = ESP_OK;
    switch (sample) {
        case AUDIO_HAL_08K_SAMPLES:
            sample_fre = 8000;
            break;
        case AUDIO_HAL_11K_SAMPLES:
            sample_fre = 11025;
            break;
        case AUDIO_HAL_16K_SAMPLES:
            sample_fre = 16000;
            break;
        case AUDIO_HAL_22K_SAMPLES:
            sample_fre = 22050;
            break;
        case AUDIO_HAL_24K_SAMPLES:
            sample_fre = 24000;
            break;
        case AUDIO_HAL_32K_SAMPLES:
            sample_fre = 32000;
            break;
        case AUDIO_HAL_44K_SAMPLES:
            sample_fre = 44100;
            break;
        case AUDIO_HAL_48K_SAMPLES:
            sample_fre = 48000;
            break;
        default:
            KIT_LOGE( "Unable to configure sample rate %dHz", sample_fre);
            break;
    }
    mclk_fre = sample_fre * MCLK_DIV_FRE;
    coeff = get_coeff(mclk_fre, sample_fre);
    if (coeff < 0) {
        KIT_LOGE( "Unable to configure sample rate %dHz with %dHz MCLK", sample_fre, mclk_fre);
        return ESP_FAIL;
    }
    /* Set clock parammeters */
    if (coeff >= 0) {
        /* Set adc_div & doubler & dll */
        regv = es7210_read_reg(ES7210_MAINCLK_REG02) & 0x00;
        regv |= coeff_div[coeff].adc_div;
        regv |= coeff_div[coeff].doubler << 6;
        regv |= coeff_div[coeff].dll << 7;
        ret |= es7210_write_reg(ES7210_MAINCLK_REG02, regv);
        /* Set osr */
        regv = coeff_div[coeff].osr;
        ret |= es7210_write_reg(ES7210_OSR_REG07, regv);
        /* Set lrck */
        regv = coeff_div[coeff].lrck_h;
        ret |= es7210_write_reg(ES7210_LRCK_DIVH_REG04, regv);
        regv = coeff_div[coeff].lrck_l;
        ret |= es7210_write_reg(ES7210_LRCK_DIVL_REG05, regv);
    }
    return ret;
}

esp_err_t es7210_mic_select(es7210_input_mics_t mic)
{
    esp_err_t ret = ESP_OK;
    mic_select = mic;
    if (mic_select & (ES7210_INPUT_MIC1 | ES7210_INPUT_MIC2 | ES7210_INPUT_MIC3 | ES7210_INPUT_MIC4)) {
        for (int i = 0; i < 4; i++) {
            ret |= es7210_update_reg_bit(ES7210_MIC1_GAIN_REG43 + i, 0x10, 0x00);
        }
        ret |= es7210_write_reg(ES7210_MIC12_POWER_REG4B, 0xff);
        ret |= es7210_write_reg(ES7210_MIC34_POWER_REG4C, 0xff);
        if (mic_select & ES7210_INPUT_MIC1) {
            KIT_LOGI( "Enable ES7210_INPUT_MIC1");
            ret |= es7210_update_reg_bit(ES7210_CLOCK_OFF_REG01, 0x0b, 0x00);
            ret |= es7210_write_reg(ES7210_MIC12_POWER_REG4B, 0x00);
            ret |= es7210_update_reg_bit(ES7210_MIC1_GAIN_REG43, 0x10, 0x10);
        }
        if (mic_select & ES7210_INPUT_MIC2) {
            KIT_LOGI( "Enable ES7210_INPUT_MIC2");
            ret |= es7210_update_reg_bit(ES7210_CLOCK_OFF_REG01, 0x0b, 0x00);
            ret |= es7210_write_reg(ES7210_MIC12_POWER_REG4B, 0x00);
            ret |= es7210_update_reg_bit(ES7210_MIC2_GAIN_REG44, 0x10, 0x10);
        }
        if (mic_select & ES7210_INPUT_MIC3) {
            KIT_LOGI( "Enable ES7210_INPUT_MIC3");
            ret |= es7210_update_reg_bit(ES7210_CLOCK_OFF_REG01, 0x15, 0x00);
            ret |= es7210_write_reg(ES7210_MIC34_POWER_REG4C, 0x00);
            ret |= es7210_update_reg_bit(ES7210_MIC3_GAIN_REG45, 0x10, 0x10);
        }
        if (mic_select & ES7210_INPUT_MIC4) {
            KIT_LOGI( "Enable ES7210_INPUT_MIC4");
            ret |= es7210_update_reg_bit(ES7210_CLOCK_OFF_REG01, 0x15, 0x00);
            ret |= es7210_write_reg(ES7210_MIC34_POWER_REG4C, 0x00);
            ret |= es7210_update_reg_bit(ES7210_MIC4_GAIN_REG46, 0x10, 0x10);
        }
    } else {
        KIT_LOGE( "Microphone selection error");
        return ESP_FAIL;
    }
    return ret;
}

esp_err_t es7210_adc_init(audio_hal_codec_config_t *codec_cfg)
{
    esp_err_t ret = ESP_OK;
    i2c_init();
    ret |= es7210_write_reg(ES7210_RESET_REG00, 0xff);
    ret |= es7210_write_reg(ES7210_RESET_REG00, 0x41);
    ret |= es7210_write_reg(ES7210_CLOCK_OFF_REG01, 0x1f);
    ret |= es7210_write_reg(ES7210_TIME_CONTROL0_REG09, 0x30);      /* Set chip state cycle */
    ret |= es7210_write_reg(ES7210_TIME_CONTROL1_REG0A, 0x30);      /* Set power on state cycle */
    ret |= es7210_write_reg(ES7210_ADC12_HPF2_REG23, 0x2a);         /* Quick setup */
    ret |= es7210_write_reg(ES7210_ADC12_HPF1_REG22, 0x0a);
    ret |= es7210_write_reg(ES7210_ADC34_HPF2_REG20, 0x0a);
    ret |= es7210_write_reg(ES7210_ADC34_HPF1_REG21, 0x2a);
    /* Set master/slave audio interface */
    audio_hal_codec_i2s_iface_t *i2s_cfg = & (codec_cfg->i2s_iface);
    switch (i2s_cfg->mode) {
        case AUDIO_HAL_MODE_MASTER:    /* MASTER MODE */
            KIT_LOGI( "ES7210 in Master mode");
            ret |= es7210_update_reg_bit(ES7210_MODE_CONFIG_REG08, 0x01, 0x01);
            /* Select clock source for internal mclk */
            switch (get_es7210_mclk_src()) {
                case FROM_PAD_PIN:
                    ret |= es7210_update_reg_bit(ES7210_MASTER_CLK_REG03, 0x80, 0x00);
                    break;
                case FROM_CLOCK_DOUBLE_PIN:
                    ret |= es7210_update_reg_bit(ES7210_MASTER_CLK_REG03, 0x80, 0x80);
                    break;
                default:
                    ret |= es7210_update_reg_bit(ES7210_MASTER_CLK_REG03, 0x80, 0x00);
                    break;
            }
            break;
        case AUDIO_HAL_MODE_SLAVE:    /* SLAVE MODE */
            KIT_LOGI( "ES7210 in Slave mode");
            ret |= es7210_update_reg_bit(ES7210_MODE_CONFIG_REG08, 0x01, 0x00);
            break;
        default:
            ret |= es7210_update_reg_bit(ES7210_MODE_CONFIG_REG08, 0x01, 0x00);
    }
    ret |= es7210_write_reg(ES7210_ANALOG_REG40, 0x43);               /* Select power off analog, vdda = 3.3V, close vx20ff, VMID select 5KΩ start */
    ret |= es7210_write_reg(ES7210_MIC12_BIAS_REG41, 0x70);           /* Select 2.87v */
    ret |= es7210_write_reg(ES7210_MIC34_BIAS_REG42, 0x70);           /* Select 2.87v */
    ret |= es7210_write_reg(ES7210_OSR_REG07, 0x20);
    ret |= es7210_write_reg(ES7210_MAINCLK_REG02, 0xc1);              /* Set the frequency division coefficient and use dll except clock doubler, and need to set 0xc1 to clear the state */
    ret |= es7210_config_sample(i2s_cfg->samples);
    ret |= es7210_mic_select(mic_select);
    ret |= es7210_adc_set_gain(GAIN_30DB);
    return ESP_OK;
}

esp_err_t es7210_adc_deinit()
{
    i2c_bus_delete(i2c_handle);
    return ESP_OK;
}

esp_err_t es7210_config_fmt(audio_hal_iface_format_t fmt)
{
    esp_err_t ret = ESP_OK;
    uint8_t adc_iface = 0;
    adc_iface = es7210_read_reg(ES7210_SDP_INTERFACE1_REG11);
    adc_iface &= 0xfc;
    switch (fmt) {
        case AUDIO_HAL_I2S_NORMAL:
            KIT_LOGD( "ES7210 in I2S Format");
            adc_iface |= 0x00;
            break;
        case AUDIO_HAL_I2S_LEFT:
        case AUDIO_HAL_I2S_RIGHT:
            KIT_LOGD( "ES7210 in LJ Format");
            adc_iface |= 0x01;
            break;
        case AUDIO_HAL_I2S_DSP:
            if (I2S_DSP_MODE) {
                KIT_LOGD( "ES7210 in DSP-A Format");
                adc_iface |= 0x13;
            } else {
                KIT_LOGD( "ES7210 in DSP-B Format");
                adc_iface |= 0x03;
            }
            break;
        default:
            adc_iface &= 0xfc;
            break;
    }
    ret |= es7210_write_reg(ES7210_SDP_INTERFACE1_REG11, adc_iface);
    return ret;
}

esp_err_t es7210_set_bits(audio_hal_iface_bits_t bits)
{
    esp_err_t ret = ESP_OK;
    uint8_t adc_iface = 0;
    adc_iface = es7210_read_reg(ES7210_SDP_INTERFACE1_REG11);
    adc_iface &= 0x1f;
    switch (bits) {
        case AUDIO_HAL_BIT_LENGTH_16BITS:
            adc_iface |= 0x60;
            break;
        case AUDIO_HAL_BIT_LENGTH_24BITS:
            adc_iface |= 0x00;
            break;
        case AUDIO_HAL_BIT_LENGTH_32BITS:
            adc_iface |= 0x80;
            break;
        default:
            adc_iface |= 0x60;
            break;
    }
    ret |= es7210_write_reg(ES7210_SDP_INTERFACE1_REG11, adc_iface);
    return ret;
}

esp_err_t es7210_adc_config_i2s(audio_hal_codec_mode_t mode, audio_hal_codec_i2s_iface_t *iface)
{
    esp_err_t ret = ESP_OK;
    ret |= es7210_set_bits(iface->bits);
    ret |= es7210_config_fmt(iface->fmt);
    ret |= es7210_config_sample(iface->samples);
    return ret;
}

esp_err_t es7210_start(uint8_t clock_reg_value)
{
    esp_err_t ret = ESP_OK;
    ret |= es7210_write_reg(ES7210_CLOCK_OFF_REG01, clock_reg_value);
    ret |= es7210_write_reg(ES7210_POWER_DOWN_REG06, 0x00);
    ret |= es7210_write_reg(ES7210_ANALOG_REG40, 0x43);
    ret |= es7210_write_reg(ES7210_MIC1_POWER_REG47, 0x00);
    ret |= es7210_write_reg(ES7210_MIC2_POWER_REG48, 0x00);
    ret |= es7210_write_reg(ES7210_MIC3_POWER_REG49, 0x00);
    ret |= es7210_write_reg(ES7210_MIC4_POWER_REG4A, 0x00);
    ret |= es7210_mic_select(mic_select);
    return ret;
}

esp_err_t es7210_stop(void)
{
    esp_err_t ret = ESP_OK;
    ret |= es7210_write_reg(ES7210_MIC1_POWER_REG47, 0xff);
    ret |= es7210_write_reg(ES7210_MIC2_POWER_REG48, 0xff);
    ret |= es7210_write_reg(ES7210_MIC3_POWER_REG49, 0xff);
    ret |= es7210_write_reg(ES7210_MIC4_POWER_REG4A, 0xff);
    ret |= es7210_write_reg(ES7210_MIC12_POWER_REG4B,0xff);
    ret |= es7210_write_reg(ES7210_MIC34_POWER_REG4C, 0xff);
    ret |= es7210_write_reg(ES7210_ANALOG_REG40, 0xc0);
    ret |= es7210_write_reg(ES7210_CLOCK_OFF_REG01, 0x7f);
    ret |= es7210_write_reg(ES7210_POWER_DOWN_REG06, 0x07);
    return ret;
}

esp_err_t es7210_adc_ctrl_state(audio_hal_codec_mode_t mode, audio_hal_ctrl_t ctrl_state)
{
    static uint8_t regv;
    esp_err_t ret = ESP_OK;
    KIT_LOGW("ES7210 only supports ADC mode");
    ret = es7210_read_reg(ES7210_CLOCK_OFF_REG01);
    if ((ret != 0x7f) && (ret != 0xff)) {
        regv = es7210_read_reg(ES7210_CLOCK_OFF_REG01);
    }
    if (ctrl_state == AUDIO_HAL_CTRL_START) {
        KIT_LOGI( "The ES7210_CLOCK_OFF_REG01 value before stop is %x",regv);
        ret |= es7210_start(regv);
    } else {
        KIT_LOGW("The codec is about to stop");
        regv = es7210_read_reg(ES7210_CLOCK_OFF_REG01);
        ret |= es7210_stop();
    }
    return ret;
}

esp_err_t es7210_adc_set_gain(es7210_gain_value_t gain)
{
    esp_err_t ret = ESP_OK;
    uint32_t  max_gain_vaule = 14;
    if (gain < 0) {
        gain = 0;
    } else if (gain > max_gain_vaule) {
        gain = max_gain_vaule;
    }
    KIT_LOGD( "SET: gain:%d", gain);
    if (mic_select & ES7210_INPUT_MIC1) {
        ret |= es7210_update_reg_bit(ES7210_MIC1_GAIN_REG43, 0x0f, gain);
    }
    if (mic_select & ES7210_INPUT_MIC2) {
        ret |= es7210_update_reg_bit(ES7210_MIC2_GAIN_REG44, 0x0f, gain);
    }
    if (mic_select & ES7210_INPUT_MIC3) {
        ret |= es7210_update_reg_bit(ES7210_MIC3_GAIN_REG45, 0x0f, gain);
    }
    if (mic_select & ES7210_INPUT_MIC4) {
        ret |= es7210_update_reg_bit(ES7210_MIC4_GAIN_REG46, 0x0f, gain);
    }
    return ret;
}

esp_err_t es7210_adc_get_gain(void)
{
    int regv = 0;
    uint8_t gain_value;
    if (mic_select & ES7210_INPUT_MIC1) {
        regv = es7210_read_reg(ES7210_MIC1_GAIN_REG43);
    } else if (mic_select & ES7210_INPUT_MIC2) {
        regv = es7210_read_reg(ES7210_MIC2_GAIN_REG44);
    } else if (mic_select & ES7210_INPUT_MIC3) {
        regv = es7210_read_reg(ES7210_MIC3_GAIN_REG45);
    } else if (mic_select & ES7210_INPUT_MIC4) {
        regv = es7210_read_reg(ES7210_MIC4_GAIN_REG46);
    } else {
        KIT_LOGE( "No MIC selected");
        return ESP_FAIL;
    }
    if (regv == ESP_FAIL) {
        return regv;
    }
    gain_value = (regv & 0x0f);     /* Retain the last four bits for gain */
    KIT_LOGI( "GET: gain_value:%d", gain_value);
    return gain_value;
}

esp_err_t es7210_adc_set_volume(int volume)
{
    esp_err_t ret = ESP_OK;
    KIT_LOGD( "ADC can adjust gain");
    return ret;
}

esp_err_t es7210_set_mute(bool enable)
{
    KIT_LOGD( "ES7210 SetMute :%d", enable);
    return ESP_OK;
}

void es7210_read_all(void)
{
    for (int i = 0; i <= 0x4E; i++) {
        uint8_t reg = es7210_read_reg(i);
        ets_printf("REG:%02x, %02x\n", reg, i);
    }
}
