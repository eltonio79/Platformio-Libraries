#pragma once

#include "AudioTools/AudioLogger.h"
#include "AudioTools/AudioTypes.h"
#include "AudioBasic/Vector.h"

namespace audio_tools {

/**
 * @brief Base class to define the abstract interface for the sound generating classes
 * @author Phil Schatzmann
 * @copyright GPLv3
 * 
 * @tparam T 
 */
template <class T>
class SoundGenerator  {
    public:
        SoundGenerator() {
            info.bits_per_sample = sizeof(T)*8;
            info.channels = 1;
            info.sample_rate = 44100;
        }

        virtual ~SoundGenerator() {
            end();
        }

        virtual bool begin(AudioBaseInfo info) {
            this->info = info;
            return begin();
        }

        virtual bool begin() {
            LOGD(LOG_METHOD);
            active = true;
            activeWarningIssued = false;
            LOGI("bits_per_sample: %d", info.bits_per_sample);
            LOGI("channels: %d", info.channels);
            LOGI("sample_rate: %d", info.sample_rate);
            return true;
        }

        /// ends the processing
        virtual void end(){
            active = false;
        }

        /// Checks if the begin method has been called - after end() isActive returns false
        virtual bool isActive() {
            return active;
        }

        /// Provides the samples into simple array - which represents 1 channel
        virtual size_t readSamples(T* data, size_t sampleCount=512){
            for (size_t j=0;j<sampleCount;j++){
                data[j] = readSample();
            }
            return sampleCount;
        }

        /// Provides the samples into a 2 channel array
        virtual size_t readSamples(T src[][2], size_t frameCount) {
            T tmp[frameCount];
            int len = readSamples(tmp, frameCount);
            for (int j=0;j<len;j++) {
                T value = tmp[j];
                src[j][1] = src[j][0] = value;
            }
            return frameCount;
        }

        /// Provides a single sample
        virtual  T readSample() = 0;

        /// Provides the data as byte array with the requested number of channels
        virtual size_t readBytes( uint8_t *buffer, size_t lengthBytes){
            //LOGD("readBytes: %d", (int)lengthBytes);
            size_t result = 0;
            int ch = audioInfo().channels;
            if (ch==0){
                LOGE("Undefine number of channels: %d",ch);
                ch = 1;
            }
            int frame_size = sizeof(T) * ch;
            if (active){
                int len = lengthBytes / frame_size;
                if (lengthBytes % frame_size!=0){
                    len++;
                }
                switch (ch){
                    case 1:
                        result = readSamples((T*) buffer, len) ;
                        break;
                    case 2:
                        result = readSamples((T(*)[2]) buffer, len);
                        break;
                    default:
                        LOGE( "SoundGenerator::readBytes -> number of channels %d is not supported (use 1 or 2)", ch);
                        result = 0;
                        break;
                }
            } else {
                if (!activeWarningIssued) {
                    LOGE("SoundGenerator::readBytes -> inactive");
                    activeWarningIssued=true;
                }
                result = 0;
            }
            //LOGD( "SoundGenerator::readBytes (channels: %d) %zu bytes -> %zu samples", ch, lengthBytes, result);
            return result * frame_size;
        }

        virtual AudioBaseInfo defaultConfig(){
            AudioBaseInfo def;
            def.bits_per_sample = sizeof(T)*8;
            def.channels = 1;
            def.sample_rate = 44100;
            return def;
        }

        virtual void setFrequency(uint16_t frequency) {
            LOGE("setFrequency not supported");
        }


        virtual AudioBaseInfo audioInfo() {
            return info;
        }

        virtual void setAudioInfo(AudioBaseInfo info){
            this->info = info;
            if (info.bits_per_sample!=sizeof(T)*8){
                LOGE("invalid bits_per_sample: %d", info.channels);
            }   
        }

    protected:
        bool active = false;
        bool activeWarningIssued = false;
        int output_channels = 1;
        AudioBaseInfo info;
        
};


/**
 * @brief Generates a Sound with the help of sin() function. If you plan to change the amplitude or frequency (incrementally),
 * I suggest to use SineFromTable instead.
 * @author Phil Schatzmann
 * @copyright GPLv3
 * 
 */
template <class T>
class SineWaveGenerator : public SoundGenerator<T>{
    public:

