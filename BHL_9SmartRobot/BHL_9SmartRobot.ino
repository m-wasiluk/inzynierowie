#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"

const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";

#define TOUCH_SENSOR 4
#define JOYSTICK_BUTTON 5
#define MULTIPLEXER 16

AsyncWebServer server(80);

// Global variables to hold joystick and button values
int globalX = 0;
int globalY = 0;
int globalButtonState = 0;

void setup() {
  pinMode(TOUCH_SENSOR, INPUT);
  pinMode(JOYSTICK_BUTTON, INPUT_PULLUP);
  pinMode(MULTIPLEXER, OUTPUT);
  Serial.begin(9600);
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();

  // Setup server routes
  server.on("/XAngle", HTTP_GET, [](AsyncWebServerRequest *request) {
    String response = String(globalX);
    request->send(200, "text/plain", response);
  });

  server.on("/YAngle", HTTP_GET, [](AsyncWebServerRequest *request) {
    String response = String(globalY);
    request->send(200, "text/plain", response);
  });

  server.on("/ButtonState", HTTP_GET, [](AsyncWebServerRequest *request) {
    String response = String(globalButtonState);
    request->send(200, "text/plain", response);
  });

  server.begin();
}

void readJoystickAndButton() {
  digitalWrite(MULTIPLEXER, HIGH);
  globalX = analogRead(A0);
  digitalWrite(MULTIPLEXER, LOW);
  globalY = analogRead(A0);
  globalButtonState = !digitalRead(JOYSTICK_BUTTON);
}

void loop() {
  // Periodic read of joystick and button
  readJoystickAndButton();
  Serial.print("X: ");
  Serial.print(globalX);
  Serial.print(", Y: ");
  Serial.print(globalY);
  Serial.print(", Button: ");
  Serial.println(globalButtonState);
  
  delay(2000); // Adjust delay as needed
}