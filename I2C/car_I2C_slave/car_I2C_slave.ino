// COM4
# include <Wire.h>
# define slave_address 0x8
# define buzzPin 12

int sensorPin = A0;
int buttonPin = 2;
int sensorValue = 0, dt = 0;
int ledPin;
int lottoStartVal;
bool initFlag = false;
bool isLock = false;  // 0
bool ledstop = false;

void setup(){
  Wire.begin(slave_address);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(8, OUTPUT); // Red
  pinMode(9, OUTPUT); // Yellow
  pinMode(10, OUTPUT);// Yellow
  pinMode(11, OUTPUT);// Green
  pinMode(buzzPin, OUTPUT); // 蜂鳴器
  turnoff();
}

void loop(){
//  Serial.print("Lock"); Serial.println(isLock);
  ledstop = digitalRead(buttonPin);
//  Serial.print("Btn"); Serial.println(ledstop);
//  isLock = false;
  if(!isLock){
    start();
  }
  if(ledstop == 1){
    isLock = true;  
  }
}

void turnoff(){
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void start(){
  if(lottoStartVal < 50){
    delay(100);
    Serial.println("******");
    Serial.println(lottoStartVal);
    Serial.println("******");
    initFlag = true;
  }
  if(initFlag == true){
     LEDshine();
  }
}

void LEDshine(){
  sensorValue = analogRead(sensorPin);
  dt = map(sensorValue, 0, 657, 50, 2000);
  for(ledPin=8; ledPin<=11; ledPin++){
    digitalWrite(ledPin, HIGH);
    ledstop = digitalRead(buttonPin);
//    Serial.println(ledstop);
    if(ledstop == true){);
      digitalWrite(ledPin, HIGH);
      delay(500);
      digitalWrite(ledPin, LOW);
      (ledPin == 11)? Bingovoice_O() : Bingovoice_X();
      initFlag = false;
      break;
    }
    else{
      delay(dt);
      digitalWrite(ledPin, LOW);
//      Serial.println(ledPin);
    }
  }
}

void Bingovoice_O() {
  int freq[] = {262, 294, 330};
  int melody[] = {1, 2, 3};
  int beat[] = {1, 1, 1};
  for(int i = 0 ; i < 3 ; i++){
    tone(buzzPin, freq[melody[i]-1]);
    delay(beat[i]*250); 
    noTone(buzzPin);
  }
}

void Bingovoice_X() {
  int freq[] = {330, 330, 330};
  int melody[] = {3, 2, 1};
  int beat[] = {1, 1, 1};
  for(int i = 0 ; i < 3 ; i++){
    tone(buzzPin, freq[melody[i]-1]);
    delay(beat[i]*250); 
    noTone(buzzPin);
  }
}

char readByte;
void receiveEvent(int lottoStartVal) {
  while(Wire.available()){
    lottoStartVal = Wire.read();
    if(lottoStartVal != 0){
      Serial.println(lottoStartVal);
      delay(300);
      if(lottoStartVal < 50){
        digitalWrite(ledPin, LOW);
        isLock = false;
      }
    }
  }
}

void requestEvent() {
  if(ledPin == 11 && ledstop == true){
    Wire.write(ledPin);
  }
}