        // the scale defines the max value which is generated
        SineWaveGenerator(float amplitude = 32767.0, float phase = 0.0){
            LOGD("SineWaveGenerator");
            m_amplitude = amplitude;
            m_phase = phase;
        }

        bool begin() override {
            LOGI(LOG_METHOD);
            SoundGenerator<T>::begin();
            this->m_deltaTime = 1.0 / SoundGenerator<T>::info.sample_rate;
            return true;
        }

        bool begin(AudioBaseInfo info) override {
            LOGI("%s::begin(channels=%d, sample_rate=%d)","SineWaveGenerator", info.channels, info.sample_rate);
            SoundGenerator<T>::begin(info);
            this->m_deltaTime = 1.0 / SoundGenerator<T>::info.sample_rate;
            return true;
        }

        bool begin(AudioBaseInfo info, uint16_t frequency){
            LOGI("%s::begin(channels=%d, sample_rate=%d, frequency=%d)","SineWaveGenerator",info.channels, info.sample_rate,frequency);
            SoundGenerator<T>::begin(info);
            this->m_deltaTime = 1.0 / SoundGenerator<T>::info.sample_rate;
            if (frequency>0){
                setFrequency(frequency);
            }
            return true;
        }

        bool begin(int channels, int sample_rate, uint16_t frequency=0){
            SoundGenerator<T>::info.channels  = channels;
            SoundGenerator<T>::info.sample_rate = sample_rate;
            return begin(SoundGenerator<T>::info, frequency);
        }

        // update m_deltaTime
        virtual void setAudioInfo(AudioBaseInfo info) override {
            SoundGenerator<T>::setAudioInfo(info);
            this->m_deltaTime = 1.0 / SoundGenerator<T>::info.sample_rate;
        }

        virtual AudioBaseInfo defaultConfig() override {
            return SoundGenerator<T>::defaultConfig();
        }

        /// Defines the frequency - after the processing has been started
        void setFrequency(uint16_t frequency)  override {
            LOGI("setFrequency: %d", frequency);
            LOGI( "active: %s", SoundGenerator<T>::active ? "true" : "false" );
            m_frequency = frequency;
        }

        /// Provides a single sample
        virtual T readSample() override {
            float angle =  double_Pi * m_cycles + m_phase;
            T result = m_amplitude * sinf(angle);
            m_cycles += m_frequency * m_deltaTime;
            if (m_cycles > 1.0) {
                m_cycles -= 1.0;
            }
            return result;
        }

    protected:
        volatile float m_frequency = 0;
        float m_cycles = 0.0; // Varies between 0.0 and 1.0
        float m_amplitude = 1.0;  
        float m_deltaTime = 0.0;
        float m_phase = 0.0;
        float double_Pi = PI * 2.0;


        void logStatus() {
            SoundGenerator<T>::info.logStatus();
            LOGI( "amplitude: %f", this->m_amplitude );
            LOGI( "active: %s", SoundGenerator<T>::active ? "true" : "false" );
        }

};

/**
 * @brief Generates a square wave sound.
 * @author Phil Schatzmann
 * @copyright GPLv3
 * 
 */
template <class T>
class SquareWaveGenerator : public SineWaveGenerator<T> {
    public:
        SquareWaveGenerator(float amplitude = 32767.0, float phase = 0.0) : SineWaveGenerator<T>(amplitude, phase) {
            LOGD("SquareWaveGenerator");
        }

        virtual  T readSample() {
            return value(SineWaveGenerator<T>::readSample(), SineWaveGenerator<T>::m_amplitude);
        }

    protected:
        // returns amplitude for positive vales and -amplitude for negative values
        T value(T value, T amplitude) {
            return (value >= 0) ? amplitude : -amplitude;
        }
};


/**
 * @brief Generates a random noise sound with the help of rand() function.
 * @author Phil Schatzmann
 * @copyright GPLv3
 * 
 */
template <class T>
class NoiseGenerator : public SoundGenerator<T> {
    public:
        /// the scale defines the max value which is generated
        NoiseGenerator(T amplitude = 32767) {
            this->amplitude = amplitude;
        }

