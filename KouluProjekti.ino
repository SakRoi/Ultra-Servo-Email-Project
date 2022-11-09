Servo myservo;        //servo object to control a servo
int servoPos = 0;    //variable to store the servo position



void setup() {
  // put your setup code here, to run once:
  //tutkan kalibrointi
  myservo.attach(11);   //attaches the servo on pin 11 to the servo object

}

void loop() {
  // put your main code here, to run repeatedly:

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
  
}

void ilmoitusSahkoposti(){
  
}

void ilmoitusLCD(){
