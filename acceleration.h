const int MPU_addr = 0x68; // адрес датчика
const float G = 9.81;

// массив данных
// [accX, accY, accZ, temp, gyrX, gyrY, gyrZ]
// acc - ускорение, temp - температура (raw), gyr - угловая скорость

boolean firstLoop = true;
int16_t data[7];
float accelSensitivity = 16384; // LSB/g
float gyroSensitivity = 131; // LSB/*/s
float accelGyro[7], lastAccel[3], accelDiff[3], vel[3];
float dt = GLOBAL_LOOP_DELAY; // in seconds already
float lastTime = millis();

float truncate(float val, byte dec)
{
  float x = val * pow(10, dec);
  float y = round(x);
  float z = x - y;
  if ((int)z == 5)
  {
    y++;
  } else {}
  x = y / pow(10, dec);
  return x;
}

void saveRAWdata() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
  for (byte i = 0; i < 7; i++) {
    data[i] = Wire.read() << 8 | Wire.read();
  }
}

void refreshAccelGyro() {
  // Save last accel values
  lastAccel[0] = accelGyro[0];
  lastAccel[1] = accelGyro[1];
  lastAccel[2] = accelGyro[2];

  // Convert new accel values from RAW. Fix zero values.
  accelGyro[0] = data[0] / accelSensitivity - 0.01;
  accelGyro[1] = data[1] / accelSensitivity + 0.015;
  accelGyro[2] = data[2] / accelSensitivity + 0.01;
  accelGyro[4] = data[4] / gyroSensitivity - 0.35;
  accelGyro[5] = data[5] / gyroSensitivity - 3.59;
  accelGyro[6] = data[6] / gyroSensitivity + 0.12;

  // Truncate values
  accelGyro[0] = truncate(accelGyro[0], 2);
  accelGyro[1] = truncate(accelGyro[1], 2);
  accelGyro[2] = truncate(accelGyro[2], 2);
  accelGyro[4] = round(accelGyro[4]);
  accelGyro[5] = round(accelGyro[5]);
  accelGyro[6] = round(accelGyro[6]);

  // Save accel differences
  accelDiff[0] = accelGyro[0] - lastAccel[0];
  accelDiff[1] = accelGyro[1] - lastAccel[1];
  accelDiff[2] = accelGyro[2] - lastAccel[2];
}

void calcVelocity() {
  if (!firstLoop) {
    vel[0] += accelDiff[0] * G * dt;
    vel[1] += accelDiff[1] * G * dt;
    vel[2] += accelDiff[2] * G * dt;
  }
  else firstLoop = false;
}

void accelerationInit() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  // Configure Accelerometer Sensitivity - Full Scale Range (default +/- 2g)
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1C);                  //Talk to the ACCEL_CONFIG register (1C hex)
  Wire.write(0x00);                  //Set the register bits as 00000000 (+/- 2g full scale range)
  //Wire.write(0x10);                  //Set the register bits as 00010000 (+/- 4g full scale range)
  //Wire.write(0x20);                  //Set the register bits as 00020000 (+/- 8g full scale range)
  //Wire.write(0x30);                  //Set the register bits as 00030000 (+/- 16g full scale range)
  Wire.endTransmission(true);

  // Configure Gyro Sensitivity - Full Scale Range (default +/- 250deg/s)
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1B);                   // Talk to the GYRO_CONFIG register (1B hex)
  Wire.write(0x00);                   // Set the register bits as 00000000 (250deg/s full scale)
  //Wire.write(0x10);                   // Set the register bits as 00010000 (500deg/s full scale)
  //Wire.write(0x20);                   // Set the register bits as 00020000 (1000deg/s full scale)
  //Wire.write(0x30);                   // Set the register bits as 00030000 (2000deg/s full scale)
  Wire.endTransmission(true);

  firstLoop = true;
  delay(25);
}

float defineAccelVector() {
  return sqrt(pow(accelDiff[0], 2) + pow(accelDiff[1], 2) + pow(accelDiff[2], 2));
}

void accelerationProcess() {
  // Update dt
  dt = (millis() - lastTime) / 1000;
  lastTime = millis();

  // Get RAW data
  saveRAWdata();

  // Prepare values is needed
  refreshAccelGyro();
  calcVelocity();
}
