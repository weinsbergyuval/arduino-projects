#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// pin definitions
int soilPin = A0;   // soil moisture sensor
int buzzerPin = 8;  // buzzer
int pumpPin1 = 5;   // L9110 A-1A
int pumpPin2 = 6;   // L9110 A-1B

int threshold = 350; // above = dry, below = wet
bool wasWatering = false;  // track state to play melody only once

void playConfirmBeep() {
    tone(buzzerPin, 523, 100);  // C note
    delay(150);
    tone(buzzerPin, 659, 100);  // E note
    delay(150);
    tone(buzzerPin, 784, 150);  // G note
    delay(200);
    noTone(buzzerPin);
}

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
        
        // play melody only when watering STARTS, not every second
        if (!wasWatering) {
            playConfirmBeep();
            wasWatering = true;
        }
        
        lcd.setCursor(0, 1);
        lcd.print("Watering...     ");
        
    } else {
        // wet soil — all good
        analogWrite(pumpPin1, 0);
        analogWrite(pumpPin2, 0);
        noTone(buzzerPin);
        wasWatering = false;  // reset so melody plays next time
        
        lcd.setCursor(0, 1);
        lcd.print("Soil is OK :)   ");
    }
    
    delay(1000);  // check every second
}