        /// Provides a single sample
        T readSample() {
            return (random(-amplitude, amplitude));
        }

    protected:
        T amplitude;

};


/**
 * @brief Provides 0 as sound data. This can be used e.g. to test the output functionality which should optimally just output
 * silence and no artifacts.
 * @author Phil Schatzmann
 * @copyright GPLv3
 * 
 */
template <class T>
class SilenceGenerator : public SoundGenerator<T> {
    public:
        // the scale defines the max value which is generated
        SilenceGenerator(double scale=1.0) {
            this->scale = scale;
        }

        /// Provides a single sample
        T readSample() {
            return  0; // return 0
        }

    protected:
        double scale;

};

/**
 * @brief An Adapter Class which lets you use any Stream as a Generator
 * @author Phil Schatzmann
 * @copyright GPLv3
 * @tparam T 
 */
template <class T>
class GeneratorFromStream : public SoundGenerator<T> {
    public:
        GeneratorFromStream() {
            maxValue = NumberConverter::maxValue(sizeof(T)*8);
        };

        /**
         * @brief Constructs a new Generator from a Stream object that can be used e.g. as input for AudioEffectss.
         * 
         * @param input Stream
         * @param channels number of channels of the Stream
         * @param volume factor my which the sample value is multiplied - default 1.0; Use it e.g. to reduce the volume (e.g. with 0.5)
         */
        GeneratorFromStream(Stream &input, int channels=1, float volume=1.0){
            maxValue = NumberConverter::maxValue(sizeof(T)*8);
            setStream(input);
            setVolume(volume);
            setChannels(channels);
        }

        /// (Re-)Assigns a stream to the Adapter class
        void setStream(Stream &input){
            this->p_stream = &input;
        }

        void setChannels(int channels){
            this->channels = channels;
        }

        /// Multiplies the input with the indicated factor (e.g. )
        void setVolume(float factor){
            this->volume = factor;
        }
        
        
        /// Provides a single sample from the stream
        T readSample() {
            T data = 0;
            float total = 0;
            if (p_stream!=nullptr) {
                for (int j=0;j<channels;j++){
                    p_stream->readBytes((uint8_t*)&data, sizeof(T));
                    total += data;
                }
                float avg = (total / channels) * volume;
                if (avg>maxValue){
                    data = maxValue;
                } else if (avg < -maxValue){
                    data = -maxValue;
                } else {
                    data = avg;
                }
            }
            return data;
        }

    protected:
        Stream *p_stream = nullptr;
        int channels=1;
        int volume=1.0;
        float maxValue;

};

/**
 * @brief We generate the samples from an array which is provided in the constructor
 * @author Phil Schatzmann
 * @copyright GPLv3
 * @tparam T 
 */
 
template <class T>
class GeneratorFromArray : public SoundGenerator<T> {
  public:

    GeneratorFromArray() = default;
    /**
     * @brief Construct a new Generator From Array object
     * 
     * @tparam array array of audio data of the the type defined as class template parameter 
     * @param repeat number of repetions the array should be played (default 1)
     * @param setInactiveAtEnd  defines if the generator is set inactive when the array has played fully. Default is true.
     */

    template  <size_t arrayLen> 
    GeneratorFromArray(T(&array)[arrayLen], int repeat=0, bool setInactiveAtEnd=true) {
        LOGD(LOG_METHOD);
        this->max_repeat = repeat;
        this->inactive_at_end = setInactiveAtEnd;
        setArray(array, arrayLen);
    }

    template  <int arrayLen> 
    void setArray(T(&array)[arrayLen]){
        LOGD(LOG_METHOD);
        setArray(array, arrayLen);
    }

    void setArray(T*array, size_t size){
      this->table_length = size;
      this->table = array;
      LOGI("table_length: %d", (int)size);
    }

    virtual bool begin(AudioBaseInfo info) {
        return SoundGenerator<T>::begin(info);
    }

    /// Starts the generation of samples
    bool begin() override {
      LOGI(LOG_METHOD);
      SoundGenerator<T>::begin();
      sound_index = 0;
      repeat_counter = 0;
      is_running = true;
      return true;
    }

