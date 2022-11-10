#include <LiquidCrystal.h>
Servo myservo;        //servo object to control a servo
int distance = 0;
int servoPos = 0;    //variable to store the servo position
const int rs = 12, en =11, d4 = 5, d5 = 4, d6 = 3, d7 = 2, servoPin = 13, trigPin = 10, echoPin = 9; //Reserving digital pins 2-7 for lcd
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //intializing the LiquidCrystal library by associating the pins

void setup() {
  //Calibration of the sensor
  myservo.attach(servoPin);   //attaches the servo on pin 13 to the servo object
  //Setting the pin modes of the ultrasonic sensor
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  //setting the LCD's colums and rows (16 columns, 2 rows)
  lcd.begin(16, 2);
  //tell the user that we're calibrating the sensor
  lcd.print("calibrating");
  delay(1000); //remove when the calibration code is written!!!!
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
   ilmoitusLCD();

}

void servoMoottori(){
  for (servoPos = 0; servoPos <= 180; servoPos += 1) {  // goes from 0 degrees to 180 degrees
    myservo.write(servoPos);                           // tell servo to go to position in variable 'servoPos'
    delay(40);                                        // waits 40ms for the servo to reach the position
  }
  for (servoPos = 180; servoPos >= 0; servoPos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(servoPos);                          // tell servo to go to position in variable 'servoPos'
    delay(40);                                       // waits 40ms for the servo to reach the position
  }
}

int aaniTutka(){

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  //when distance is greater than or equal to 200 OR less than or equal to 0,LED is off
  if (distance >= 200 || distance <= 0) 
        {
        Serial.println("no object detected");
        }
  else {
        Serial.print("distance= ");              
        Serial.println(distance );        
  }
}

void ilmoitusSahkoposti(){
  
}

void ilmoitusLCD(){
  lcd.setCursor(0, 0); //sets cursor to the first row
  lcd.print("Distance:");
  lcd.setCursor(0, 1);
  lcd.print(distance); //prints etaisyys
  lcd.print(" m");
  
}
