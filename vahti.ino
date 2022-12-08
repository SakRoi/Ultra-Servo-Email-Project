/* This school project was made by:
    Saku Roininen - LCD screen
    Santtu Niskanen - ESP3866 connection and email
    Joonas Ridanpää - Ultrasonic sensor
    Lauri Tuovinen - Servo Motor
*/


#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 6
#define SS_PIN 53

byte readCard[4];
String MasterTag = "51F95027"; 
String tagID = "";
MFRC522 mfrc522(SS_PIN, RST_PIN);

#include <LiquidCrystal.h>
#include <Servo.h>
Servo myservo;        //servo object to control a servo
bool rotation = true; //this is used to check, if the servo is rotatin to or from 180 degrees. true = 0 -> 180 and false 180 -> 0
int calibratedDistance[13] = {0};
int distance = 0;
int servoPos = 0;    //variable to store the servo position
int arrayPos = 0;     //arrayPos to circumvent the problem created by dividing servoPos by 15
long newTime = 0;
long oldTime = 60000; 


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2, servoPin = 13, trigPin = 10, echoPin = 9, ESPPin = 8; //Reserving digital pins 2-7 for lcd, pin 13 for servo, pin 8 for ESP3866 and pins 10-9 for ultrasonic sensor
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //intializing the LiquidCrystal library by associating the pins

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  //attaches the servo on pin 13 to the servo object
  myservo.attach(servoPin);
  //Setting the pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ESPPin, OUTPUT);
  
  //setting the LCD's colums and rows (16 columns, 2 rows)
  lcd.begin(16, 2);
  lcd.print("calibrating");
  
  //calibrating the sensor
  myservo.write(servoPos);
  calibration();
  Serial.print("calibration for 12th element in array (setup) ");
  Serial.println(calibratedDistance[12]);
  lcd.clear();
  
  //telling the user that calibration is done
  lcd.print("calibration");
  lcd.setCursor(0, 1);
  lcd.print("is done");
  delay(500);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  while (getID()==false)
  {  
	  aaniTutka();
	  servoMoottori();
	  arrayPosition();
	  scanCompare();
  }
  Serial.print(" ID : ");
  Serial.println(tagID);
  while(getID()==false)
  {
    Serial.println("Keskeytetty");
  }
	delay(500);
}

void arrayPosition() {
  if (rotation)
  {
    arrayPos +=1;
  }
  else
  {
    arrayPos -= 1;
  }
}

void servoMoottori() {
  if (rotation)
  {
    servoPos += 15;
    myservo.write(servoPos);
    if (servoPos == 180)
    {
      rotation = false;
    }
  }
  else
  {
    servoPos -= 15;
    myservo.write(servoPos);
    if (servoPos == 0)
    {
      rotation = true;
    }
  }
  delay(500);
}

int aaniTutka() {
  distance = 0;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int duration = pulseIn(echoPin, HIGH);
  distance = (duration / 58);
  
  if (distance >= 400 || distance <= 0)
  {
    Serial.println("no object detected");
  }
  else
  {
//    Serial.print("distance= ");
//    Serial.println(distance );
  }
  
  delay(200);
  return distance;
}

void ilmoitusSahkoposti() {
  Serial.println("ILMOITUSSÄHKÖPOSTISSA");
  digitalWrite(ESPPin, HIGH);
  delay(1000);
  digitalWrite(ESPPin, LOW);
}

void ilmoitusLCD() {
  lcd.clear();
  lcd.setCursor(0, 0); //sets cursor to the first row
  lcd.print("Distance:");
  lcd.setCursor(0, 1);
  //400 is the maximum distance of the ultrasonic
  if (distance > 400)
  {
    lcd.print("400+ cm");
  }
  else {
    lcd.print(distance); //prints distance
    lcd.print( "cm");
  }
}

void calibration() {
  arrayPos = 11;
  int index = 0;
  while (index < 13){
    calibratedDistance[index] = aaniTutka();
    Serial.print("index ");
    Serial.println(index);
    Serial.print("servo Position ");
    Serial.println(servoPos);
    
    if (index < 12) {
      servoMoottori();
    }
    
    index++;
    delay(500);
  }
}

void scanCompare() {
  if ((calibratedDistance[arrayPos]<=(distance+2))&(calibratedDistance[arrayPos]>=(distance-2)))
  {
    Serial.println("Täsmää");
    Serial.print("arrayPos: ");
    Serial.println(arrayPos);
  }
  else
  {
//    Serial.print("distance from scancompare: ");
//    Serial.println(distance);
//    Serial.print("distance from calibratedDistance: ");
//    Serial.println(calibratedDistance[arrayPos]);
    Serial.println("Ei Täsmää");
    Serial.print("arrayPos: ");
    Serial.println(arrayPos);
    Serial.print("distance from calibratedDistance: ");
    Serial.println(calibratedDistance[arrayPos]);
    emailSendTimer();
    //ilmoitusSahkoposti();
  }

}


void emailSendTimer(){
    Serial.println("EMAILSENDTIMERISSÄ");
    newTime = millis();
        if(oldTime - newTime < 0){
            oldTime = newTime + 60000;
            Serial.println(oldTime);
            ilmoitusSahkoposti();
  }
}

//Read new tag if available
boolean getID() 
{
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
  return false;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
  return false;
  }
  tagID = "";
  for ( uint8_t i = 0; i < 4; i++) { // The MIFARE PICCs that we use have 4 byte UID
  //readCard[i] = mfrc522.uid.uidByte[i];
  tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); // Adds the 4 bytes in a single String variable
  }
  tagID.toUpperCase();
  mfrc522.PICC_HaltA(); // Stop reading
  if (tagID == MasterTag) 
  {
    return true;
  }
  else
  {
    return false;
  }
}