    /// Provides a single sample
    T readSample() override {
      // at end deactivate output
      if (sound_index >= table_length) {
        // LOGD("reset index - sound_index: %d, table_length: %d",sound_index,table_length);
        sound_index = 0;
        // deactivate when count has been used up
        if (max_repeat>=1 && ++repeat_counter>=max_repeat){
            LOGD("atEnd");
            this->is_running = false;
            if (inactive_at_end){
                this->active = false;
            }
        }
      }

      //LOGD("index: %d - active: %d", sound_index, this->active);
      T result = 0;
      if (this->is_running) {
        result = table[sound_index];
        sound_index++;
      }

      return result;
    }

    // Similar like is active to check if the array is still playing.  
    bool isRunning() {
        return is_running;
    }


  protected:
    int sound_index = 0;
    int max_repeat = 0;
    int repeat_counter = 0;
    bool inactive_at_end;
    bool is_running = false;
    T *table;
    size_t table_length = 0;

};

/**
 * @brief A sine generator based on a table. The table is created based using degress where one full wave is 360 degrees.
 * @author Phil Schatzmann
 * @copyright GPLv3
 */
template <class T>
class SineFromTable  : public SoundGenerator<T> {
    public:
        SineFromTable(float amplitude = 32767.0){
            this->amplitude = amplitude;
            this->amplitude_to_be = amplitude;
        }

        /// Defines the new amplitude (volume)
        void setAmplitude(float amplitude){
            this->amplitude_to_be = amplitude;
        }

        /// To avoid pops we do not allow to big amplitude changes at once and spread them over time
        void setMaxAmplitudeStep(float step){
            max_amplitude_step = step;
        }

        T readSample() {
            // update angle
            angle += step;
            if (angle >= 360){
               angle -= 360; 
               // update frequency at start of circle (near 0 degrees)
               step = step_new;

               updateAmplitudeInSteps();
               //amplitude = amplitude_to_be;
            }
            return amplitude * interpolate(angle);
        }

        bool begin() {
            is_first = true;
            SoundGenerator<T>::begin();
            base_frequency = SoundGenerator<T>::audioInfo().sample_rate / 360.0; //122.5 hz (at 44100); 61 hz (at 22050)
            return true;
        }

        bool begin(AudioBaseInfo info, float frequency) {
            SoundGenerator<T>::begin(info);
            base_frequency = SoundGenerator<T>::audioInfo().sample_rate / 360.0; //122.5 hz (at 44100); 61 hz (at 22050)
            setFrequency(frequency);
            return true;
        }

        bool begin(int channels, int sample_rate, uint16_t frequency=0){
            SoundGenerator<T>::info.channels  = channels;
            SoundGenerator<T>::info.sample_rate = sample_rate;
            return begin(SoundGenerator<T>::info, frequency);
        }

        void setFrequency(float freq) {
            step_new = freq / base_frequency;
            if (is_first){
                step = step_new;
                is_first = false;
            }
            LOGI("step: %f", step_new);
        }

