float batteryVoltage = 0;
byte batteryPercentage = 4;
float sunVoltage = 0;
const float OFF_LEVEL = 3.18; // was 3.03
const float MAX_LEVEL = 4.03;

void sensorsInit() {
  analogReference(DEFAULT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void sensorsProcess() {
	 batteryVoltage = analogRead(A0) * 5.0 / 1024;
   batteryVoltage /= 0.276;
   batteryPercentage = (batteryVoltage - OFF_LEVEL) / (MAX_LEVEL - OFF_LEVEL) * 100;
   batteryPercentage = round(constrain(batteryPercentage, 1, 100));
	 sunVoltage = analogRead(A1) * 5.0 / 1024;
   sunVoltage /= 0.16;
}
