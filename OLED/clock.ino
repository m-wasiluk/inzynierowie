  #include <Time.h>
  #include <TimeLib.h>

  extern Adafruit_SSD1306 display;

  void digitalClockDisplay()
  {
    display.print(hour());
    printDigits(minute());
    printDigits(second());
    display.println();  
  }
  void printDigits(int digits)
  {
    display.print(":");
    if(digits < 10)
      display.print('0');
    display.print(digits);  
  }