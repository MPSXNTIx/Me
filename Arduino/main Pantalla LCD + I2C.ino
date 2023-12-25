#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  mainArduino();
  delay(1000);
}

void mainArduino() {
  lcd.setCursor(0,0);
  lcd.print("Hola Mundo");
}
