#include <Wire.h>
#include <MPU6050_tockn.h>

#define pin_encoder 2

MPU6050 mpu(Wire);

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

  mpu.begin();
  mpu.setGyroRange(1);
  mpu.calcGyroOffsets(true);

  attachInterrupt(digitalPinToInterrupt(encoderPin), contarPulso, RISING);
}

void loop() {
  unsigned long tempo_atual = millis();
  float delta_tempo = (tempo_atual - tempo_anterior) / 1000.00;
  tempo_anterior = tempo_atual;

  mpu.update();

  noInterrupts();
  unsigned long total_pulsos = pulsos;
  pulsos = 0;
  interrupts();
  
  msg = String(mpu.getGyroX());
  msg += "_";
  msg += String(pulsos);
  msg += "!";
  msg += String(delta_tempo);
  
  Serial.println(msg);
}
