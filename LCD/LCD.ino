#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Подключение библиотеки
//#include <LiquidCrystal_PCF8574.h> // Подключение альтернативной библиотеки

LiquidCrystal_I2C lcd(0x27, 16, 2); // Указываем I2C адрес (наиболее распространенное значение), а также параметры экрана (в случае LCD 1602 - 2 строки по 16 символов в каждой
//LiquidCrystal_PCF8574 lcd(0x27); // Вариант для библиотеки PCF8574

void setup() {
  lcd.init();                      // Инициализация дисплея
  lcd.backlight();                 // Подключение подсветки
  lcd.setCursor(0, 0);             // Установка курсора в начало первой строки
  lcd.print("Boooo");             // Набор текста на первой строке
  lcd.setCursor(0, 1);             // Установка курсора в начало второй строки
  lcd.printstr("");   // Набор текста на второй строке
}

void loop() {
  for (int i = 0; i < 12; i++) {
    lcd.setCursor(0, 0);
    lcd.print("Timer: " + String(i) + " ");
    lcd.setCursor(0, 1);
    lcd.print("Timer: " + String(11 - i) + " ");
    delay(1000);
  }
}
