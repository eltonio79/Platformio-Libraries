#pragma once

#include "AudioConfig.h"
#ifdef USE_AUDIO_SERVER

#ifdef ESP32
#include <WiFi.h>
#endif
#include "AudioCodecs/CodecWAV.h"
#include "AudioTools.h"

namespace audio_tools {

/// Calback which writes the sound data to the stream
typedef void (*AudioServerDataCallback)(Print *out);

/**
 * @brief A simple Arduino Webserver which streams the result 
 * This class is based on the WiFiServer class. All you need to do is to provide the data 
 * with a callback method or from an Arduino Stream:   in -copy> client

 * 
 * 
 * @author Phil Schatzmann
 * @copyright GPLv3
 */
class AudioServer {

    public:
        /**
         * @brief Construct a new Audio W A V Server object
         * We assume that the WiFi is already connected
         */
        AudioServer() = default;

        /**
         * @brief Construct a new Audio W A V Server object
         * 
         * @param network 
         * @param password 
         */
        AudioServer(const char* network, const char *password) {
            this->network = (char*)network;
            this->password = (char*)password;
        }

        /**
         * @brief Start the server. You need to be connected to WiFI before calling this method
         * 
         * @param in 
         * @param contentType Mime Type of result
         */
        void begin(Stream &in, const char* contentType) {
             LOGD(LOG_METHOD);
            this->in = &in;
            this->content_type = contentType;

            connectWiFi();

            // start server
            server.begin();
        }

        /**
         * @brief Start the server. The data must be provided by a callback method
         * 
         * @param cb 
         * @param contentType Mime Type of result
         */
        void begin(AudioServerDataCallback cb, const char* contentType) {
             LOGD(LOG_METHOD);
            this->in =nullptr;
            this->callback = cb;
            this->content_type = contentType;

            connectWiFi();

            // start server
            server.begin();
        }

        /**
         * @brief Add this method to your loop
         * Returns true while the client is connected. (The same functionality like doLoop())
         * 
         * @return true 
         * @return false 
         */
        bool copy(){
            return doLoop();
        }

        /**
         * @brief Add this method to your loop
         * Returns true while the client is connected.
         */
        bool doLoop() {
            //LOGD("doLoop");
            bool active = true;
            if (!client_obj.connected()) {
                client_obj = server.available(); // listen for incoming clients
                processClient();
            } else {
                // We are connected: copy input from source to wav output
                if (client_obj){
                    if (callback==nullptr) {
                        LOGD("copy data...");
                        if (converter_ptr==nullptr) {
                            copier.copy();
                        }else {
                            copier.copy<int16_t>(*converter_ptr);
                        }
                        // if we limit the size of the WAV the encoder gets automatically closed when all has been sent
                        if (!client_obj) {
                            LOGI("stop client...");
                            client_obj.stop();
                            active = false;
                        }
                    } 
                } else {
                    LOGI("client was not connected");
                }
            }
            return active;
        }

        // defines a converter that will be used when the audio is rendered
        void setConverter(BaseConverter<int16_t>  *c){
            converter_ptr = c;
        }

        Stream& out() {
            return client_obj;
        }

        Stream* out_ptr() {
            return &client_obj;
        }

    protected:
        // WIFI
        WiFiServer server = WiFiServer(80);
        WiFiClient client_obj;
        char *password = nullptr;
        char *network = nullptr;

        // Content
        const char *content_type=nullptr;
        AudioServerDataCallback callback = nullptr;
        Stream *in = nullptr;                    
        StreamCopy copier;
        BaseConverter<int16_t> *converter_ptr = nullptr;

        void connectWiFi() {
             LOGD(LOG_METHOD);
            if (WiFi.status() != WL_CONNECTED && network!=nullptr && password != nullptr){
                WiFi.begin(network, password);
                //WiFi.setSleep(false);
                while (WiFi.status() != WL_CONNECTED){
                    Serial.print(".");
                    delay(500); 
                }
                Serial.println();
            }
            Serial.print("IP address: ");
            Serial.println(WiFi.localIP());
        }

        virtual void sendReplyHeader(){
             LOGD(LOG_METHOD);
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client_obj.println("HTTP/1.1 200 OK");
            if (content_type!=nullptr){
                client_obj.print("Content-type:");
                client_obj.println(content_type);
            }
            client_obj.println();

        }

        virtual void sendReplyContent() {
             LOGD(LOG_METHOD);
            if (callback!=nullptr){
                // provide data via Callback
                LOGI("sendReply - calling callback");
                callback(&client_obj);
                client_obj.stop();
            } else if (in!=nullptr){
                // provide data for stream
                LOGI("sendReply - Returning WAV stream...");
                copier.begin(client_obj, *in);
            }
        }

