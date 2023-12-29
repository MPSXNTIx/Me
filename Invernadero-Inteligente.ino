#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Pin
int LedWhite = 7;
int LedRed = 6;
int LedYellow = 5;
int LedBlue = 4;
int Trig = 11;
int Echo = 12;
int SerMor = 9;
int Piezo = 8;
int SenH = A1;
int SenF = A0;

// Variable
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo motor;
int humedad;
int luminicidad;
int tiempo;
int distancia;

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
  mainArduino();
  delay(1000);
}

void mainArduino() {
  // iniciarTrigger
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);

  // obtenerDatos
    humedad = map(analogRead(SenH), 0, 1023, 117, 0);
    Serial.println("Humedad: " + String(humedad) + "%");
    luminicidad = analogRead(SenF);
    Serial.println("Luminicidad: " + String(luminicidad));
    tiempo = pulseIn(Echo, HIGH);
    distancia = ( tiempo * 0.000001 * 34000.0 )/ 2;
    Serial.println("Distancia: " + String(distancia) + "cm");

  // controlLeds
    digitalWrite(LedRed, LOW);
    digitalWrite(LedYellow, LOW);
    digitalWrite(LedBlue, LOW);

    if ( humedad < 30 ) {
      digitalWrite(LedRed, HIGH);
    } else if ( humedad < 70 ) {
      digitalWrite(LedYellow, HIGH);
    } else {
      digitalWrite(LedBlue, HIGH);
    }

    if ( luminicidad < 300 ) {
      digitalWrite(LedWhite, HIGH);
    } else {
      digitalWrite(LedWhite, LOW);
    }

  // controlMotor
    if ( luminicidad < 300 ) {
      motor.write(0);
    } else if ( distancia < 50 ) {
      motor.write(0);
      tone(Piezo, 523, 200);
    } else {
      motor.write(180);
    }

  // actualizarPantalla
    if ( luminicidad < 300 ) {
      lcd.setCursor(0,0);
      lcd.print("Noche");
    } else {
      lcd.setCursor(0,0);
      lcd.print("Dia  ");
    }

    lcd.setCursor(6,0);
    lcd.print("//");

    int angulo = motor.read();
    if ( angulo == 0 ) {
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
