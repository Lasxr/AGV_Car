#include <Arduino.h>
#include <Wifi.h>
#include <PubSubClient.h>


//-----Wifi-----
WiFiClient wifiClient;
PubSubClient mqttclient(wifiClient);
const char *ssid = "Atsc-2.4G"; 
const char *password = "1245@atsc"; 
const char *mqtt_broker = "192.168.100.8"; 
const char *topic = "AGV/MQTTX/01"; 
const int mqttPort = 1883;
const char *mqtt_client_id = "Inwza007";


String data_in;

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

//Buzzer
int Buzzer = 18;

// Motor Speed
uint8_t BR_Speed = 125; 
uint8_t BL_Speed = 95; 
uint8_t FR_Speed = 125; 
uint8_t FL_Speed = 95; 


// IR Sensor Pins
#define IR_LEFT 35
#define IR_RIGHT 34                                                                                                                                                                                                                                                                                      
bool ir_L, ir_R;

void callback(char *topic, byte *payload, unsigned int length);


void mqtt_setup() {
  Serial.println("Connecting WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  Serial.println("Connecting MQTT");
  mqttclient.setServer(mqtt_broker, mqttPort);
  mqttclient.setCallback(callback);

  while (!mqttclient.connected()) {
    Serial.printf("The client %s connects to the MQTT broker\n", mqtt_client_id);
    if (mqttclient.connect(mqtt_client_id)) {
      Serial.println("MQTT connected");
    } else {
      Serial.print("failed with state ");
      Serial.println(mqttclient.state());
      delay(2000);
    }
  }
  mqttclient.subscribe(topic);
}

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

  //Buzzer
  pinMode(Buzzer, OUTPUT);

  analogWrite(BR_ENA, BR_Speed); // Back Right Motor
  analogWrite(FR_ENB, FR_Speed); // Front Right Motor
  analogWrite(BL_ENB, BL_Speed); // Back Left Motor
  analogWrite(FL_ENA, FL_Speed); // Front Left Motor

  digitalWrite(Buzzer, 1);
  delay(100);
  digitalWrite(Buzzer, 0);
  delay(100);
  digitalWrite(Buzzer, 1);
  delay(100);
  digitalWrite(Buzzer, 0);

  mqtt_setup();
  
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

void StopCar(int Delay) {
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

void TurnLeft(int Delay) {
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

void TurnRight(int Delay) {
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

void Beep(int Round, int Delay){ 
  for (int  i = 0; i < Round; i++)
  {
    digitalWrite(Buzzer, 1);
    delay(Delay);
    digitalWrite(Buzzer, 0);
    delay(Delay);

  }
  
}

void Check_Car() {
  Forward(1000);
  StopCar(1000);
  Backward(1000);
  StopCar(1000);
  Left(1000);
  StopCar(1000);
  Right(1000);
  StopCar(1000);
  BackLeft(1000);
  StopCar(1000);
  BackRight(1000);
  StopCar(1000);
  ForwardLeft(1000);
  StopCar(1000);
  ForwardRight(1000);
  StopCar(1000);
  TurnLeft(1000);
  StopCar(1000);
  TurnRight(1000);
  StopCar(1000);
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

void val_IR(){
  ir_L = digitalRead(IR_LEFT);
  ir_R = digitalRead(IR_RIGHT);
}

void check_command(char x){
  switch (x) {
    case 'f':
      Serial.println("Go forward");
      Forward(100);
      break;
    case 'b':
      Serial.println("Go backward");
      Backward(100);
      break;
    case 'l':
      Serial.println("Turn left");
      Left(100);
      break;
    case 'r':
      Serial.println("Turn right");
      Right(100);
      break;
    case 's':
      Serial.println("Stop");
      StopCar(100);
      break;
    default:
      Serial.println("Unknown command");
  }
}

void callback(char *topic, byte *payload, unsigned int length) {
  payload[length] = '\0';
  String topic_str = topic;
  String payload_str = (char *)payload;
  data_in = payload_str;
  Serial.println(data_in);
  if (data_in.length() > 0) {
    data_in.trim();
    int count = data_in.length();
    for (int i = 0; i < count; i++) {
      check_command(data_in[i]);
    }
    StopCar(0);
  }
}

void mqtt_run() {
  mqttclient.loop();
}

void Trackline(){
  while (1)
  {
    val_IR();
    if(ir_L == 1 && ir_R == 1){
      StopCar(0);
      break;
    }else if(ir_L == 0 && ir_R == 0){
      Forward(0);
    }else if(ir_L == 1 && ir_R == 0){
      TurnLeft(0);
    }else if(ir_L == 0 && ir_R == 1){
      TurnRight(0);
    }
  }
  StopCar(0);
}

void Forward_cross(int time){
  while (1)
  {
    Forward(0);
    delay(time);
    StopCar(0);
    break;
  }
  StopCar(0);
}

void Back_cross(int time){
  while (1)
  {
    Backward(0);
    delay(time);
    StopCar(0);
    break;
  }
  StopCar(0);
}

void Track_forward() {
  while (1)
  {
    val_IR();
    if(ir_L == 1 && ir_R == 1){
      StopCar(0);
      break;
    }else if(ir_L == 0 && ir_R == 0){
      Forward(0);
    }else if(ir_L == 1 && ir_R == 0){
      TurnRight(0);
    }else if(ir_L == 0 && ir_R == 1){
      TurnLeft(0);
    }
  }
  StopCar(0);
}

void Track_backward() {
  while (1)
  {
    val_IR();
    if(ir_L == 1 && ir_R == 1){
      StopCar(0);
      break;
    }else if(ir_L == 0 && ir_R == 0){
      Backward(0);
    }else if(ir_L == 1 && ir_R == 0){
      TurnRight(0);
    }else if(ir_L == 0 && ir_R == 1){
      TurnLeft(0);
    }
  }
  StopCar(0);
}

void Track_left(int time){
  TurnLeft(0);
  delay(time);
  StopCar(0);
}

void Track_right(int time){
  TurnRight(0);
  delay(time);
  StopCar(0);
}

void To_Line() {
  while (1)
  {
    val_IR();
    if(ir_L == 1 && ir_R == 1){
      StopCar(0);
      break;
    }else if(ir_L == 0 && ir_R == 0){
      Forward(0);
    }else if(ir_L == 1 && ir_R == 0){
      TurnLeft(0);
    }else if(ir_L == 0 && ir_R == 1){
      TurnRight(0);
    }
  }
  StopCar(0);
}

void End_proses(){
  while (1)
  {
    StopCar(0);
  }
  
}

void loop()
{
  Track_forward();
  Beep(2, 100);
  Forward_cross(500);
  Beep(2, 100);
  Track_forward();
  Beep(2, 100);
  Forward_cross(1000);
  Beep(2, 100);
  Track_left(750);
  Beep(2, 100);
  To_Line();
  Beep(2, 100);
  Forward_cross(1000);
  Beep(2, 100);
  Track_forward();
  Beep(2, 100);
  Forward_cross(1000);
  Beep(2, 100);
  Track_right(750);
  Beep(2, 100);
  To_Line();
  Beep(3, 100);
  End_proses();

}