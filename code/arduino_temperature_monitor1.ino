#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD configuration
LiquidCrystal_I2C lcd(0x27,16,2);

// Temperature limits
const float Tmin = 10.0;
const float Tmax = 50.0;
const float overheatTemp = 45.0;

// LED configuration
const int numLEDs = 8;
int ledPins[numLEDs] = {2,3,4,5,6,7,8,9};

// Sensor pin
const int sensorPin = A0;

// Global temperature variable
float temperature;

// ------- SETUP -------
void setup()
{
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  
  for(int i = 0; i < numLEDs; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }
}

// ------- MAIN LOOP -------
void loop()
{
  temperature = readTemperature();

  updateLEDBar();

  updateLCD();

  handleOverheat();

  delay(200);
}


// ------- Temperature + Filter -------
float readTemperature()
{
  int sum = 0;
  for(int i = 0; i < 15; i ++)
  {
    sum += analogRead(sensorPin);
    delay(5);
  }
  
  int adcValue = sum / 15;
  
  float voltage = (adcValue * 5.0) / 1023.0;
  
  float temp = (voltage - 0.5) * 100.0;
  
  Serial.print("Temperature: ");
  Serial.println(temp);

  return temp;
}


// ------- LED BAR CONTROL -------
void updateLEDBar()
{
  int ledLevel = ((temperature - Tmin) * numLEDs) / (Tmax - Tmin);
  
  if(ledLevel < 0) ledLevel = 0;
  if(ledLevel > numLEDs) ledLevel = numLEDs;
  
  for(int i = 0; i < numLEDs; i ++)
  {
    if(i < ledLevel)
      digitalWrite(ledPins[i],HIGH);
    else
      digitalWrite(ledPins[i],LOW);
  }
}


// ------- LCD DISPLAY -------
void updateLCD()
{
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);
  lcd.print(" C");
  
  lcd.setCursor(0,1);
  
  if(temperature > overheatTemp)
    lcd.print("OVERHEAT! ");
  else
    lcd.print("Status: Normal ");
}


// ------- OVERHEAT WARNING -------
void handleOverheat()
{
  if(temperature > overheatTemp)
  {
    digitalWrite(ledPins[numLEDs - 1],HIGH);
    delay(200);
    digitalWrite(ledPins[numLEDs - 1],LOW);
    delay(200);
  }
}

















