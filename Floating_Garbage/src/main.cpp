#include "max6675.h"
#include <LiquidCrystal_I2C.h>

int thermoDOA = 4;
int thermoCSA = 5;
int thermoCLKA = 6;
int thermoDOB = 7;
int thermoCSB = 8;
int thermoCLKB = 9;

LiquidCrystal_I2C lcd(0x27,20,4);

MAX6675 thermocoupleA(thermoCLKA, thermoCSA, thermoDOA);
MAX6675 thermocoupleB(thermoCLKB, thermoCSB, thermoDOB);

void setup() {
  Serial.begin(9600);
  lcd.init();                   
  lcd.backlight();
}

void loop() {
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("C = ");
  lcd.setCursor(4,0);
  lcd.print(thermocoupleA.readCelsius());
  lcd.setCursor(0,1);
  lcd.print("C = ");
  lcd.setCursor(4,1);
  lcd.print(thermocoupleB.readCelsius());
 
  // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
  delay(1000);
}