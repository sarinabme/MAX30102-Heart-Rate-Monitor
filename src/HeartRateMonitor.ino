#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "MAX30105.h"
#include "heartRate.h"

MAX30105 particleSensor;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buzzerPin = 8;

const unsigned long MEASURE_TIME = 20000;
const unsigned long RESULT_TIME = 7000;
const unsigned long FINGER_TIMEOUT = 30000;

unsigned long lastBeat = 0;
float beatsPerMinute = 0;

void setup()
{
  Serial.begin(115200);

  pinMode(buzzerPin, OUTPUT);
  noTone(buzzerPin);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Heart Monitor");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");

  if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD))
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MAX30102 Error");

    Serial.println("MAX30102 not found!");

    while (1)
      ;
  }

  particleSensor.setup();

  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeGreen(0);

  delay(2000);

  lcd.clear();
}

void loop()
{
  noTone(buzzerPin);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Place Finger");
  lcd.setCursor(0, 1);
  lcd.print("Ready...");

  unsigned long fingerStartTime = millis();

  while (particleSensor.getIR() < 50000)
  {
    if (millis() - fingerStartTime >= FINGER_TIMEOUT)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("No Finger");
      lcd.setCursor(0, 1);
      lcd.print("Try Again");

      Serial.println("No finger detected.");

      delay(3000);
      return;
    }

    delay(100);
  }

  tone(buzzerPin, 2000, 200);

  float bpmSum = 0;
  int bpmCount = 0;

  unsigned long startTime = millis();

  lastBeat = 0;
  beatsPerMinute = 0;

  while (millis() - startTime < MEASURE_TIME)
  {
    long irValue = particleSensor.getIR();

    int remain =
        (MEASURE_TIME - (millis() - startTime)) / 1000;

    lcd.setCursor(0, 0);
    lcd.print("Measuring...   ");

    lcd.setCursor(0, 1);
    lcd.print("Time:");
    lcd.print(remain);
    lcd.print("s    ");

    if (checkForBeat(irValue))
    {
      unsigned long currentTime = millis();

      if (lastBeat != 0)
      {
        unsigned long delta = currentTime - lastBeat;

        if (delta > 0)
        {
          beatsPerMinute = 60000.0 / delta;

          if (beatsPerMinute > 20 && beatsPerMinute < 220)
          {
            bpmSum += beatsPerMinute;
            bpmCount++;

            Serial.print("BPM: ");
            Serial.println(beatsPerMinute);
          }
        }
      }

      lastBeat = currentTime;
    }
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Analyzing...");
  lcd.setCursor(0, 1);
  lcd.print("Please Wait");

  delay(1500);

  lcd.clear();

  if (bpmCount == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print("No Reading");
    delay(3000);
    return;
  }

  int avgBPM = bpmSum / bpmCount;

  lcd.setCursor(0, 0);
  lcd.print("Avg:");
  lcd.print(avgBPM);
  lcd.print(" BPM");

  lcd.setCursor(0, 1);

  if (avgBPM < 60)
  {
    lcd.print("BRADYCARDIA");

    tone(buzzerPin, 1000);

    Serial.println("Status: LOW HEART!");
  }
  else if (avgBPM > 100)
  {
    lcd.print("TACHYCARDIA");

    tone(buzzerPin, 1000);

    Serial.println("Status: HIGH HEART!");
  }
  else
  {
    lcd.print("NORMAL");

    noTone(buzzerPin);

    Serial.println("Status: NORMAL");

    tone(buzzerPin, 2500, 150);
  }

  Serial.print("Average BPM = ");
  Serial.println(avgBPM);

  delay(RESULT_TIME);

  noTone(buzzerPin);

  for (int i = 5; i > 0; i--)
  {
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("New Test In");

    lcd.setCursor(0, 1);
    lcd.print(i);
    lcd.print(" sec");

    delay(1000);
  }

  lcd.clear();
}