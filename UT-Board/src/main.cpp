#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

const int device = 110;
SoftwareSerial vSerial(12, 13);
float sigma = 0;
float get_float(int);

void turn_on();

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  vSerial.begin(9600);
  turn_on();
}

void loop() {
  float x = get_float(0x0a);
  float y = get_float(0x28);
  sigma += (float)(pow(x, 2) + pow(y, 2));
  vSerial.println(sigma);
  byte* casted = reinterpret_cast <byte*>(&sigma);
  Serial.write(casted, 4);
  delay(100);
}


float get_float(int base_addr){
  int i  = 0;
  byte result[4];
  for (i=0;i<4;i++){
    Wire.beginTransmission(device);
    Wire.write(base_addr+i);
    Wire.endTransmission();
    Wire.requestFrom(device, 1);    // request 6 bytes from slave device #8
    result[i] = Wire.read();
  }
  return *(float*)(result);
}

void turn_on(){
  Wire.beginTransmission(device);
  Wire.write(0x00);
  Wire.write(0x01);
  Wire.endTransmission();
}