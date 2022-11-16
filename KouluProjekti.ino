/* This school project was made by:
 *  Saku Roininen - LCD screen
 *  Santtu Niskanen - ESP3866 connection and email
 *  Joonas Ridanpää - Ultrasonic sensor
 *  Lauri Tuovinen - Servo Motor
*/


#include <LiquidCrystal.h>
#include <Servo.h>
Servo myservo;        //servo object to control a servo
bool rotation = true; //this is used to check, if the servo is rotatin to or from 180 degrees. true = 0 -> 180 and false 180 -> 0
int calibratedDistance [12];
int distance = 0;
int servoPos = 0;    //variable to store the servo position
const int rs = 12, en =11, d4 = 5, d5 = 4, d6 = 3, d7 = 2, servoPin = 13, trigPin = 10, echoPin = 9; //Reserving digital pins 2-7 for lcd, pin 13 for servo and pins 10-9 for ultrasonic sensor
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //intializing the LiquidCrystal library by associating the pins

void setup() {
  Serial.begin(9600);
  //Calibration of the sensor
  //attaches the servo on pin 13 to the servo object
  myservo.attach(servoPin);   
  //Setting the pin modes of the ultrasonic sensor
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  //setting the LCD's colums and rows (16 columns, 2 rows)
  lcd.begin(16, 2);
  //tell the user that we're calibrating the sensor
  lcd.print("calibrating");
  calibration();
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
   aaniTutka();
   servoMoottori();
   ilmoitusLCD();

}

void servoMoottori(){
  if(rotation)
  {
    servoPos += 15;
    myservo.write(servoPos); 
      if(servoPos == 180)
      {
        rotation = false;
      }
  }
  else
  {
    servoPos -= 15;
    myservo.write(servoPos);
      if(servoPos == 0)
      {
        rotation = true;
      }
    }
  }

int aaniTutka(){
    distance = 0;
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    int duration = pulseIn(echoPin, HIGH);
    distance = (duration/58);
  if (distance >= 400 || distance <= 0) 
    {
        Serial.println("no object detected");
    }
  else 
    {
        Serial.print("distance= ");              
        Serial.println(distance );
        return distance;        
    }
  return distance = 15;
}

void ilmoitusSahkoposti(){
  
}

void ilmoitusLCD(){
  lcd.clear();
  lcd.setCursor(0, 0); //sets cursor to the first row
  lcd.print("Distance:");
  lcd.setCursor(0, 1);
  //400 is the maximum distance of the ultrasonic
  if (distance > 400)
  {
    lcd.print("400+ cm");
  }
  else{
   lcd.print(distance); //prints etaisyys
   lcd.print( "cm"); 
  }
  //if (calibrated[x] != distance && calibrated[x] != (distance + 1 || distance - 1)
}

void calibration(){
  for (int index = 0; index < 13; index++){
    calibratedDistance[index]=aaniTutka;
    if (index < 12){
      servoMoottori();
    }
    Serial.println("index");
    Serial.println(index);
    Serial.println("servo Position");
    Serial.println(servoPos);
  }
 }

// void scanCompare(){
//  int index = 0;
//  if (servoPos == 0){
//   if (calibratedDistance[0] != distance && calibratedDistance[0] != (distance + 1 || distance - 1)
//   {
//    
//   }
//  }
// }
