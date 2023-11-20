#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

// Authenticating network access
const char* ssid = "";
const char* password =  "";

// The IFTTT webhook with your key
String url = ""; 



void setup() {
  //connect to WiFi
  WiFi.begin(ssid, password);

  //setting up RX pin to be an GPIO pin, then setting it to be input
  pinMode(3, FUNCTION_3);
  pinMode(3, INPUT);
}


void loop() {  
  int input = digitalRead(3);
  if (input == HIGH) {      
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClientSecure client;
      client.setInsecure();
      HTTPClient https;
      if (https.begin(client, url)) {
        int httpCode = https.GET();
        https.end();
    }
  delay(2000);
  }
}
