#include <Servo.h>

Servo wrist, elbow, shoulder, shoulder2, base; // Servo motors
//int wristPot, elbowPot, shoulderPot, basePot; // Positions of the potentiometer
int wristPotVal, elbowPotVal, shoulderPotVal, shoulder2Val, basePotVal;  

void setup()
{ 
  // attach the servos to ports
  elbow.attach(12);
//  wrist.attach(1);
  shoulder.attach(11);
  shoulder2.attach(10); 
//  base.attach(10);
  
  // Initialize the ids of the servo ports
/*  wristPot = A0;
  elbowPot = A1;
  shoulderPot = A2;
  basePot = A3;  */
  
  /* Set the potentiometers to input
  pinMode(wristPot, INPUT);
  pinMode(elbowPot, INPUT);
  pinMode(shoulderPot, INPUT);
  pinMode(basePot, INPUT); */ 
  
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available() >= 4)
  { 
    // Read where to put the joints from the serial
//    wristPotVal = Serial.read();
    elbowPotVal = Serial.read();
    shoulderPotVal = Serial.read();
    shoulder2Val = Serial.read(); 
    basePotVal = Serial.read(); 
    
    // Send the angle values to the motors
    if (elbowPotVal <= 180)
      elbow.write(elbowPotVal);
    if (shoulderPotVal <= 180)
      shoulder.write(shoulderPotVal);
    if (shoulder2Val <= 180)
      shoulder2.write(shoulder2Val); 
    if (basePotVal <= 180)
      base.write(basePotVal);
  }
}

