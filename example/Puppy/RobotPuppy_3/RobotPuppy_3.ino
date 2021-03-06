/*
  RobotPuppy_3
 
 This example uses two ultrasonic sensors to check wether an object is in front, 
 to the left, or the right of the robot. The left sensor is connected to DP4 and
 the right one to A1 on the Svante robot. When we now where the object is the 
 robot wheels are controlled to move towards the object.
 
 This is an example from the Svante robot summer camp.

 (c) 2014 Arduino LLC
 */
 
#include <Svante.h>
#include <EEPROM.h>

int trigR = A1;
int echoR = A1;
int trigL = DP8;
int echoL = DP8;

int threshold = 70;
int stopThreshold = 10;

void setup(){  
  Serial.begin(9600);  //Initializes the serial communication
  robot.begin();       //Initializes the Svante library
}

void loop(){
  int disR = getDistance(trigR, echoR);
  int disL = getDistance(trigL, echoL);
  
  if(disL<stopThreshold || disR<stopThreshold) {
    Serial.println("Too close!");
    robot.stop();                       //If the robot gets too close to something, stop the robot
  }
  else if(disL<threshold && disR<threshold){
    Serial.println("In front!");
    robot.go(70, 70);                  //If object is in front, make the robot go forward
  }
  else if(disL<threshold){
    Serial.println("To the left!");
    robot.go(10, 70);                  //If object is to the left, make the robot turn left
  }
  else if(disR<threshold) {
    Serial.println("To the right!");
    robot.go(70, 10);                  //If object is to the right, make the robot turn lefrightt
  }
  else {
    Serial.println("Nothing there!");
    robot.stop();                       //If there's nothing there, stop the robot
  }

  delay(100);
}


int getDistance(int triggerPin, int echoPin){
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin,LOW);
  delayMicroseconds(2);  
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(triggerPin, LOW);
  
  pinMode(echoPin, INPUT);
  int duration = pulseIn(echoPin, HIGH, 11800);
  int distance = constrain(duration/29/2, 0, 200);
  if(distance==0)distance=200;

  return distance;
}
