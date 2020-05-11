void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
}

void loop() {
  analogWrite(9, analogToPWM(A0));
  analogWrite(10, 0);
  analogWrite(11, analogToPWM(A1));
}

int analogToPWM(int pinNum) {
  int pwmValue = analogRead(pinNum);
  pwmValue = map(pwmValue, 0, 1023, 0, 255);
  pwmValue = constrain(pwmValue, 0, 255);
  return pwmValue;
}
