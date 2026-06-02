# Automatic Plant Watering System

An Arduino-based automated irrigation system that monitors soil moisture and activates a water pump when the soil is dry.

## Demo
> Watch the build on [LinkedIn](https://www.linkedin.com/in/yuval-weinsberg-b2aa54284/)

## How It Works
1. Capacitive soil moisture sensor reads soil humidity every second
2. If moisture value is above threshold (dry) → pump activates, buzzer alerts, LCD shows "Watering..."
3. If moisture value is below threshold (wet) → pump stops, LCD shows "Soil is OK :)"

## Components
| Component | Purpose |
|---|---|
| SunFounder R3 (Arduino Uno) | Main microcontroller |
| Capacitive Soil Moisture Sensor v1.2 | Reads soil humidity |
| Centrifugal Pump + L9110 Motor Driver | Waters the plant |
| I2C LCD1602 | Displays system status |
| Buzzer | Dry soil audio alert |

## Wiring
| Component | Arduino Pin |
|---|---|
| Soil Sensor (AOUT) | A0 |
| Buzzer (+) | Pin 8 |
| L9110 A-1A | Pin 5 (PWM) |
| L9110 A-1B | Pin 6 (PWM) |
| LCD SDA | A4 |
| LCD SCL | A5 |

## Skills Learned
- Analog sensor reading with `analogRead()`
- I2C protocol for LCD communication
- Motor control with L9110 driver and PWM
- Threshold-based decision logic in embedded C++
- Circuit design with power rails on breadboard
- CH340 USB driver setup on macOS

## Setup
1. Install [Arduino IDE 2](https://www.arduino.cc/en/software)
2. Install libraries: `LiquidCrystal I2C` by Frank de Brabander
3. Upload `plant_watering_system.ino` to Arduino Uno
4. Adjust `threshold` value (default 350) based on your sensor calibration

## Author
Yuval Weinsberg — Software Engineering Student