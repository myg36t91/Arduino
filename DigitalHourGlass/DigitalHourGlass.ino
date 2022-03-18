/*
  Arduino Starter Kit example
  Project 8 - Digital Hourglass

  This sketch is written to accompany Project 8 in the Arduino Starter Kit

  Parts required:
  - 10 kilohm resistor
  - six 220 ohm resistors
  - six LEDs
  - tilt switch

  created 13 Sep 2012
  by Scott Fitzgerald

  http://www.arduino.cc/starterKit

  This example code is part of the public domain.
*/

// named constant for the switch pin
const int switchPin = 8;
const int buzzer = 12;
const int button = 13;

unsigned long previousTime = 0; // store the last time an LED was updated
int switchState = 0; // the current switch state
int prevSwitchState = 0; // the previous switch state
int led = 2; // a variable to refer to the LEDs

// 600000 = 10 minutes in milliseconds
long interval = 1000; // interval at which to light the next LED
int countDownSeconds = 0;
boolean timerStart = false;
boolean timerEnd = false;

void startTimer(){
  timerStart = true;
}

void buzzerStart(){
  tone(buzzer, 500);
}

void buzzerOff(){
  noTone(buzzer);
}

void flashing(){
  for (int x = 2; x < 8; x++) {
    digitalWrite(x, HIGH);
  }
  delay(500);
  for (int x = 2; x < 8; x++) {
    digitalWrite(x, LOW);
  }
  delay(500);
}

void increaseSeconds(){
  countDownSeconds++;
  if(countDownSeconds>6){
    countDownSeconds = 6;
  }
  digitalWrite(led+countDownSeconds-1, HIGH);
}

void setup() {
  // set the LED pins as outputs
  for (int x = 2; x < 8; x++) {
    pinMode(x, OUTPUT);
  }
  // set the tilt switch pin as input
  pinMode(switchPin, INPUT);
  Serial.begin(9600);
  buzzerOff();
}

void loop() {
  if(timerStart){
    unsigned long currentTime = millis();
    if (currentTime - previousTime > interval) {
      // save the current time as the last time you changed an LED
      previousTime = currentTime;
      // Turn the LED on
      digitalWrite(led+countDownSeconds-1, LOW);
      // increment the led variable
      // in 10 minutes the next LED will light up
      countDownSeconds--;
  
      if (countDownSeconds == 0) {
        buzzerStart();
        timerStart = false;
        flashing();
        flashing();
        buzzerOff();
      }
    }
  }
  else{
    int state = digitalRead(button);
    if(state == 0){
    int count = 0;
    while(state==0){
      Serial.println(count);
      state = digitalRead(button);
      delay(100);
      count++;
    }
    if(count>=20){
      startTimer();
    }
    else{
      increaseSeconds();
    }
  }
  }
}
