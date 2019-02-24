#include <Arduino.h>
#include <Ultrasonic.h>



const int trigPin = 9;
const int echoPin = 10;

const int LM35 = A0;

Ultrasonic ultrasonic(trigPin,echoPin);

void setup() {
    pinMode(LM35,INPUT);
    Serial.begin(9600);
}

void loop() {
float Temp = (analogRead(LM35)/1024.0)*500;
int distance = ultrasonic.read(CM);
String res = String(Temp) + "$" + String(distance) + "@";
Serial.print(res);
delay(100);
}