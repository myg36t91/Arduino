// COM3
#include <Wire.h>
#include <Servo.h> 
# define LEDR 9
# define LEDB 10
# define LEDG 11
# define slave_address 0x8

Servo myservo;

int lottoStartPin = A0; 
int lottoStartVal = 0; 
int carSensorPin = A1; 
int carSensorVal = 0;
int returnLEDG = 0;
int carNum = 0;
int car_in = 0, car_out = 0;
bool forOneTime = true;

void setup(){
  Wire.begin(slave_address);
  myservo.attach(6);
  myservo.write(0);  
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  Serial.begin(9600);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, LOW);  
}

void loop(){
  // --------------------------------------
  lottoStartVal = analogRead(lottoStartPin);
  Serial.println(lottoStartVal);
  delay(200);
  // -------------------------------------- 
  Wire.beginTransmission(slave_address);
  Wire.write(lottoStartVal);
  Wire.endTransmission();
  Wire.requestFrom(slave_address, 2);
  if(Wire.available()){
    returnLEDG = Wire.read();
  }
  carSensorVal = analogRead(carSensorPin);
  if(carSensorVal < 450 && carNum == 0){myservo.write(0);}
  if(returnLEDG == 11 && forOneTime){ // 綠燈才能讓車進去
    car_parking();
    forOneTime = false;
  }
  forOneTime = true;
}

void car_parking(){
  Serial.println("***********");
  Serial.println(returnLEDG);
  Serial.println(forOneTime);
  Serial.println("***********");
  delay(300);
  for(;;){
    carSensorVal = analogRead(carSensorPin);
//    Serial.println(carSensorVal);
    delay(300);
    if(carNum < 3){
      myservo.write(90);
    }
    if(carSensorVal < 450){
      if(carNum < 3){ // 停車場有幾輛車(max:3)
        delay(500);
        carNum += 1;
        myservo.write(0);
        Serial.println(carNum);
        delay(500);
        car_in = 1;
      }
      if(carNum == 3 || carNum == 0){myservo.write(0);}
      break;
    }
  }
  if(carNum == 1){
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, LOW);
  }
  if(carNum == 2){
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDB, HIGH);
  }
  if(carNum == 3){
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDB, LOW);
  }
}
