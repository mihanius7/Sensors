#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int page = 5;
boolean autoTransition = false;

void lcdInit() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
}

void lcdProcess() {
  lcd.clear();
  lcd.setCursor(0, 0);
  switch (page)
  { case 1:
      lcd.print("T = ");
      lcd.print(cTemp);
      lcd.print(" *C");
      lcd.setCursor(0, 1);
      lcd.print("P = ");
      lcd.print(pressure / 10);
      lcd.print(" kPa");
      break;
    case 2:
      lcd.print("batt = ");
      lcd.print(batteryVoltage);
      lcd.print(" V");
      lcd.setCursor(0, 1);
      lcd.print("sun = ");
      lcd.print(sunVoltage);
      lcd.print(" V");
      break;
    case 3:
      lcd.print("accVec = ");
      lcd.print(defineAccelVector());
      lcd.print(" g");
      lcd.setCursor(0, 1);
      lcd.print("gyro = ");
      lcd.print(max(max(accelGyro[4], accelGyro[5]), max(accelGyro[5], accelGyro[6])));
      lcd.print(" */s");
      break;
    case 4:
      lcd.print("Vx=");
      lcd.print(vel[0]);
      lcd.print(" ");
      lcd.setCursor(9, 0);
      lcd.print("Vy=");
      lcd.print(vel[1]);
      lcd.setCursor(1, 1);
      lcd.print("Vz=");
      lcd.print(vel[2]);
      lcd.print(" m/s");
      break;
    case 5:
      lcd.print("GPS: ");
      lcd.print(latitude, 6);
      lcd.setCursor(0, 1);
      lcd.print(longitude, 6);
      lcd.setCursor(13, 1);
      lcd.print("{");
      lcd.print(satNumber);
      lcd.print("}");
      if (autoTransition)
        page = 0;
      break;
    default:
      page = 0;
      break;
  }
  if (autoTransition)
    page++;
}
