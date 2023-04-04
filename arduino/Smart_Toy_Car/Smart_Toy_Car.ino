/*
 connections to be made 
 ultrasonic sensor d18 for echo and trig on d4
 motor drive in3 an in4 on d22 and d23
 motor drive in1 an in2 on d19 and d21
*/
#include <WiFi.h>
#include <WiFiClient.h> // to be able to connect to connect to hotspot
#include <WebServer.h> // to make a server in arduino
#include <HTTPClient.h> // to be abkle to make https requests to and from client (POST, GET, PUT, DELETE)

//pins to drive motors
int MotorLeft[2] = { 19, 21 };
int MotorRight[2] = { 22, 23 };
#define PIN_ENA_RIGHT 14
#define PIN_ENA_LEFT 27

// variables for connecting to hotspot
char ssid[] = "tatendaZw";
char pass[] = "12345677";
IPAddress ip;

int currentSpeed;
char direction[] = "";

// function to connect eps32 to hotspot
void connect_to_hotspot() {
  WiFi.begin(ssid, pass);  //Connect to WiFi

  // run loop below while trying to connect to hotspot
  Serial.print("Connecting.");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("IP address: ");
  ip = WiFi.localIP();
  Serial.println(WiFi.localIP());
}


void setup() {
  Serial.begin(9600);

  // connect to hotspot
  connect_to_hotspot();
  // put your setup code here, to run once:
  pinMode(PIN_ENA_RIGHT, OUTPUT);
  pinMode(PIN_ENA_LEFT, OUTPUT);
  pinMode(MotorLeft[2], OUTPUT);
  pinMode(MotorRight[2], OUTPUT);
  MotorInit();
}

void loop() {
  // put your main code here, to run repeatedly:
  Robot_Forward();
  delay(4000);
  Robot_Stop();
  delay(1000);
  Robot_Backward();
  delay(4000);
  Robot_Stop();
  delay(5000);
}


void Robot_Backward() {
  // direction = "backwards";
  digitalWrite(MotorLeft[0], 0);
  digitalWrite(MotorLeft[1], 1);
  digitalWrite(MotorRight[0], 1);
  digitalWrite(MotorRight[1], 0);
  for (int speed = 0; speed <= 255; speed++) {
    analogWrite(PIN_ENA_RIGHT, speed);  // speed up
    analogWrite(PIN_ENA_LEFT, speed);   // speed up
    currentSpeed = speed;
    delay(10);
  }
}
void Robot_Forward() {
  // direction = "forward";
  digitalWrite(MotorLeft[0], 1);
  digitalWrite(MotorLeft[1], 0);
  digitalWrite(MotorRight[0], 0);
  digitalWrite(MotorRight[1], 1);
  for (int speed = 0; speed <= 255; speed++) {
    analogWrite(PIN_ENA_RIGHT, speed);  // speed up
    analogWrite(PIN_ENA_LEFT, speed);   // speed up
    currentSpeed = speed;
    delay(10);
  }
}
void Robot_Left() {
  // direction = "left";
  digitalWrite(MotorLeft[0], 1);
  digitalWrite(MotorLeft[1], 0);
  digitalWrite(MotorRight[0], 1);
  digitalWrite(MotorRight[1], 0);
}
void Robot_Right() {
  // direction = "right";
  digitalWrite(MotorLeft[0], 0);
  digitalWrite(MotorLeft[1], 1);
  digitalWrite(MotorRight[0], 0);
  digitalWrite(MotorRight[1], 1);
}

void Robot_Stop() {
  digitalWrite(MotorLeft[0], 0);
  digitalWrite(MotorLeft[1], 0);
  digitalWrite(MotorRight[0], 0);
  digitalWrite(MotorRight[1], 0);
}

void MotorInit() {
  int i;
  for (i = 0; i < 2; i++) {
    pinMode(MotorLeft[i], OUTPUT);
    pinMode(MotorRight[i], OUTPUT);
  }
}
