#include <Servo.h>

Servo wrist, elbow, shoulder, base;

enum positions {STANDARD,
               READING,
               STORED,
               VERTICAL};
               
int currentPosition, incomingByte;
int wristPot, elbowPot, shoulderPot, basePot;
int wristPotVal, elbowPotVal, shoulderPotVal, basePotVal;
boolean automatic;

void moveArm(int pos)
{
  switch (pos)
  {
    case STANDARD:
      base.write(90);
      shoulder.write(135);
      elbow.write(120);
      break;
    case READING:
      base.write(90);
      shoulder.write(70);
      elbow.write(90);
      break;
    case STORED:
      base.write(90);
      shoulder.write(180);
      elbow.write(0);
      break;
    case VERTICAL:
      base.write(90);
      shoulder.write(180);
      elbow.write(90);
      break;  
    default:
      break;
  }  
}

void setup()
{
  currentPosition = NULL;  
  
  elbow.attach(24);
  wrist.attach(26);
  shoulder.attach(28);
  base.attach(30);
  
  wristPot = A0;
  elbowPot = A1;
  shoulderPot = A2;
  basePot = A3;  
  
  pinMode(wristPot, INPUT);
  pinMode(elbowPot, INPUT);
  pinMode(shoulderPot, INPUT);
  pinMode(basePot, INPUT);
  
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available() >= 4)
  { 
    wristPotVal = Serial.read();
    elbowPotVal = Serial.read();
    shoulderPotVal = Serial.read();
    basePotVal = Serial.read(); 
    
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
