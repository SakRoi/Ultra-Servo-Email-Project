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
const int rs = 12, en =11, d4 = 5, d5 = 4, d6 = 3, d7 = 2, servoPin = 13, trigPin = 10, echoPin = 9, ESPPin = 8; //Reserving digital pins 2-7 for lcd, pin 13 for servo, pin 8 for ESP3866 and pins 10-9 for ultrasonic sensor

LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //intializing the LiquidCrystal library by associating the pins

void setup() {
  Serial.begin(9600);
  //attaches the servo on pin 13 to the servo object
  myservo.attach(servoPin);   
  //Setting the pin modes of the ultrasonic sensor
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  //Setting the pin modes for the ESP3886
  pinMode(ESPPin, OUTPUT);
  //setting the LCD's colums and rows (16 columns, 2 rows)
  lcd.begin(16, 2);
  lcd.print("calibrating");
  //calibrating the sensor
  myservo.write(servoPos);
  calibration();
  lcd.clear();
  //telling the user that calibration is done
  lcd.print("calibration");
  lcd.setCursor(0, 1);
  lcd.print("is done");
  delay(1000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
   aaniTutka();
   servoMoottori();
   scanCompare();
   ilmoitusLCD();

}

void servoMoottori(){
  if(rotation = true)
  {
    servoPos += 15;
    myservo.write(servoPos); 
      if(servoPos >= 180)
      {
        Serial.write("turning");
        rotation = false;
        servoPos = 180;
      }
  }
  else
  {
    servoPos -= 15;
    myservo.write(servoPos);
      if(servoPos <= 0)
      {
        Serial.write("turning");
        rotation = true;
        servoPos = 0;
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
    }
    delay(200);
    return distance;
}

void ilmoitusSahkoposti(){
  Serial.println("Email Send!");
  delay(500);
  /*digitalWrite(ESPPin, HIGH);
  delay(1000);
  digitalWrite(ESPPin, LOW);*/
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
}

void calibration(){
  
  for (int index = 0; index < 13; index++){
    calibratedDistance[index]=aaniTutka();
    if (index < 12){
      servoMoottori();
    }
    delay(2000);
      Serial.println("index");
      Serial.println(index);
      Serial.println("calibration");
      Serial.println(calibratedDistance[index]);
      Serial.println("servo Position");
      Serial.println(servoPos);    
  }
 }

void scanCompare(){
  delay(1000);
  int x = servoPos/15; 
    if (calibratedDistance[x] != distance && calibratedDistance[x] != (distance + 1) or (distance - 1)){
      Serial.print("Calibrated value in this index ");
      Serial.println(calibratedDistance[x]);
      Serial.println(x);
      Serial.println(servoPos);
      Serial.print("Current distance ");
      Serial.println(distance);
      delay(1000);
      ilmoitusSahkoposti();
    }
    else{
    }
}
