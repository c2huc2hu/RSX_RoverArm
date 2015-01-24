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
      break;
    case READING:
      base.write(90);
      shoulder.write(40);
      break;
    case STORED:
      base.write(90);
      shoulder.write(135);
      break;
    case VERTICAL:
      base.write(90);
      shoulder.write(180);
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
//  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
//  {                                  // in steps of 1 degree 
//    wrist.write(pos);              // tell servo to go to position in variable 'pos' 
//    delay(15);                       // waits 15ms for the servo to reach the position 
//  } 
//  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
//  {                                
//    wrist.write(pos);              // tell servo to go to position in variable 'pos' 
//    delay(15);                       // waits 15ms for the servo to reach the position 
//  } 
  
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
