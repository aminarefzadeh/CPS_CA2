#include <Arduino.h>
#include <LiquidCrystal.h> // includes the LiquidCrystal Library
#include <SoftwareSerial.h>
#include <AltSoftSerial.h>


LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)

SoftwareSerial vSerial(12,13);
AltSoftSerial sensorSerial;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(20,4); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
  lcd.print("hello world");
  Serial.begin(9600);
  vSerial.begin(9600);
  sensorSerial.begin(9600);
}

  String tempr;
  String distance; 
  float casted_ut_data = 0;


void loop() {
  // put your main code here, to run repeatedly:
  // char ut_data_char[4];
  // float ut_data = *(float*)(&(ut_data_char));
  byte ut_data[4];
  // byte sensor_data_buff[10];
  String sensor_data;
  if(Serial.available()){
    Serial.readBytes(ut_data, 4);
    casted_ut_data = *(reinterpret_cast<float*>(&ut_data));
    // vSerial.println(casted);
  if(sensorSerial.available())
    sensor_data =  sensorSerial.readStringUntil('@');
    vSerial.println(sensor_data);
    tempr = sensor_data.substring(0, sensor_data.indexOf('$'));
    distance = sensor_data.substring(sensor_data.indexOf('$')+1);
    vSerial.print("temprature:");
    vSerial.println(tempr);
    vSerial.print("distance:");
    vSerial.println(distance);
    // sensor_data += *(reinterpret_cast<String*>(&sensor_data_buff));
    // vSerial.println(ut_data);
  }
  
  // vSerial.println(ut_data);
  lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
  lcd.print("Dist: "); // Prints string "Distance" on the LCD
  lcd.print(distance); // Prints the distance value from the sensor
  lcd.print(" cm");

  lcd.setCursor(0,1); // Sets the location at which subsequent text written to the LCD will be displayed
  lcd.print("Temp: "); // Prints string "Distance" on the LCD
  lcd.print(tempr); // Prints the distance value from the sensor
  lcd.print(" C");

  lcd.setCursor(0,2); // Sets the location at which subsequent text written to the LCD will be displayed
  lcd.print("UT: "); // Prints string "Distance" on the LCD
  lcd.print(casted_ut_data); // Prints the distance value from the sensor

}