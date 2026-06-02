#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2      // DHT11 data pin
#define DHTTYPE DHT11 // DHT11 sensor type

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // addr: 0x27, 16 columns, 2 rows

int photoPin = A0;  // photoresistor
int screen = 0;     // current screen (0 or 1)

// get light status label based on analog reading
String getLightStatus(int light) {
    if (light > 700) return "Sunny";
    if (light > 300) return "Cloudy";
    return "Dark";
}

void setup() {
    Serial.begin(9600);
    dht.begin();
    lcd.init();
    lcd.backlight();

    // startup animation
    lcd.setCursor(0, 0);
    lcd.print("Weather Station");
    lcd.setCursor(0, 1);
    lcd.print("Initializing...");
    delay(2000);  // show initializing message
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Full-Stack Eng.");
    lcd.setCursor(3, 1);
    lcd.print("in the Making");
    delay(2000);  // show personal message
    lcd.clear();
}

void loop() {
    float temp = dht.readTemperature();       // celsius
    float humidity = dht.readHumidity();      // percentage
    float heatIndex = dht.computeHeatIndex(temp, humidity, false);  // feels like temp
    int light = analogRead(photoPin);         // 0-1023
    String lightStatus = getLightStatus(light);

    // serial monitor output for debugging
    Serial.print("Temp: "); Serial.print(temp); Serial.println(" C");
    Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");
    Serial.print("Feels like: "); Serial.print(heatIndex); Serial.println(" C");
    Serial.print("Light: "); Serial.print(light); Serial.println(" - " + lightStatus);

    lcd.clear();

    if (screen == 0) {
        // screen 1: temperature + humidity
        lcd.setCursor(0, 0);
        lcd.print("Temp: ");
        lcd.print(temp, 1);   // 1 decimal place
        lcd.print(" C");
        lcd.setCursor(0, 1);
        lcd.print("Humidity: ");
        lcd.print(humidity, 0);  // no decimal
        lcd.print("%");

    } else {
        // screen 2: feels like + light status
        lcd.setCursor(0, 0);
        lcd.print("Feels like:");
        lcd.print(heatIndex, 1);
        lcd.setCursor(0, 1);
        lcd.print("Light: ");
        lcd.print(lightStatus);
    }

    screen = (screen + 1) % 2;  // toggle between screen 0 and 1
    delay(3000);  // show each screen for 3 seconds
}