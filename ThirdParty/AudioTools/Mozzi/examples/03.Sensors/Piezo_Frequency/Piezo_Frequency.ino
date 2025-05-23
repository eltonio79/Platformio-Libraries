/*
   Example using a piezo to change the frequency of a sinewave
   with Mozzi sonification library.

   Demonstrates the use of Oscil to play a wavetable, and analog input for control.

   This example goes with a tutorial on the Mozzi site:
   http://sensorium.github.io/Mozzi/learn/introductory-tutorial/

   The circuit:
     Audio output on digital pin 9 on a Uno or similar, or
    DAC/A14 on Teensy 3.1, or
     check the README or http://sensorium.github.io/Mozzi/

     Piezo on analog pin 3:
       + connection of the piezo attached to the analog pin
       - connection of the piezo attached to ground
       1-megohm resistor between the analog pin and ground

    Mozzi documentation/API
    https://sensorium.github.io/Mozzi/doc/html/index.html

    Mozzi help/discussion/announcements:
    https://groups.google.com/forum/#!forum/mozzi-users

   Tim Barrass 2013, CC by-nc-sa.
*/

#include <MozziGuts.h>
#include <Oscil.h> // oscillator
#include <tables/sin2048_int8.h> // table for Oscils to play
#include <Smooth.h>

// increase the rate of updateControl from the default of 50, to catch the piezo's rapid transients
#define CONTROL_RATE 150

const int PIEZO_PIN = 3;  // set the analog input pin for the piezo

// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);


void setup(){
  //Serial.begin(9600); // for Teensy 3.1, beware printout can cause glitches
  Serial.begin(115200); // set up the Serial output so we can look at the piezo values // set up the Serial output so we can look at the piezo values
  startMozzi(CONTROL_RATE); // :)) use the control rate defined above
}


void updateControl(){
  // read the piezo
  int piezo_value = mozziAnalogRead(PIEZO_PIN); // value is 0-1023

  // print the value to the Serial monitor for debugging
  Serial.print("piezo_value = ");
  Serial.print(piezo_value);
  Serial.print("\t \t"); // prints 2 tabs

  int frequency = piezo_value*3; // calibrate

  // print the frequency to the Serial monitor for debugging
  Serial.print("frequency = ");
  Serial.print(frequency);

  // set the frequency
  aSin.setFreq(frequency);

  Serial.println(); // next line
}


AudioOutput_t updateAudio(){
  return MonoOutput::from8Bit(aSin.next());
}


void loop(){
  audioHook();
}
