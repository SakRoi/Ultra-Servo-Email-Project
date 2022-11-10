#define trigPin 12
#define echoPin 13
int ledPin= 6;  //Connect LEd pin to 6
int duration, distance; //to measure the distance and time taken 

void setup() {
        Serial.begin (9600); 
        //Define the output and input objects(devices)
        pinMode(trigPin, OUTPUT); 
        pinMode(echoPin, INPUT);
        pinMode(ledPin, OUTPUT);
}

void loop() {

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;
    //when distance is greater than or equal to 200 OR less than or equal to 0,LED is off
  if (distance >= 200 || distance <= 0) 
        {
        Serial.println("no object detected");
        digitalWrite(ledPin,LOW);
        }
  else {
        Serial.print("distance= ");              
        Serial.println(distance );        
        digitalWrite(ledPin,HIGH);
  }
}
