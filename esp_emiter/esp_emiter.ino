#include <Arduino.h>

#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"

const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";

AsyncWebServer server(80);
long timer = 0;



void setup() {
  //Serial.begin(9600);
  Serial.begin(115200);

  WiFi.softAP(ssid,password);
  IPAddress IP = WiFi.softAPIP();

  server.on("/XAngle", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send_P(200, "text/plain", "11");
  });
  server.on("/YAngle", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send_P(200, "text/plain", "22");
  });
  server.on("/ZAngle", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send_P(200, "text/plain", "33");
  });

  server.begin();
}




void loop() {

}
