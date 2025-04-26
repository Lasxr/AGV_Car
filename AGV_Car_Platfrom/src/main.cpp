#include <Arduino.h>

#define MR_IN1 12       // Back Right Motor
#define MR_IN2 13
#define MR_IN3 32     // Front Right Motor
#define MR_IN4 33       

#define ML_IN1 27   // Front Left Motor
#define ML_IN2 14
#define ML_IN3 25   // Back Left Motor
#define ML_IN4 26

// Motor Driver Pins
#define BR_ENA 15
#define FR_ENB 2
#define BL_ENB 4
#define FL_ENA 19



// Led Pins
int L_fornt_led = 16;
int R_fornt_led = 17;


// Motor Speed
uint8_t BR_Speed = 125; 
uint8_t BL_Speed = 125; 
uint8_t FR_Speed = 125; 
uint8_t FL_Speed = 125; 


// IR Sensor Pins
#define IR_LEFT 23
#define IR_RIGHT 34

void setup() {

  Serial.begin(9600);

  // Motor Pins
  pinMode(MR_IN1, OUTPUT);  // Back Right Motor
  pinMode(MR_IN2, OUTPUT); 
  pinMode(MR_IN3, OUTPUT);   // Front Right Motor
  pinMode(MR_IN4, OUTPUT);

  pinMode(ML_IN1, OUTPUT);  // Front Left Motor
  pinMode(ML_IN2, OUTPUT);
  pinMode(ML_IN3, OUTPUT);  // Back Left Motor
  pinMode(ML_IN4, OUTPUT);

  pinMode(BR_ENA, OUTPUT);
  pinMode(FR_ENB, OUTPUT);
  pinMode(BL_ENB, OUTPUT);
  pinMode(FL_ENA, OUTPUT);

  // Led On
  pinMode(L_fornt_led, OUTPUT);
  pinMode(R_fornt_led, OUTPUT);
  digitalWrite(L_fornt_led, HIGH);
  digitalWrite(R_fornt_led, HIGH);

  // IR Sensor Pins
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);


  analogWrite(BR_ENA, BR_Speed); // Back Right Motor
  analogWrite(FR_ENB, FR_Speed); // Front Right Motor
  analogWrite(BL_ENB, BL_Speed); // Back Left Motor
  analogWrite(FL_ENA, FL_Speed); // Front Left Motor

}

void Forward(int Delay) {

  digitalWrite(MR_IN1, HIGH);  // Back Right Motor
  digitalWrite(MR_IN2, LOW);
  digitalWrite(MR_IN3, HIGH);   // Front Right Motor
  digitalWrite(MR_IN4, LOW);

  digitalWrite(ML_IN1, HIGH);  // Front Left Motor
  digitalWrite(ML_IN2, LOW);
  digitalWrite(ML_IN3, HIGH);  // Back Left Motor
  digitalWrite(ML_IN4, LOW);

  delay(Delay);
}

void Backward(int Delay) {
  digitalWrite(MR_IN1, LOW);  // Back Right Motor
  digitalWrite(MR_IN2, HIGH);
  digitalWrite(MR_IN3, LOW);   // Front Right Motor
  digitalWrite(MR_IN4, HIGH);

  digitalWrite(ML_IN1, LOW);  // Front Left Motor
  digitalWrite(ML_IN2, HIGH);
  digitalWrite(ML_IN3, LOW);  // Back Left Motor
  digitalWrite(ML_IN4, HIGH);

  delay(Delay);
}

void Left(int Delay) {
  digitalWrite(MR_IN1, LOW);  // Back Right Motor
  digitalWrite(MR_IN2, HIGH);
  digitalWrite(MR_IN3, HIGH);   // Front Right Motor
  digitalWrite(MR_IN4, LOW);

  digitalWrite(ML_IN1, LOW);  // Front Left Motor
  digitalWrite(ML_IN2, HIGH);
  digitalWrite(ML_IN3, HIGH);  // Back Left Motor
  digitalWrite(ML_IN4, LOW);

  delay(Delay);
}

void Right(int Delay) {
  digitalWrite(MR_IN1, HIGH);  // Back Right Motor
  digitalWrite(MR_IN2, LOW);
  digitalWrite(MR_IN3, LOW);   // Front Right Motor
  digitalWrite(MR_IN4, HIGH);

  digitalWrite(ML_IN1, HIGH);  // Front Left Motor
  digitalWrite(ML_IN2, LOW);
  digitalWrite(ML_IN3, LOW);  // Back Left Motor
  digitalWrite(ML_IN4, HIGH);

  delay(Delay);
}

