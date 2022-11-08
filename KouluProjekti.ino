#include <LiquidCrystal.h>

const int rs = 12, en =11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //Reserving digital pins 2-7 for lcd
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //intializing the LiquidCrystal library by associating the pins

void setup() {
  //setting the LCD's colums and rows (16 columns, 2 rows)
  lcd.begin(16, 2);
  //tell the user that we're calibrating the sensor
  lcd.print("calibrating");
  delay(10000); //remove when the calibration code is written!!!!
  lcd.clear();
  //calibrating the sensor
  //telling the user that calibration is done
  lcd.print("calibration");
  lcd.setCursor(0, 1);
  lcd.print("is done");
  delay(10000);
  lcd.clear();

}

void loop() {
  // put your main code here, to run repeatedly:

}

void servoMoottori(){
  
}

int aaniTutka(){
  
}

void ilmoitusSahkoposti(){
  
}

void ilmoitusLCD(){
  
}
