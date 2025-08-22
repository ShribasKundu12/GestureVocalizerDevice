#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MPU6050.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
MPU6050 mpu;

// Flex pins
const int flex1 = A0;
const int flex2 = A1;
const int flex3 = A2;
const int flex4 = A3;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Gesture Vocaliser");
  lcd.setCursor(0, 1);
  lcd.print("Initialized...");
  delay(3000);
  lcd.clear();

  mpu.initialize();
  if (!mpu.testConnection()) {
    lcd.print("MPU6050 Fail");
    while (1);
  }

  pinMode(flex1, INPUT);
  pinMode(flex2, INPUT);
  pinMode(flex3, INPUT);
  pinMode(flex4, INPUT);
}

void loop() {
  // Flex sensor readings
  int f1 = analogRead(flex1);
  int f2 = analogRead(flex2);
  int f3 = analogRead(flex3);
  int f4 = analogRead(flex4);

  // MPU6050 readings
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  Serial.print("F1: "); Serial.print(f1);
  Serial.print(" F2: "); Serial.print(f2);
  Serial.print(" F3: "); Serial.print(f3);
  Serial.print(" F4: "); Serial.print(f4);
  Serial.print(" AX: "); Serial.print(ax);
  Serial.print(" AY: "); Serial.print(ay);
  Serial.print(" AZ: "); Serial.println(az);

  // Gesture 1: all fingers straight
  bool fingersStraight = (f1 < 750 && f2 < 750 && f3 < 750 && f4 < 750);

  // Gesture 2: specific MPU6050 position
  bool helloGesture = (ax <0 && ay <0);

  // Gesture 3: new custom gesture
  //bool winGesture = (f1 > 700 && f2 < 700 && f3 > 700 && f4 >= 709 && ax<0);

 // bool okGesture = (f1 >=750 && f2 >=f1 && f3 > 720 && f4 < 740);

  bool comehereGesture = (f1 >= 725 && f2 >= 717 && f3 >= 730 && f4 >= 740);
  bool givemewaterGesture = (ax < 0);
  bool disapprovalGesture = (ay < 0 &&  ax>0);
  lcd.setCursor(0, 0);

  //if (fingersStraight && specificPosition) {
    //lcd.print("Gesture: Hello");
 // } 
  /*if (winGesture) {
    lcd.print(" Victory...         ");
  }*/
  
  if(helloGesture){
    lcd.print(" Hello...");
  }
  else if(givemewaterGesture){
    lcd.print("Give Me Water...    ");
  }
  else if(disapprovalGesture){
    lcd.print("Disapproved!!     ");
  }
  /*else if (okGesture) {
    lcd.print(" Ok...             ");
  }*/
  else if (comehereGesture) {
    lcd.print(" Come Here...       ");
  }
  else {
    lcd.print(" Waiting...  ");
  }

  delay(1000);
}
