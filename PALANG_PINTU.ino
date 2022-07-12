#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  //Change the HEX address
#include <Servo.h> 

Servo myservo1;
Servo myservo2;

// pin sensor infrared palang pintu
int IR1 = 3;  // pin palang pintu in
int IR2 = 4;
int IR3 = 6; // pin palang pintu out
int IR4 = 5;

int Slot = 4;           //Masukkan total slot parkir yang tersedia

int flag1 = 0;
int flag2 = 0;
int flag3 = 0;
int flag4 = 0;

void setup() {
  lcd.begin(16,2);
  lcd.backlight();
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  
  myservo1.attach(9); // pin dc motor servo palang masuk
  myservo1.write(90);

  myservo2.attach(10); // pin dc motor servo palang keluar
  myservo2.write(90);

  /*lcd.setCursor (0,0);
  lcd.print("     ARDUINO    ");
  lcd.setCursor (0,1);
  lcd.print(" PARKING SYSTEM ");
  delay (2000);
  lcd.clear();*/
}

void loop(){ 

  //palang pintu masuk
  
  if(digitalRead (IR1) == LOW && flag1==0){
    if(Slot>0){
      flag1=1;
    if(flag2==0){
      myservo1.write(0); Slot = Slot-1;
      }
    }
    else{
      lcd.setCursor (0,0);
      lcd.print(" Parkir Penuh ");    
      lcd.setCursor (0,1);
      lcd.print("  Parking Full  "); 
      delay (3000);
      lcd.clear(); 
    }
  }
  if(digitalRead (IR2) == LOW && flag2==0){
    flag2=1;
  if(flag1==0){
    myservo1.write(90);
  }
 }
  if(flag1==1 && flag2==1){
    delay (1000);
    myservo1.write(100);
    flag1=0, flag2=0;
  }

  //palang pintu keluar
  if(digitalRead (IR3) == LOW && flag3==0){
      flag3=1;
    if(flag4==0){
      myservo2.write(0); Slot = Slot+1;
      }
  }
 if(digitalRead (IR4) == LOW && flag4==0){
    flag4=1;
  if(flag3==0){
    myservo2.write(90);
  }
 }
  if(flag3==1 && flag4==1){
    delay (1000);
    myservo2.write(100);
    flag3=0, flag4=0;
  }


lcd.setCursor (0,0);
lcd.print("Selamat Datang!");
lcd.setCursor (0,1);
lcd.print("Slot Parkir :");
lcd.print(Slot); 
}
