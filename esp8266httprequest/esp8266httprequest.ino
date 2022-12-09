#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

// Authenticating network access
const char* ssid = "";
const char* password =  "";

// The IFTTT webhook with your key
String url = ""; 



void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    // If WiFi has not been connected
    // Dots will be printed to serial
    delay(500);
    Serial.print(".");
  }

  // Once connection has been established,
  // You will be greeted with a message
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);

  // Can be removed if you want your IP hidden
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop() {  
    int input = digitalRead(2);
    if (input == HIGH) {      
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClientSecure client;
      client.setInsecure();
      
      HTTPClient https;
      Serial.println("Requesting " + url);
      if (https.begin(client, url)) {
        int httpCode = https.GET();
        Serial.println("============== Response code: " + String(httpCode));
        if (httpCode > 0) {
          Serial.println(https.getString());
        }
        https.end();
      } else {
        Serial.printf("[HTTPS] Unable to connect\n");
      }
    }
    delay(2000);
  }
}