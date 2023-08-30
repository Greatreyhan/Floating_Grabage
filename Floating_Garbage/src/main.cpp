#include "max6675.h"
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

#define thermoDOA 4
#define thermoCSA 5
#define thermoCLKA 6
#define thermoDOB 7
#define thermoCSB 8
#define thermoCLKB 9
#define rxPin 10
#define txPin 11
#define MQ A0

SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);
LiquidCrystal_I2C lcd(0x27, 20, 4);

MAX6675 thermocoupleA(thermoCLKA, thermoCSA, thermoDOA);
MAX6675 thermocoupleB(thermoCLKB, thermoCSB, thermoDOB);
volatile int dist = 0;
void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  mySerial.begin(9600);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  pinMode(MQ, INPUT);
}

void loop()
{
  static String receivedData;
  if (mySerial.available())
  {
    // Read the incoming data from UART
    char receivedChar = mySerial.read();
    if (receivedChar == 13)
    { // Check for CR termination
      dist = receivedData.toInt();
      Serial.println(dist);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("T1 = ");
      lcd.setCursor(4, 0);
      lcd.print(thermocoupleA.readCelsius());
      lcd.setCursor(0, 1);
      lcd.print("T2 = ");
      lcd.setCursor(4, 1);
      lcd.print(thermocoupleB.readCelsius());
      lcd.setCursor(0, 2);
      lcd.print("D = ");
      lcd.setCursor(4, 2);
      lcd.print(dist);
      lcd.setCursor(0, 3);
      lcd.print("MQ = ");
      lcd.setCursor(4, 3);
      lcd.print(analogRead(MQ));
      // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
      delay(1000);
      receivedData = ""; // Clear the data buffer
    }
    else
    {
      receivedData += receivedChar; // Append character to data buffer
    }
  }
}