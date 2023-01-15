#include <TinyGPS++.h>
#include <SoftwareSerial.h>

const int rxPin = 2, txPin = 3;
int satNumber = 0;
double latitude = 0, longitude = 0;

SoftwareSerial gpsSerial(rxPin, txPin);
TinyGPSPlus gpsParser;

void gpsInit() {
  gpsSerial.begin(9600);
  Serial.println("GPS initialized.");
}

void gpsProcess() {
  // This sketch displays information every time a new sentence is correctly encoded.
  if (gpsSerial.available() > 0) {
    gpsParser.encode(gpsSerial.read());
    satNumber = gpsParser.satellites.value();
    Serial.print("GPS Satellites found: ");
    Serial.println(satNumber);
    Serial.print("GPS date: ");
    Serial.println(gpsParser.date.value());
    if (gpsParser.location.isUpdated()) {
      // Latitude in degrees (double)
      latitude = gpsParser.location.lat();
      Serial.print("Latitude = ");
      Serial.print(latitude, 6);
      // Longitude in degrees (double)
      longitude = gpsParser.location.lng();
      Serial.print(", longitude = ");
      Serial.println(longitude, 6);
    }
  }
}
