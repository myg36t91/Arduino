/*
  Arduino Starter Kit example
  Project 7 - Keyboard

  This sketch is written to accompany Project 7 in the Arduino Starter Kit

  Parts required:
  - two 10 kilohm resistors
  - 1 megohm resistor
  - 220 ohm resistor
  - four pushbuttons
  - piezo

  created 13 Sep 2012
  by Scott Fitzgerald

  http://www.arduino.cc/starterKit

  This example code is part of the public domain.
*/

// create an array of notes
// the numbers below correspond to the frequencies of middle C, D, E, and F
int notes[] = {262, 294, 330, 349, 370, 392, 440, 493};

void setup() {
  //start serial communication
  Serial.begin(9600);
}

void loop() {
  // create a local variable to hold the input on pin A0
  int keyVal = analogRead(A0);
  // send the value from A0 to the Serial Monitor
  Serial.println(keyVal);

  // play the note corresponding to each value on A0
  if (keyVal == 254) {
    // play the first frequency in the array on pin 8
    tone(8, notes[0]);
  } else if (keyVal >= 252 && keyVal <= 253) {
    // play the first frequency in the array on pin 8
    tone(8, notes[1]);
  } else if (keyVal == 340) {
    // play the second frequency in the array on pin 8
    tone(8, notes[2]);
  } else if (keyVal >= 19 && keyVal <= 20) {
    // play the third frequency in the array on pin 8
    tone(8, notes[3]);
  } else if (keyVal == 290) {
    // play the fourth frequency in the array on pin 8
    tone(8, notes[4]);
  } else if (keyVal == 382) {
    // play the fourth frequency in the array on pin 8
    tone(8, notes[5]);
  } else if (keyVal >= 349 && keyVal <= 350) {
    // play the fourth frequency in the array on pin 8
    tone(8, notes[6]);
  } else if (keyVal >= 266 && keyVal <= 267) {
    tone(8, notes[7]);
  } else {
    // if the value is out of range, play no tone
    noTone(8);
  }
  delay(250);
  
}
