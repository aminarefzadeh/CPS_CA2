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
Serial.print("distance is : ");
Serial.print(distance); // Prints the distance value from the sensor
Serial.println("");
Serial.print("temparator is : ");
Serial.println(Temp);
delay(1000);

}