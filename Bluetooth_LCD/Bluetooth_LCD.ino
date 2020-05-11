#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Подключение библиотеки
boolean backlightIsEnable = true;
unsigned long backligthOnTime = 0;


LiquidCrystal_I2C lcd(0x27, 16, 2); // Указываем I2C адрес (наиболее распространенное значение), а также параметры экрана (в случае LCD 1602 - 2 строки по 16 символов в каждой

void setup() {
  lcd.init();                      // Инициализация дисплея
  lcd.backlight();                 // Подключение подсветки
  Serial.begin(9600);
  backligthOnTime = millis();
}

void loop() {
  if (Serial.available()) {
    lcd.setCursor(0, 0);
    lcd.print(Serial.readString());
    lcd.backlight();
    backlightIsEnable = true;
    backligthOnTime = millis();
  }

  if (backlightIsEnable && ((millis() - backligthOnTime) > 5000)) {
    backlightIsEnable = false;
    lcd.noBacklight();
  }
}
