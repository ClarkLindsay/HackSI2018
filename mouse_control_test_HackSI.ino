#include <Servo.h>

Servo servoLeft;
Servo servoRight;
const float pi = 3.14159;
float RadianToDegree = 160/pi;
float DegreeToRadian = pi/160;
byte midHeight = 200;
byte midWidth = 67;
float x=0.;
float y=0;
int MyDelay=10;
int incomingByteX = 0;
void setup()
{
  Serial.begin(9600);
  servoLeft.attach(7);
  servoRight.attach(8);
  servoLeft.writeMicroseconds(90);
  servoRight.writeMicroseconds(90);
}
void loop()
{
  if(Serial.available() >= 2) ;
  {
    incomingByteX = Serial.read();
    incomingByteY = Serial.read();
   if (incomingByteX>=0 && incomingByteX<=127
    && incomingByteY>=127 && incomingByteY<=255)
    {
      #ifdef DEBUG
      Serial.print("SERIAL X : ");Serial.print(incomingByteX);
      Serial.print(" ||  SERIAL Y : ");Serial.print(incomingByteY);
      #endif
      x = incomingByteX;
      y = incomingByteY;
      if (x < 50 && y < midHeight) {
        servoLeft.write(90);
        servoRight.write(180);
      }
      else if (x < 50 && y > midHeight) {
        servoLeft.write(90);
        servoRight.write(160);
      }
      else if (x > 80 && y < midHeight) {
        servoLeft.write(10);
        servoRight.write(160);
      }
      else if (x > 80 && y > midHeight) {
        servoLeft.write(180);
        servoRight.write(90);
      }
      else if ((x >= 50 && x <= 80) && y > midHeight) {
        servoLeft.write(180);
        servoRight.write(0);
      }
      else if ((x >= 50 && x <= 80) && y < midHeight) {
        servoLeft.write(10);
        servoRight.write(160);
      }
    }
  }
    delay(MyDelay);
}
