# IoT Weather Station

An Arduino-based weather station that monitors temperature, humidity, and light levels with a rotating I2C LCD display.

## Demo
> Video coming soon — check my [LinkedIn](https://www.linkedin.com/in/yuval-weinsberg-b2aa54284/)

## How It Works
1. DHT11 sensor reads temperature and humidity every 3 seconds
2. Photoresistor reads ambient light level
3. Heat index ("feels like" temperature) is calculated from temp + humidity
4. LCD rotates between two screens every 3 seconds:
   - Screen 1: Temperature + Humidity
   - Screen 2: Feels like + Light status (Sunny/Cloudy/Dark)

## Components
| Component | Purpose |
|---|---|
| SunFounder R3 (Arduino Uno) | Main microcontroller |
| DHT11 | Temperature and humidity sensor |
| Photoresistor + 10kΩ resistor | Ambient light level |
| I2C LCD1602 | Rotating display |

## Wiring
| Component | Arduino Pin |
|---|---|
| DHT11 DATA | Pin 2 |
| Photoresistor (via voltage divider) | A0 |
| LCD SDA | A4 |
| LCD SCL | A5 |

## Skills Learned
- DHT11 sensor reading with Adafruit library
- Voltage divider circuit for analog light sensing
- Rotating LCD display logic with screen state management
- Heat index calculation
- I2C protocol communication
- Serial Monitor debugging

## Setup
1. Install [Arduino IDE 2](https://www.arduino.cc/en/software)
2. Install libraries: `DHT sensor library` and `Adafruit Unified Sensor` by Adafruit, `LiquidCrystal I2C` by Frank de Brabander
3. Upload `weather_station.ino` to Arduino Uno
4. Adjust light thresholds in `getLightStatus()` based on your environment

## Author
Yuval Weinsberg — Software Engineering Student
[LinkedIn](https://www.linkedin.com/in/yuval-weinsberg-b2aa54284/) | [GitHub](https://github.com/weinsbergyuval/arduino-projects)