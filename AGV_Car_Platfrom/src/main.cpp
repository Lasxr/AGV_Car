#include <Arduino.h>

int FF = 12;

void setup() {

  Serial.begin(9600);

  pinMode(2, OUTPUT);
}

void loop() {

  digitalWrite(2, HIGH);
  delay(1000); 
  digitalWrite(2, LOW);  
  delay(1000);
}