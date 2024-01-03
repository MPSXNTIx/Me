#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Pin
#define LedWhite 7;
#define LedRed 6;
#define LedYellow 5;
#define LedBlue 4;
#define Trig 11;
#define Echo 12;
#define SerMor 9;
#define Piezo 8;
#define SenH A1;
#define SenF A0;

// Variable
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo motor;
int humedad = 0;
int luminicidad = 0;
int tiempo = 0;
int distancia = 0;

void setup() {
  // Analog
  pinMode(SenH, INPUT);
  pinMode(SenF, INPUT);

  // Digital
  pinMode(Piezo, OUTPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  motor.attach(SerMor);

  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  iniciarTrigger();
  obtenerDatos();
  controlLeds();
  controlMotor();
  actualizarPantalla();
  Serial.println("Humedad: " + String(humedad) + "%");
  Serial.println("Luminicidad: " + String(luminicidad));
  Serial.println("Distancia: " + String(distancia) + "cm");
  delay(1000);
}

void iniciarTrigger(){
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
}

void obtenerDatos() {
  humedad = map(analogRead(SenH), 0, 1023, 117, 0);
  luminicidad = analogRead(SenF);
  tiempo = pulseIn(Echo, HIGH);
  distancia = (tiempo * 0.000001 * 34000.0)/ 2;
}

void controlLeds() {
  digitalWrite(LedRed, LOW);
  digitalWrite(LedYellow, LOW);
  digitalWrite(LedBlue, LOW);
  
  if (humedad < 30) {
    digitalWrite(LedRed, HIGH);
  } else if (humedad < 70) {
    digitalWrite(LedYellow, HIGH);
  } else {
    digitalWrite(LedBlue, HIGH);
  }

  if (luminicidad < 300) {
    digitalWrite(LedWhite, HIGH);
  } else {
    digitalWrite(LedWhite, LOW);
  }
}

void controlMotor() {
  if (luminicidad < 300) {
    motor.write(0);
  } else if (distancia < 50) {
    motor.write(0);
    tone(Piezo, 523, 200);
  } else {
    motor.write(180);
  }
}

void actualizarPantalla() {
  if (luminicidad < 300) {
    lcd.setCursor(0,0);
    lcd.print("Noche");
  } else {
    lcd.setCursor(0,0);
    lcd.print("Dia  ");
  }
  
  lcd.setCursor(6,0);
  lcd.print("//");
  
  int angulo = motor.read();
  if (angulo == 0) {
    lcd.setCursor(9,0);
    lcd.print("Cerrado");
  } else {
    lcd.setCursor(9,0);
    lcd.print("Abierto");
  }
  
  lcd.setCursor(0,1);
  lcd.print("Humedad: " + String(humedad) + "%     ");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.println("Distancia: " + String(distancia) + "cm  ");
  delay(1000);
}
