/*
 connections to be made 
 ultrasonic sensor d18 for echo and trig on d4
 motor drive in3 an in4 on d22 and d23
 motor drive in1 an in2 on d19 and d21
*/
#include <WiFi.h>
#include <WiFiClient.h>  // to be able to connect to connect to hotspot
#include <WebServer.h>   // to make a server in arduino
#include <HTTPClient.h>  // to be abkle to make https requests to and from client (POST, GET, PUT, DELETE)
#include <DabbleESP32.h>

#include "BluetoothSerial.h"
// // Check if Bluetooth configs are enabled
// #if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
// #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
// #endif

// Bluetooth Serial object
// BluetoothSerial SerialBT;

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

// values for connectibng to webserver
WebServer server(5500);  // connecting webserver on port 80

void setup() {
  Dabble.begin("MyEsp32");
  Serial.begin(115200);
  // connect_to_hotspot();  // connect to hotspot

  // setting up enable pins
  pinMode(PIN_ENA_RIGHT, OUTPUT);
  pinMode(PIN_ENA_LEFT, OUTPUT);

  // setting up motot pins
  pinMode(MotorLeft[2], OUTPUT);
  pinMode(MotorRight[2], OUTPUT);

  // initializing motor
  MotorInit();

  // Bluetooth device name
  // SerialBT.begin("ESP32-HUB");
  // Serial.println("The device started, now you can pair it with bluetooth!");
}

// html to distplay if default router port is hit
String SendHTML() {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>ESP32 for hydropinics is READY!!!</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr += "p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>ESP32 for hydropinics is READY!!</h1>\n";
  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

// default route for server
void handle_OnConnect() {
  server.send(200, "text/html", SendHTML());
}

void loop() {
  // Robot_Forward();
  // delay(4000);
  // Robot_Stop();
  // delay(1000);
  // Robot_Backward();
  // delay(4000);
  // Robot_Stop();
  // delay(5000);
  Dabble.processInput();

  // It will be checking which button is pressed or not? Depending upon the button pressed, output pins of the microcontroller will be set to high or low. We are using else if statement.


  boolean a = GamePad.isUpPressed();
  boolean b = GamePad.isDownPressed();
  boolean c = GamePad.isLeftPressed();
  boolean d = GamePad.isRightPressed();
  boolean e = GamePad.isTrianglePressed();
  boolean f = GamePad.isCirclePressed();
  boolean g = GamePad.isCrossPressed();
  boolean h = GamePad.isSquarePressed();

  // move forward
  if (a || e) {
    Robot_Forward();
  }
  // Go Left condition
  else if (d || f) {
    Robot_Left();
  }
  //* Rights condition
  else if (c || h) {
    Robot_Right();
  }

  // Go back condition
  else if (b || g) {
    Robot_Backward();
  }
  //stop condition
  else {
    Robot_Stop();
  }
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
