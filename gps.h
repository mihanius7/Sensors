#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int rxPin = 2, txPin = 3;

SoftwareSerial ss = SoftwareSerial(rxPin, txPin);
TinyGPSPlus gps;

void gpsInit() {
  ss.begin(9600);
  Serial.println("GPS initialized.");
}

void gpsProcess() {
  // This sketch displays information every time a new sentence is correctly encoded.
  if (ss.isListening()) {
    Serial.print("GPS listening. I hear: ");
    Serial.println(ss.read());
  }
  if (ss.available() > 0) {
    gps.encode(ss.read());
    if (gps.location.isUpdated()) {
      // Latitude in degrees (double)
      Serial.print("Latitude = ");
      Serial.print(gps.location.lat(), 6);
      // Longitude in degrees (double)
      Serial.print(", longitude = ");
      Serial.println(gps.location.lng(), 6);
    }
  }
}