    protected:
        bool is_first = true;
        float amplitude;
        float amplitude_to_be;
        float max_amplitude_step = 50;
        float base_frequency = 1.0;
        float step = 1.0; 
        float step_new = 1.0; 
        float angle = 0;
        //122.5 hz (at 44100); 61 hz (at 22050)
        const float values[181] = {0, 0.0174524, 0.0348995, 0.052336, 0.0697565, 0.0871557, 0.104528, 0.121869, 0.139173, 0.156434, 0.173648, 0.190809, 0.207912, 0.224951, 0.241922, 0.258819, 0.275637, 0.292372, 0.309017, 0.325568, 0.34202, 0.358368, 0.374607, 0.390731, 0.406737, 0.422618, 0.438371, 0.45399, 0.469472, 0.48481, 0.5, 0.515038, 0.529919, 0.544639, 0.559193, 0.573576, 0.587785, 0.601815, 0.615661, 0.62932, 0.642788, 0.656059, 0.669131, 0.681998, 0.694658, 0.707107, 0.71934, 0.731354, 0.743145, 0.75471, 0.766044, 0.777146, 0.788011, 0.798636, 0.809017, 0.819152, 0.829038, 0.838671, 0.848048, 0.857167, 0.866025, 0.87462, 0.882948, 0.891007, 0.898794, 0.906308, 0.913545, 0.920505, 0.927184, 0.93358, 0.939693, 0.945519, 0.951057, 0.956305, 0.961262, 0.965926, 0.970296, 0.97437, 0.978148, 0.981627, 0.984808, 0.987688, 0.990268, 0.992546, 0.994522, 0.996195, 0.997564, 0.99863, 0.999391, 0.999848, 1, 0.999848, 0.999391, 0.99863, 0.997564, 0.996195, 0.994522, 0.992546, 0.990268, 0.987688, 0.984808, 0.981627, 0.978148, 0.97437, 0.970296, 0.965926, 0.961262, 0.956305, 0.951057, 0.945519, 0.939693, 0.93358, 0.927184, 0.920505, 0.913545, 0.906308, 0.898794, 0.891007, 0.882948, 0.87462, 0.866025, 0.857167, 0.848048, 0.838671, 0.829038, 0.819152, 0.809017, 0.798636, 0.788011, 0.777146, 0.766044, 0.75471, 0.743145, 0.731354, 0.71934, 0.707107, 0.694658, 0.681998, 0.669131, 0.656059, 0.642788, 0.62932, 0.615661, 0.601815, 0.587785, 0.573576, 0.559193, 0.544639, 0.529919, 0.515038, 0.5, 0.48481, 0.469472, 0.45399, 0.438371, 0.422618, 0.406737, 0.390731, 0.374607, 0.358368, 0.34202, 0.325568, 0.309017, 0.292372, 0.275637, 0.258819, 0.241922, 0.224951, 0.207912, 0.190809, 0.173648, 0.156434, 0.139173, 0.121869, 0.104528, 0.0871557, 0.0697565, 0.052336, 0.0348995, 0.0174524, 0}; 

        float interpolate(float angle){
            bool positive = (angle<=180);
            float angle_positive = positive ? angle : angle - 180.0;
            int angle_int1 = angle_positive;
            int angle_int2 = angle_int1+1;
            float v1 = values[angle_int1];
            float v2 = values[angle_int2];
            float result = v1 < v2 ? map(angle_positive,angle_int1,angle_int2,v1, v2) : map(angle_positive,angle_int1,angle_int2,v2, v1)  ;
            //float result = v1;
            return positive ? result : -result;
        }

        float map(float x, float in_min, float in_max, float out_min, float out_max) {
          return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
        }

        void updateAmplitudeInSteps() {
            float diff = amplitude_to_be - amplitude; 
            if (abs(diff) > max_amplitude_step){
                diff = (diff<0) ? -max_amplitude_step : max_amplitude_step;
            } 
            if (diff>=1.0){
                amplitude += diff;
            }
        }
};

/**
 * @brief Mixer which combines multiple sound generators into one output
 * @author Phil Schatzmann
 * @copyright GPLv3
 * @tparam T 
 */
template <class T>
class GeneratorMixer : public SoundGenerator<T> {
    public:
        GeneratorMixer() = default;

        void add(SoundGenerator<T> &generator){
            vector.push_back(&generator);
        }
        void add(SoundGenerator<T> *generator){
            vector.push_back(generator);
        }

        void clear() {
            vector.clear();
        }

        T readSample() {
            T result;
            int count = 0;
            for (int j=0;j<vector.size();j++){
                T tmp = vector[j]->readSample();
                if (j==actualChannel){
                    result = tmp;
                }
            }
            actualChannel++;
            if (actualChannel>=vector.size()){
                actualChannel = 0;
            }
            return result;;
        }

    protected:
        Vector<SoundGenerator<T>*> vector;
        int actualChannel=0;

};

/**
 * @brief Generates a test signal which is easy to check because the values are incremented or decremented by 1
 * @author Phil Schatzmann
 * @copyright GPLv3
 * @tparam T 
 */
template <class T>
class TestGenerator : public SoundGenerator<T>{
    public:
        TestGenerator(T max=1000, T inc=1){
            this->max=max;
        }

        T readSample() override {
            value += inc;
            if (abs(value)>=max){
                inc = -inc;
                value += (inc * 2);
            }
            return value;
        }

    protected:
        T max;
        T value=0;
        T inc=1;

};

}
