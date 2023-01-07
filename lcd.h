#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int page = 4;
boolean autoTransition = false;

void lcdInit() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
}

void lcdProcess() {
  switch (page)
  { case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("T = ");
      lcd.print(cTemp);
      lcd.print(" *C");
      lcd.setCursor(0, 1);
      lcd.print("P = ");
      lcd.print(pressure / 10);
      lcd.print(" kPa");
      if (autoTransition) page++;
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("batt = ");
      lcd.print(batteryPercentage);
      lcd.print(" %");
      lcd.setCursor(0, 1);
      lcd.print("sun = ");
      lcd.print(sunVoltage);
      lcd.print(" V");
      if (autoTransition) page++;
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("accVec = ");
      lcd.print(defineAccelVector());
      lcd.print(" g");
      lcd.setCursor(0, 1);
      lcd.print("gyro = ");
      lcd.print(max(max(accelGyro[4], accelGyro[5]), max(accelGyro[5], accelGyro[6])));
      lcd.print(" */s");
      if (autoTransition) page++;
      break;
    case 4:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Vx=");
      lcd.print(vel[0]);
      lcd.print(" ");
      lcd.setCursor(9, 0);
      lcd.print("Vy=");
      lcd.print(vel[1]);
      lcd.setCursor(3, 1);
      lcd.print("Vz=");
      lcd.print(vel[2]);
      lcd.print(" km/h");
      if (autoTransition) page = 1;
      break;
    default:
      lcd.clear();
      if (autoTransition) page = 1;
      break;
  }
}
