#include <Wire.h>
#include "printf.h"

const int GLOBAL_LOOP_DELAY = 500;
const boolean USING_PLOTTER = false;

#include "sensors.h"
#include "climatic.h"
#include "acceleration.h"
#include "radio.h"
#include "lcd.h"
#include "gps.h"

void setup() {
  Serial.begin(9600);
  printf_begin();
  Wire.begin();
  lcdInit();
  climaticInit();
  accelerationInit();
  radioInit();
  gpsInit();
}

void loop() {
  sensorsProcess();
  climaticProcess();
  accelerationProcess();
  radioProcess();
  gpsProcess();
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
  Serial.print(accelDiff[0]);
  Serial.print(" ");
  Serial.print(accelDiff[1]);
  Serial.print(" ");
  Serial.println(accelDiff[2]);
  Serial.print(F("vx vy vz = "));
  Serial.print(vel[0]);
  Serial.print(" ");
  Serial.print(vel[1]);
  Serial.print(" ");
  Serial.println(vel[2]);
  Serial.print("Time step = ");
  Serial.println(dt);
  if (!USING_PLOTTER) {
    Serial.print(F("Battery = "));
    Serial.print(batteryVoltage * 1.17);
    Serial.println(" V");
    Serial.print(F("Sun = "));
    Serial.print(sunVoltage * 1.17);
    Serial.println(" V");
  }
  Serial.println();
}
