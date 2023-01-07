#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(8, 10); //CE, CSN
byte pipe[6] = "1SNSR";
byte payload[7];

void radioInit() {
  pinMode(LED_BUILTIN, OUTPUT);
  if (!USING_PLOTTER) Serial.println("Configure NRF24...");
  SPI.begin();

  radio.begin();
  radio.enableDynamicPayloads();
  radio.setAutoAck(true);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setRetries(5, 15);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(55);
  radio.setCRCLength(RF24_CRC_16);
  radio.setPayloadSize(32);
  radio.openWritingPipe(pipe);
  radio.stopListening();

  if (!USING_PLOTTER) radio.printDetails();
  delay(500);
  Serial.println();
}

void radioProcess() {
  payload[0] = (cTemp - 10) * 10;
  payload[1] = pressure - 850;
  payload[2] = batteryVoltage * 25;
  payload[3] = sunVoltage * 25;
  payload[4] = accelGyro[0] * 15 + 50;
  payload[5] = accelGyro[1] * 15 + 50;
  payload[6] = accelGyro[2] * 15 + 50;
  radio.stopListening();
  if (radio.write(payload, sizeof(payload))) {
    digitalWrite(LED_BUILTIN, HIGH);
    if (!USING_PLOTTER) Serial.print("TRANSMIT DONE.");
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    if (!USING_PLOTTER) {
      Serial.print("    Retries: ");
      Serial.println(radio.getARC());
    }
  } else {
    if (!USING_PLOTTER) {
      Serial.println("TRANSMIT FAILED. ");
      Serial.print("    Retries: ");
      Serial.println(radio.getARC());
    }
    delay(100);
  }
  radio.startListening();
}
