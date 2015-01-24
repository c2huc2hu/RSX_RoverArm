#include <Servo.h>

Servo wrist, elbow, shoulder, base;

enum positions {STANDARD,
               READING,
               STORED,
               VERTICAL};
               
int currentPosition, incomingByte, pos;

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
  
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available() > 0)
  {
    incomingByte = Serial.read();
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);  
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
      default:
        break;
    }
    moveArm(currentPosition);
  }
}
