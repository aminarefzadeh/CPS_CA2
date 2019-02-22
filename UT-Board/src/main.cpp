#include <Arduino.h>
// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

const int device = 110;

int get_float(int);

void turn_on();

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  turn_on();
}

void loop() {
  double a = get_float(0x0a);
  double b = get_float(0x28);
  float x = *(float*)(& a);
  float y = *(float*)(& b);
  Serial.print("data is: ");
  Serial.print(a);
  Serial.print(", ");
  Serial.println(x);
  // Serial.print(send_req(0x0));
  delay(20);
}


int get_float(int base_addr){
  int i  = 0;
  int sum = 0;
  for (i=0;i<4;i++){
    delay(10);
    Wire.beginTransmission(device);
    Wire.write(base_addr+i);
    Wire.endTransmission();
    Wire.requestFrom(device, 1);    // request 6 bytes from slave device #8
    sum = (int)(Wire.read()) + (sum >> 8) ;
  }
  return sum;
}

void turn_on(){
  Wire.beginTransmission(device);
  Wire.write(0x00);
  Wire.write(0x01);
  Wire.endTransmission();
}