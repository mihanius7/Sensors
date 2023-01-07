#include <Wire.h>
#include "printf.h"

const int GLOBAL_LOOP_DELAY = 150;
const boolean USING_PLOTTER = true;

#include "sensors.h"
#include "climatic.h"
#include "acceleration.h"
#include "radio.h"
#include "lcd.h"

void setup() {
  Serial.begin(9600);
  printf_begin();
  Wire.begin();
  lcdInit();
  climaticInit();
  accelerationInit();
  radioInit();
}

void loop() {
  sensorsProcess();
  climaticProcess();
  accelerationProcess();
  radioProcess();
  lcdProcess();

  debugToSerial();

  delay(GLOBAL_LOOP_DELAY);
}

void debugToSerial() {
  if (!USING_PLOTTER) {
    Serial.print(F("Temperature = "));
    Serial.print(cTemp);
    Serial.println(" *C");
    Serial.print(F("Pressure = "));
    Serial.print(pressure);
    Serial.println(" hPa");
    Serial.print(F("Approx altitude = "));
    Serial.print(altitude);
    Serial.println(" m");
    Serial.print(F("ax ay az = "));
  }
  Serial.print(accelGyro[0] - lastAccel[0]);
  Serial.print(" ");
  Serial.print(accelGyro[1] - lastAccel[1]);
  Serial.print(" ");
  Serial.print(accelGyro[2] - lastAccel[2]);
//  Serial.print(vel[0]);
//  Serial.print(" ");
//  Serial.print(vel[1]);
//  Serial.print(" ");
//  Serial.println(vel[2]);
  Serial.print(" ");
  Serial.println(dt);
  if (!USING_PLOTTER) {
    Serial.println(" g");
    Serial.print(F("Battery = "));
    Serial.print(batteryVoltage * 1.17);
    Serial.println(" V");
    Serial.print(F("Sun = "));
    Serial.print(sunVoltage * 1.17);
    Serial.println(" V");
  }
//  Serial.println();
}
