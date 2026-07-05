#include <Wire.h>
#include <MPU6050_tockn.h>

#define pin_encoder 2

MPU6050 mpu6050(Wire);

volatile unsigned long pulsos = 0;
const int pulsos_volta = 20;
unsigned long tempoAnterior = 0;

void contar_pulso() {
  pulsos++;
}

void setup() {
  Serial.begin(115200);  
  Wire.begin();

  pinMode(encoderPin, INPUT_PULLUP);

  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  attachInterrupt(digitalPinToInterrupt(encoderPin), contarPulso, RISING);
}

void loop() {
  mpu6050.update();

  float ang_x = mpu6050.getAngleX();
  float ang_y = mpu6050.getAngleY();
  
  ang_x = constrain(ang_x, -90, 90);
  ang_y = constrain(ang_y, -90, 90);

  noInterrupts();
  unsigned long total_pulsos = pulsos;
  pulsos = 0;
  interrupts();
  
  msg = String(ang_x);
  msg += "_";
  msg += String(ang_y);
  msg += "!";
  msg += String(pulsos);
  
  Serial.println(msg_giroscopio);
  
}
