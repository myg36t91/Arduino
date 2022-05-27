/*
  Arduino Starter Kit example
  Project 9 - Motorized Pinwheel

  This sketch is written to accompany Project 9 in the Arduino Starter Kit

  Parts required:
  - 10 kilohm resistor
  - pushbutton
  - motor
  - 9V battery
  - IRF520 MOSFET
  - 1N4007 diode

  created 13 Sep 2012
  by Scott Fitzgerald

  http://www.arduino.cc/starterKit

  This example code is part of the public domain.
*/

// named constants for the switch and motor pins
const int switchPin = 2; // the number of the switch pin
const int motorPin =  9; // the number of the motor pin
int pinA3 = A3;


int switchState = 0;  // variable for reading the switch's status

void setup() {
  // initialize the motor pin as an output:
  pinMode(motorPin, OUTPUT);
  // initialize the switch pin as an input:
  pinMode(switchPin, INPUT);
}

void loop() {
  // read the state of the switch value:

  int val = analogRead(pinA3);
  int val_map = map(val, 0, 1023, 0, 179);
  // check if the switch is pressed.
  if (val == HIGH) {
    // turn motor on:
    analogWrite(motorPin, val_map);
  } else {
    // turn motor off:
    analogWrite(motorPin, val_map);
  }
}