void Stop(int Delay) {
  digitalWrite(MR_IN1, LOW);  // Back Right Motor
  digitalWrite(MR_IN2, LOW);
  digitalWrite(MR_IN3, LOW);   // Front Right Motor
  digitalWrite(MR_IN4, LOW);

  digitalWrite(ML_IN1, LOW);  // Front Left Motor
  digitalWrite(ML_IN2, LOW);
  digitalWrite(ML_IN3, LOW);  // Back Left Motor
  digitalWrite(ML_IN4, LOW);

  delay(Delay);
}

void BackLeft(int Delay) {
  digitalWrite(MR_IN1, LOW);  // Back Right Motor
  digitalWrite(MR_IN2, HIGH);
  digitalWrite(MR_IN3, LOW);   // Front Right Motor
  digitalWrite(MR_IN4, LOW);

  digitalWrite(ML_IN1, LOW);  // Front Left Motor
  digitalWrite(ML_IN2, HIGH);
  digitalWrite(ML_IN3, LOW);  // Back Left Motor
  digitalWrite(ML_IN4, LOW);

  delay(Delay);
}

void BackRight(int Delay) {
  digitalWrite(MR_IN1, LOW);  // Back Right Motor
  digitalWrite(MR_IN2, LOW);
  digitalWrite(MR_IN3, LOW);   // Front Right Motor
  digitalWrite(MR_IN4, HIGH);

  digitalWrite(ML_IN1, LOW);  // Front Left Motor
  digitalWrite(ML_IN2, LOW);
  digitalWrite(ML_IN3, LOW);  // Back Left Motor
  digitalWrite(ML_IN4, HIGH);

  delay(Delay);
}

void ForwardLeft(int Delay) {
  digitalWrite(MR_IN1, LOW);  // Back Right Motor
  digitalWrite(MR_IN2, LOW);
  digitalWrite(MR_IN3, HIGH);   // Front Right Motor
  digitalWrite(MR_IN4, LOW);

  digitalWrite(ML_IN1, LOW);  // Front Left Motor
  digitalWrite(ML_IN2, LOW);
  digitalWrite(ML_IN3, HIGH);  // Back Left Motor
  digitalWrite(ML_IN4, LOW);

  delay(Delay);
}

void ForwardRight(int Delay) {
  digitalWrite(MR_IN1, HIGH);  // Back Right Motor
  digitalWrite(MR_IN2, LOW);
  digitalWrite(MR_IN3, LOW);   // Front Right Motor
  digitalWrite(MR_IN4, LOW);

  digitalWrite(ML_IN1, HIGH);  // Front Left Motor
  digitalWrite(ML_IN2, LOW);
  digitalWrite(ML_IN3, LOW);  // Back Left Motor
  digitalWrite(ML_IN4, LOW);

  delay(Delay);
}

void RotateLeft(int Delay) {
  digitalWrite(MR_IN1, HIGH);  // Back Right Motor
  digitalWrite(MR_IN2, LOW);
  digitalWrite(MR_IN3, HIGH);   // Front Right Motor
  digitalWrite(MR_IN4, LOW);

  digitalWrite(ML_IN1, LOW);  // Front Left Motor
  digitalWrite(ML_IN2, HIGH);
  digitalWrite(ML_IN3, LOW);  // Back Left Motor
  digitalWrite(ML_IN4, HIGH);

  delay(Delay);
}

void RotateRight(int Delay) {
  digitalWrite(MR_IN1, LOW);  // Back Right Motor
  digitalWrite(MR_IN2, HIGH);
  digitalWrite(MR_IN3, LOW);   // Front Right Motor
  digitalWrite(MR_IN4, HIGH);

  digitalWrite(ML_IN1, HIGH);  // Front Left Motor
  digitalWrite(ML_IN2, LOW);
  digitalWrite(ML_IN3, HIGH);  // Back Left Motor
  digitalWrite(ML_IN4, LOW);

  delay(Delay);
}

void Check_Car() {
  Forward(1000);
  Stop(1000);
  Backward(1000);
  Stop(1000);
  Left(1000);
  Stop(1000);
  Right(1000);
  Stop(1000);
  BackLeft(1000);
  Stop(1000);
  BackRight(1000);
  Stop(1000);
  ForwardLeft(1000);
  Stop(1000);
  ForwardRight(1000);
  Stop(1000);
  RotateLeft(1000);
  Stop(1000);
  RotateRight(1000);
  Stop(1000);
}

void read_ir() {
  while (1) {
    Serial.print(" Right Sensor value: ");
    Serial.print(digitalRead(IR_RIGHT));
    ///////////////////////////////////////////
    Serial.print("      Left Sensor value: ");
    Serial.println(digitalRead(IR_LEFT));
    delay(100);
  }
}


void loop() {
  read_ir();
}