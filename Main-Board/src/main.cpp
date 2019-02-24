#include <Arduino.h>
#include <LiquidCrystal.h> // includes the LiquidCrystal Library
#include <SoftwareSerial.h>
#include <AltSoftSerial.h>


LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
SoftwareSerial vSerial(12,13);
AltSoftSerial sensorSerial;   // Tx = 9 and Rx = 8

void setup() {
  // put your setup code here, to run once:
  lcd.begin(20,4); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
  Serial.begin(9600);   // serial user for bluetooth
  vSerial.begin(9600);  // for using virtual terminal and debuging
  sensorSerial.begin(9600); // used for connecting Sensor and Main board
}

  String tempr = "23";
  String distance = "40"; 
  float casted_ut_data = 0;


void loop() {
  byte ut_data[4];
  String sensor_data;
  if(Serial.available() >=4){
    Serial.readBytes(ut_data, 4);
    casted_ut_data = *(reinterpret_cast<float*>(ut_data));
  }
  if(sensorSerial.available()>=9){
    sensor_data =  sensorSerial.readStringUntil('@');
    vSerial.println(sensor_data);
    tempr = sensor_data.substring(0, sensor_data.indexOf('$'));
    distance = sensor_data.substring(sensor_data.indexOf('$')+1);
    vSerial.print("temprature:");
    vSerial.println(tempr);
    vSerial.print("distance:");
    vSerial.println(distance);
  }
  
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