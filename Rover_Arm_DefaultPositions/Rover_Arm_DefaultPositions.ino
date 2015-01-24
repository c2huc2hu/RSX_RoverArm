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
  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  
  wristPot = 0;
  elbowPot = 1;
  shoulderPot = 2;
  basePot = 3;
  
  automatic = true;
  
  Serial.begin(9600);
}

void loop()
{
  if (automatic)
  {
    if (Serial.available() > 0)
    {
      incomingByte = Serial.read();
      switch (incomingByte)
      {
        case 49:
          currentPosition = STANDARD;
          break;
        case 50:
          currentPosition = READING;
          break;
        case 51:
          currentPosition = STORED;
          break;
        case 52:
          currentPosition = VERTICAL;
          break;
        case 53: 
          automatic = false;
        default:
          break;
      }
      moveArm(currentPosition);
    }
  }
  else 
  {
    elbowPotVal = analogRead(elbowPot);
    shoulderPotVal = analogRead(shoulderPot);
    wristPotVal = analogRead(wristPot);
    basePotVal = analogRead(basePot);
    
    elbowPotVal = map(elbowPotVal, 0, 1023, 0, 179); 
    shoulderPotVal = map(shoulderPotVal, 0, 1023, 0, 179);  
    wristPotVal = map(wristPotVal, 0, 1023, 0, 179);
    basePotVal = map(basePotVal, 0, 1023, 0, 179);
    
    elbow.write(elbowPotVal);
    shoulder.write(shoulderPotVal);
    wrist.write(wristPotVal);
    base.write(basePotVal);
    
    if (Serial.available() > 0)
    {
      incomingByte = Serial.read();
      if (incomingByte == 53)
      {
        automatic = true;
      }
    }
    
  }
}
