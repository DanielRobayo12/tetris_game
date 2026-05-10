#include <Arduino.h>

const int READ = A0;


void setup(){
    Serial.begin(9600);

    pinMode(READ, INPUT);

}

void loop(){
    int data = 0;

    data = analogRead(READ);
    Serial.println("\n-----------");
    Serial.print("Data: ");
    Serial.print(data);


}