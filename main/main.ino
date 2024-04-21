#include <Time.h>
#include <TimeLib.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "OLED.h"
#include <dht.h>
#include "images.h"
#include "messages.h"
#include <pitches.h>
#include "motor_driver.h"

#define BUZZER_PIN 9

  #define FORWARDS  0
  #define BACKWARDS 1
  #define RIGHT     0
  #define LEFT      1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
dht DHT;

void setup()
{
  pinMode( 13, OUTPUT );
  digitalWrite( 13, 1 );
  Serial.begin(9600);
  Serial.println("1");
  OLED_setup();
  Serial.println("2");
  setTime(13,0,0,1,1,20);
  buzzer();
    //przypisanie stanów do stron ruchu platformy


  //inicjalizacja modułów
  //CENG_init();
 // CENG_setEngines( 100, 0, 100, 0 );
}

void loop()
{
  Serial.println("3");
  for(int i = 0; i < 100; i++)
    display_clock();
  Serial.println("4");
  for(int i = 0; i < 7; i++) { 
    display_image(images_allArray[i]);
    display_text(messages[i]);
    delay(5000); 
  }
}

  int melody[] = {
  REST, NOTE_D4,
  NOTE_G4, NOTE_AS4, NOTE_A4,
  NOTE_G4, NOTE_D5,
  NOTE_C5, 
  NOTE_A4,
  NOTE_G4, NOTE_AS4, NOTE_A4,
  NOTE_F4, NOTE_GS4,
  NOTE_D4, 
  NOTE_D4,
  
  NOTE_G4, NOTE_AS4, NOTE_A4,
  NOTE_G4, NOTE_D5,
  NOTE_F5, NOTE_E5,
  NOTE_DS5, NOTE_B4,
  NOTE_DS5, NOTE_D5, NOTE_CS5,
  NOTE_CS4, NOTE_B4,
  NOTE_G4,
};

int durations[] = {
  2, 4,
  4, 8, 4,
  2, 4,
  2, 
  2,
  4, 8, 4,
  2, 4,
  1, 
  4,
  
  4, 8, 4,
  2, 4,
  2, 4,
  2, 4,
  4, 8, 4,
  2, 4,
  1,
};


void buzzer() {
    int size = sizeof(durations) / sizeof(int);

  for (int note = 0; note < size; note++) {
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 1000 / durations[note];
    tone(BUZZER_PIN, melody[note], duration);

    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    
    //stop the tone playing:
    noTone(BUZZER_PIN);
  }
}
