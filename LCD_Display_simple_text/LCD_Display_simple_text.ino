#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  display.clearDisplay();
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Hello world!");
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.println("Second line");
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(60, 40);
  display.println("------>");
  
  display.display();
  delay(500);
}

void loop() {
  // Moving text effect for the second line

  static int pos = 0;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(pos, 20);
  display.println("Second line");
  display.display();
  
  pos++;
  if (pos > SCREEN_WIDTH) {
    pos = 0;
  }
  
  delay(5);
}