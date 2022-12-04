#include <ESP8266WiFi.h>
WiFiClient client;

#define WIFI_SSID ""
#define WIFI_PASSWORD ""

int HTTP_PORT = 80;
String HTTP_METHOD = "GET";
char HOST_NAME[] = "maker.ifttt.com";
String PATH_NAME = "";

// const char* resource = "";
// const char* server = "maker.ifttt.com";

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(++i);
    Serial.println('\n');
  }
  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());

  client.println(HTTP_METHOD + " " + PATH_NAME + " HTTP/1.1");
  client.println("Host: " + String(HOST_NAME));
  client.println("Connection: close");
  client.println(); 

  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      Serial.print(c);
    }
  }
  client.stop();
  Serial.println();
  Serial.println("Disconnected");
  }


void loop() {
  // put your main code here, to run repeatedly:
  
  }