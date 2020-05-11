#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Подключение библиотеки
#include "DHT.h"

#define DHTPIN 2 // Тот самый номер пина, о котором упоминалось выше

LiquidCrystal_I2C lcd(0x27, 16, 2); // Указываем I2C адрес (наиболее распространенное значение), а также параметры экрана (в случае LCD 1602 - 2 строки по 16 символов в каждой
DHT dht(DHTPIN, DHT11);

void setup() {
  lcd.init();                      // Инициализация дисплея
  lcd.backlight();                 // Подключение подсветки

  dht.begin();
}

void loop() {
  delay(2000);
  while (true) {
    float h = dht.readHumidity(); //Измеряем влажность
    float t = dht.readTemperature(); //Измеряем температуру

    lcd.setCursor(0, 0);
    lcd.print("Humidity:" + String(h) + "     ");
    lcd.setCursor(0, 1);
    lcd.print("Temp:" + String(t) + "    ");
    delay(1000);
  }
}
