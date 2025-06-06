/**
 * @file streams-stk-a2dp.ino
 * @author Phil Schatzmann
 * @brief The Synthesis ToolKit in C++ (STK) is a set of open source audio signal processing and algorithmic synthesis classes written in the C++ programming language. 
 * @author Phil Schatzmann
 * @copyright GPLv3
 */

// Add this in your sketch or change the setting in AudioConfig.h
#define USE_STK

#include "AudioTools.h"
#include "Clarinet.h"



stk::Clarinet clarinet(440); // the stk clarinet instrument
STKGenerator<int16_t> generator(clarinet);    // subclass of SoundGenerator
GeneratedSoundStream<int16_t> in(generator);  // Stream generated from sine wave
AnalogAudioStream out; // Output stream
StreamCopy copier(out, in); // copy stkStream to a2dpStream
MusicalNotes notes; // notes with frequencies

// Arduino Setup
void setup(void) {
    Serial.begin(115200);
    AudioLogger::instance().begin(Serial, AudioLogger::Info);
    
    // start Output
    Serial.println("starting Analog Output...");
    out.begin(out.defaultConfig());

    // start STK input with default configuration
    Serial.println("starting STK...");
    auto cfgSTK = in.defaultConfig();
    cfgSTK.channels = 2;
    in.setNotifyAudioChange(out);
    in.begin(cfgSTK);

}

void playNoteStk() {
    static unsigned long timeout=0;
    static int note = 60;
    static bool isNoteOn = false;

    if (!isNoteOn) {
      if (millis()>timeout) {
          // play note for 1000 ms
          note += rand() % 10 - 5; // generate some random offset
          float frequency = notes.frequency(note);
          clarinet.noteOn( frequency, 0.5 );
  
          // set timeout
          timeout = millis()+1000;
      }
    } else {
      if (millis()>timeout) {
        // switch note off for 200 ms 
        clarinet.noteOff(0.5);
        
        // set timeout
        timeout = millis()+200; 
      }           
    }
    isNoteOn = !isNoteOn;
    
}


// Arduino loop - copy data
void loop() {
    playNoteStk();
    copier.copy();
}
