/*  Test of audio and control rate analog input using Mozzi sonification library.

  An audio input using the range between 0 to 5V on analog pin A0
  is sampled and output on digital pin 9.
  All the other analog channels are sampled at control rate and printed to Serial.

  Demonstrates mozziAnalogRead(pin), which reads analog inputs in the background,
  and getAudioInput(), which samples audio on AUDIO_INPUT_PIN, configured in mozzi_config.h.

  Configuration: requires these lines in the Mozzi/mozzi_config.h file:
  #define USE_AUDIO_INPUT true
  #define AUDIO_INPUT_PIN 0


  Circuit:
  Audio cable centre wire on pin A0, outer shielding to Arduino Ground.
  Audio output on DAC/A14 on Teensy 3.0, 3.1, or digital pin 9 on a Uno or similar, or
  check the README or http://sensorium.github.io/Mozzi/
  Analog sensor inputs on any other analog input pins.
  The serial printing might cause glitches, so try commenting
  them out to test if this is a problem.

  Mozzi documentation/API
  https://sensorium.github.io/Mozzi/doc/html/index.html

  Mozzi help/discussion/announcements:
  https://groups.google.com/forum/#!forum/mozzi-users

  Tim Barrass 2013, CC by-nc-sa.
*/

#include <MozziGuts.h>


void setup() {
  //Serial.begin(9600); // for Teensy 3.1, beware printout can cause glitches
  Serial.begin(115200);
  Serial.print("num_analog_inputs = ");
  Serial.println(NUM_ANALOG_INPUTS);
  startMozzi();
}


void updateControl(){
  for (int i=1;i<NUM_ANALOG_INPUTS;i++) { // analog 0 is configured for audio
    Serial.print(mozziAnalogRead(i)); // mozziAnalogRead is better than mozziAnalogRead
    Serial.print("\t"); // tab
  }
  Serial.println();
}


AudioOutput_t updateAudio(){
  int asig = getAudioInput(); // range 0-1023
  asig = asig - 512; // now range is -512 to 511
  return MonoOutput::fromAlmostNBit(9, asig).clip();
}


void loop(){
  audioHook();
}
