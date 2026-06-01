#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// pin definitions
int soilPin = A0;   // soil moisture sensor
int buzzerPin = 8;  // buzzer
int pumpPin1 = 5;   // L9110 A-1A
int pumpPin2 = 6;   // L9110 A-1B

int threshold = 350; // above = dry, below = wet

void setup() {
    Serial.begin(9600);
    
    pinMode(buzzerPin, OUTPUT);
    pinMode(pumpPin1, OUTPUT);
    pinMode(pumpPin2, OUTPUT);
    
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Plant Watering");
    lcd.setCursor(0, 1);
    lcd.print("System Ready!");
    delay(2000);  // show welcome message for 2 seconds
}

void loop() {
    int soilValue = analogRead(soilPin);  // read sensor
    
    Serial.print("Soil value: ");
    Serial.println(soilValue);
    
    lcd.setCursor(0, 0);
    lcd.print("Moisture: ");
    lcd.print(soilValue);
    lcd.print("   ");  // clear leftover characters
    
    if (soilValue > threshold) {
        // dry soil — water it!
        analogWrite(pumpPin1, 200);
        analogWrite(pumpPin2, 0);
        tone(buzzerPin, 1000);
        
        lcd.setCursor(0, 1);
        lcd.print("Watering...     ");
        
    } else {
        // wet soil — all good
        analogWrite(pumpPin1, 0);
        analogWrite(pumpPin2, 0);
        noTone(buzzerPin);
        
        lcd.setCursor(0, 1);
        lcd.print("Soil is OK :)   ");
    }
    
    delay(1000);  // check every second
}