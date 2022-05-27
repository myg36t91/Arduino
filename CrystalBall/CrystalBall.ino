
// include the library code:
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int switchState1;
int switchState2;
int reply;
int score;
int btn1 = 6;
int btn2 = 7;
int row = 0;
void setup(){
  lcd.begin(16, 2);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  lcd.setCursor(0, 0);
  lcd.print("team7");
  lcd.setCursor(0, 1);
  lcd.print("setup");
}
void loop(){
  for(int i=0;i<10;i++)
  {
    lcd.scrollDisplayRight();   //往右移一格顯示
    delay(200);   
  }
  // 判斷目前行數, 是0行，將Row + 1,往下跳一行          
  if(row == 0){
     row = row + 1;
     lcd.clear();
     lcd.setCursor(10,1);
     lcd.print("hello!"); 
     delay(200);          
  }
   
  for(int i=0;i<10;i++)
  {
    lcd.scrollDisplayLeft();  //往左移一格顯示
    delay(200);
  }
  // 判斷目前行數, 是1行，將Row 改為0行         
  if(row == 1){
     row = 0;
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("hello!"); 
     delay(200);          
  }          
  switchState1 = digitalRead(btn1);
  switchState2 = digitalRead(btn2);
  if(switchState1 == HIGH){
    reply = random(1, 12);
    lcd.clear();
    lcd.setCursor(0, 0);
    // print some text
    lcd.print("Team");
    lcd.print(reply);
    lcd.print(", your final score:");
  }
  if(switchState2 == HIGH){
    score = random(0, 100);
    lcd.setCursor(0, 1);
    lcd.print(score);
  }
}
