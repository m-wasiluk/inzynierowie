#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <dht.h>
#include "OLED.h"

extern Adafruit_SSD1306 display;
extern dht DHT;

void OLED_setup() {
  Serial.println("1.0");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Serial.println("1.1");
  display.display();
  Serial.println("1.2");
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
}

// display clock with temp and humidity
void display_clock() {
  int temp_hum = DHT.read11(DHTPIN); // Read data from the DHT11 sensor

  display.clearDisplay();
  display.drawRect(0, 0, SCREEN_WIDTH, 25, SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(15, 5);
  digitalClockDisplay();
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("Temp: ");
  display.setTextSize(2);
  display.setCursor(50, 30);
  display.print((float)DHT.temperature);
  display.setTextSize(1);
  display.setCursor(110, 35);
  display.println(" oC");
  display.setCursor(0, 55);
  display.print("Wilgot:    ");
  display.setTextSize(2);
  display.setCursor(50, 50);
  display.print((float)DHT.humidity);
  display.setCursor(110, 55);
  display.setTextSize(1);
  display.println(" %");
  display.display();
}

void display_image(const unsigned char * image) {
  display.clearDisplay();
  display.drawBitmap(0, 0, image, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
  display.display();
}

void display_text(const char* message) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println(message);
  display.display();
}
