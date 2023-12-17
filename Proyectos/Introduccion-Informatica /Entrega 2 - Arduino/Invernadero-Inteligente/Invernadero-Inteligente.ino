#include <Servo.h>
#include <LiquidCrystal_I2C.h>

//Pines
int PinFR = A0;//Pin de fotoresistor
int Trig = 7;//Pin de UltraSensor
int Echo = 6;//Pin de UltraSensor
int PinH = A1;//Pin de SensorHumedad
int PinMot = 5;//Pin de ServoMotor
int LedR = 9;//Pin LED rojo
int LedB = 8;//Pin LED azul

//Variables
int VelSon = 34000.0;
int luminicidad;
int tiempo;
int distancia;
int humedad;
Servo motor;
LiquidCrystal_I2C lcd(0x27, 20, 4);
String estado;
String detectado;

void setup(){
  //Pantalla led
  lcd.init();
  lcd.backlight();
  
  //Analogicos
  pinMode(PinFR, INPUT);
  pinMode(PinH, INPUT);
  
  //Digitales
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  motor.attach(PinMot);
  
  //Conexion Serial
  Serial.begin(9600);
}

void loop(){
  //Guardar el valor del fotoresistor
  luminicidad = analogRead(PinFR);//Lee entrada analogica
  Serial.print("luminicidad: ");
  Serial.println(luminicidad);
  
  //Guardar el valor del ultrasonido
  iniciarTrigger();//Emitimos una onda sonica
  tiempo = pulseIn(Echo, HIGH);//Recibimos onda sonica
  distancia = ( tiempo * 0.000001 * VelSon )/ 2;//Distancia = (velocidad * tiempo)/2
  Serial.print("distancia: ");
  Serial.println(distancia);
  
  //Guardar el valor de humedad
  humedad = map(analogRead(PinH), 0, 1023, 100, 0);//Lee entrada analogica ; map transforma rango de valores a un rango requerido
  Serial.print("humedad: ");
  Serial.println(humedad);
  
  //Pantalla led
  if (humedad < 40){
    lcd.setCursor(0,1);
    lcd.print("H2O = ");
    lcd.print(humedad);
    lcd.print("% ");
    lcd.setCursor(9,1);
    lcd.print("  Water");
  } else {
    lcd.setCursor(0,1);
    lcd.print("H2O = ");
    lcd.print(humedad);
    lcd.print("% ");
  }
  
  if (distancia < 10){
    lcd.setCursor(8,0);
    detectado = "DETECTED";
    lcd.print(detectado);
  } else {
    lcd.setCursor(8,0);
    detectado = "NOTHING ";
    lcd.print(detectado);
  }

  //Validar intensidad de luz
  if (luminicidad < 30){
    motor.write(0);//Cierra el toldo
    lcd.setCursor(0,0);
    estado = "Night";
    lcd.print(estado);
  } else {
    lcd.setCursor(0,0);
    estado = "Day  ";
    lcd.print(estado);
    //motor.write(180);//Abre el toldo ; para verificar si no hya nada cerca
    if (distancia < 10){
      motor.write(0);//Cierra el toldo
    } else {
      motor.write(180);//Abre el toldo
    }
  }
  
  //LED RED/BLUE
  int angulo = motor.read();
  if (angulo == 180){
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
  } else {
    digitalWrite(9, HIGH);
    digitalWrite(8, LOW);
  }

  delay(1000);//tiempo de espera
}

void iniciarTrigger(){
  // Ponemos el Triiger en estado bajo y esperamos 2 ms
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  // Ponemos el pin Trigger a estado alto y esperamos 10 ms
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  // Comenzamos poniendo el pin Trigger en estado bajo
  digitalWrite(Trig, LOW);
}
