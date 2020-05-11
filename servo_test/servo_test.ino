#include <Servo.h>

Servo servo;

void setup() {
  pinMode(A0, INPUT);
  servo.attach(11);
}

void loop() {
  int potVal = analogRead(A0);
  int servoValue = map(potVal, 0, 1023, 0, 180);
  servoValue  = constrain(servoValue , 0, 180);
  servo.write(servoValue);

  int  ledValue = map(potVal, 0, 1023, 0, 255);
  ledValue = constrain(ledValue, 0, 255);
  analogWrite(3, ledValue);
  //  delay(100);
}