        // Handle an new client connection and return the data
        void processClient() {
            //LOGD("processClient");
            if (client_obj)  { // if you get a client,
                LOGI("New Client."); // print a message out the serial port
                String currentLine = "";       // make a String to hold incoming data from the client
                while (client_obj.connected()) { // loop while the client's connected
                    if (client_obj.available()) { // if there's bytes to read from the client,
                        char c = client_obj.read(); // read a byte, then
                        if (c == '\n') { // if the byte is a newline character

                            // if the current line is blank, you got two newline characters in a row.
                            // that's the end of the client HTTP request, so send a response:
                            if (currentLine.length() == 0){
                                sendReplyHeader();
                                sendReplyContent();
                                // break out of the while loop:
                                break;
                            } else { // if you got a newline, then clear currentLine:
                                currentLine = "";
                            }
                        }
                        else if (c != '\r') { // if you got anything else but a carriage return character,
                            currentLine += c; // add it to the end of the currentLine
                        }
                    }
                }
            }  
        }
};


/**
 * @brief A simple Arduino Webserver which streams the audio using the indicated encoder.. 
 * This class is based on the WiFiServer class. All you need to do is to provide the data 
 * with a callback method or from a Stream.
 * 
 * in -copy> client
 */
class AudioEncoderServer  : public AudioServer {

    public:

        /**
         * @brief Construct a new Audio W A V Server object
         * We assume that the WiFi is already connected
         */
        AudioEncoderServer(AudioEncoder *encoder) : AudioServer() {
            this->encoder = encoder;
        }

        /**
         * @brief Construct a new Audio W A V Server object
         * 
         * @param network 
         * @param password 
         */
        AudioEncoderServer(AudioEncoder *encoder, const char* network, const char *password) : AudioServer(network, password) {
            this->encoder = encoder;
        }

        /**
         * @brief Destructor release the memory
         **/
        ~AudioEncoderServer() {
        }


        /**
         * @brief Start the server. You need to be connected to WiFI before calling this method
         * 
         * @param in 
         * @param sample_rate 
         * @param channels 
         */
        void begin(Stream &in, int sample_rate, int channels, int bits_per_sample=16, BaseConverter<int16_t> *converter=nullptr) {
            LOGD(LOG_METHOD);
            this->in = &in;
            audio_info.sample_rate = sample_rate;
            audio_info.channels = channels;
            audio_info.bits_per_sample = bits_per_sample;
            encoder->setAudioInfo(audio_info);
            encoded_stream.begin(&client_obj, encoder);
            AudioServer::begin(in, encoder->mime());
        }

        /**
         * @brief Start the server. You need to be connected to WiFI before calling this method
         * 
         * @param in 
         * @param info 
         * @param converter 
         */
        void begin(Stream &in, AudioBaseInfo info, BaseConverter<int16_t> *converter=nullptr) {
            LOGD(LOG_METHOD);
            this->in = &in;
            this->audio_info = info;
            encoder->setAudioInfo(audio_info);
            encoded_stream.begin(&client_obj, encoder);

            AudioServer::begin(in, encoder->mime());
        }

        /**
         * @brief Start the server. The data must be provided by a callback method
         * 
         * @param cb 
         * @param sample_rate 
         * @param channels 
         */
        void begin(AudioServerDataCallback cb, int sample_rate, int channels, int bits_per_sample=16) {
            LOGD(LOG_METHOD);
            audio_info.sample_rate = sample_rate;
            audio_info.channels = channels;
            audio_info.bits_per_sample = bits_per_sample;
            encoder->setAudioInfo(audio_info);

            AudioServer::begin(cb, encoder->mime());
        }

        // provides a pointer to the encoder
        AudioEncoder *audioEncoder(){
            return encoder;
        }


    protected:

        // Sound Generation
        EncodedAudioStream  encoded_stream;
        AudioBaseInfo audio_info;
        AudioEncoder *encoder = nullptr;


        virtual void sendReplyContent() {
            LOGD(LOG_METHOD);
            if (callback!=nullptr){
                encoded_stream.begin(out_ptr(), encoder);
                // provide data via Callback to encoded_stream
                LOGI("sendReply - calling callback");
                callback(&encoded_stream);
                client_obj.stop();
            } else if (in!=nullptr){
                // provide data for stream: in -copy>  encoded_stream -> out
                LOGI("sendReply - Returning WAV stream...");
                encoded_stream.begin(out_ptr(), encoder);
                copier.begin(encoded_stream, *in);
            }
        }


};

/**
 * @brief A simple Arduino Webserver which streams the audio as WAV data. 
 * This class is based on the AudioEncodedServer class. All you need to do is to provide the data 
 * with a callback method or from a Stream.
 */
class AudioWAVServer : public AudioEncoderServer {
    public:
        /**
         * @brief Construct a new Audio W A V Server object
         * We assume that the WiFi is already connected
         */
        AudioWAVServer() : AudioEncoderServer(new WAVEncoder()){
        }

        /**
         * @brief Construct a new Audio W A V Server object
         * 
         * @param network 
         * @param password 
         */
        AudioWAVServer(const char* network, const char *password) : AudioEncoderServer(new WAVEncoder(), network, password) {
        }

        /// Destructor: release the allocated encoder
        ~AudioWAVServer() {
            AudioEncoder *encoder = audioEncoder();
            if (encoder!=nullptr){
                delete encoder;
            }
        }

                // provides a pointer to the encoder
        WAVEncoder &wavEncoder(){
            return *static_cast<WAVEncoder*>(encoder);
        }


};

}

#endif
