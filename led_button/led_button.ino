boolean ledStatus = true;
boolean pressed = false;
void setup() {
  pinMode(A5, INPUT_PULLUP);
  pinMode(12, INPUT);
  pinMode(A4, OUTPUT);
  pinMode(A0, INPUT);

  Serial.begin(9600);
}

void loop() {
  boolean button1 = !digitalRead(A5);
  if (button1) {
    if (!pressed) {
      pressed = true;
      ledStatus = !ledStatus;
    } else {
      pressed = false;
    }
    delay(100);
  }

  if (ledStatus) {
    int potVal = analogRead(A0);
    potVal = map(potVal, 0, 1023, 0, 255);
    potVal = constrain(potVal, 0, 255);
    Serial.println(potVal);
    analogWrite(3, potVal);
  } else {
    analogWrite(3, 0);
  }
  delay(30);
}
