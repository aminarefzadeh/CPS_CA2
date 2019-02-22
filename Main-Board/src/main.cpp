#include <Arduino.h>
#include <LiquidCrystal.h> // includes the LiquidCrystal Library

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)

void setup() {
  // put your setup code here, to run once:
  lcd.begin(20,4); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
  lcd.print("hello world");
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
  lcd.print("Distance: "); // Prints string "Distance" on the LCD
  lcd.print("10"); // Prints the distance value from the sensor
  lcd.print(" cm");
  delay(10);
}