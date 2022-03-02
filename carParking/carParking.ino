#include <Servo.h>
Servo myservo; // 宣告伺服馬達物件

int red = 5; // LED 訊號線腳位 
int green = 6; 
int blue = 7;  

int parkSpace = 3; // 預設車位數量
bool detection = false; // lock

void setup(){  
  Serial.begin(9600);
  myservo.attach(9); // 設定要將伺服馬達接到哪一個 PIN 腳
  myservo.write(180);  // 旋轉到 180 度
  setColor(0, 255, 0); // 初始綠燈
  pinMode(red, OUTPUT); // 設定 LED 腳位是輸出腳位
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop(){
  int sensorValueA0 = analogRead(A0); // 讀取&設定光敏電阻值
  int sensorValueA1 = analogRead(A1);

  switch(parkSpace){
    case 1: // 僅剩一個車位
      setColor(0, 0, 255); // Yello Color
      break;
    case 0: // 沒車位
      setColor(255, 0, 0); // Red Color
      break; 
    default: // 有車位
      setColor(0, 255, 0); // Green Color
      break;
  }
  if(parkSpace != 0){ // 停車場還有空位
    if(parkSpace == 3){ // 如果停車場沒車，只進不出
      if(sensorValueA0 < 400){ // 400 是 A0 光敏電阻(進入感測)值
        detection = true;
        myservo.write(90); // on
      }
      if(sensorValueA1 < 40 && detection){ // 40 是 A1 光敏(出去感測)電阻值
        parkSpace -= 1;
        detection = false;
        myservo.write(180); // off
      }
    }
    else{ // 否則進出都可以
      // ----------------- 進 --------------------
      if(sensorValueA0 < 400){
        detection = true;
        myservo.write(90); // on
      }
      if(sensorValueA1 < 40 && detection){ 
        parkSpace -= 1;
        detection = false;
        myservo.write(180); // off
      }
      // ----------------- 出 --------------------
      if(sensorValueA1 < 40){
        detection = true;
        myservo.write(90); // on
      }
      if(sensorValueA0 < 400 && detection){
        parkSpace += 1;
        detection = false;
        myservo.write(180); // off
      }      
    }
  }
  if(parkSpace == 0){ // 停車場滿車，只出不進
    if(sensorValueA1 < 40){
      detection = true;
      myservo.write(90); // on
    }
    if(sensorValueA0 < 400 && detection){
      parkSpace += 1;
      detection = false;
      myservo.write(180); // off
    }
  }

  // debug
  Serial.println(parkSpace);
  Serial.println(detection);
  delay(300);
}

void setColor(int redValue, int greenValue, int blueValue){
  analogWrite(red, redValue);
  analogWrite(green, greenValue);
  analogWrite(blue, blueValue);
}
