/*
 connections to be made 
 ultrasonic sensor d18 for echo and trig on d4
 motor drive in3 an in4 on d22 and d23
 motor drive in1 an in2 on d19 and d21
*/
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

//pins to drive motors
int MotorLeft[2] = {19,21};  
int MotorRight[2] = {22,23};
char ssid[] = "ray";
char pass[] = "2444666668888888";

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
  pinMode(MotorLeft[i],OUTPUT);
  pinMode(MotorRight[i],OUTPUT);
  MotorInit()

}

void loop() {
  // put your main code here, to run repeatedly:

}


void Robot_Forward()
{
   digitalWrite(MotorLeft[0],0);
   digitalWrite(MotorLeft[1],1);
   digitalWrite(MotorRight[0],1);
   digitalWrite(MotorRight[1],0);   
}
void Robot_Backward()
{
   digitalWrite(MotorLeft[0],1);
   digitalWrite(MotorLeft[1],0);
   digitalWrite(MotorRight[0],0);
   digitalWrite(MotorRight[1],1);  
}
void Robot_Left()
{
  digitalWrite(MotorLeft[0],1);
  digitalWrite(MotorLeft[1],0);
  digitalWrite(MotorRight[0],1);
  digitalWrite(MotorRight[1],0);    
}
void Robot_Right()
{
  digitalWrite(MotorLeft[0],0);
  digitalWrite(MotorLeft[1],1);
  digitalWrite(MotorRight[0],0);
  digitalWrite(MotorRight[1],1);    
}

void Robot_Stop()
{
  digitalWrite(MotorLeft[0],0);
  digitalWrite(MotorLeft[1],0);
  digitalWrite(MotorRight[0],0);
  digitalWrite(MotorRight[1],0);    
}

void MotorInit()
{
  int i;
  for(i=0 ; i<2; i++)
  {
  pinMode(MotorLeft[i],OUTPUT);
  pinMode(MotorRight[i],OUTPUT);
  }
}
