#include <Servo.h>

Servo wrist, elbow, shoulder, base; // Servo motors
//int wristPot, elbowPot, shoulderPot, basePot; // Positions of the potentiometer
int wristPotVal, elbowPotVal, shoulderPotVal, basePotVal;  

void setup()
{ 
  // attach the servos to ports
  elbow.attach(24);
  wrist.attach(26);
  shoulder.attach(28);
  base.attach(30);
  
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
    wristPotVal = Serial.read();
    elbowPotVal = Serial.read();
    shoulderPotVal = Serial.read();
    basePotVal = Serial.read(); 
    
    // Send the angle values to the motors
    if (wristPotVal <= 180)
      wrist.write(wristPotVal);
    if (elbowPotVal <= 180)
      elbow.write(elbowPotVal);
    if (shoulderPotVal <= 180)
      shoulder.write(shoulderPotVal);
    if (basePotVal <= 180)
      base.write(basePotVal);
  }
}

