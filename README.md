# Environment-Aware-Smart-Proximity-Display-System

# Smart Proximity Display and Alert System

## Overview

This project implements a temperature- and humidity-compensated ultrasonic proximity system using an **Arduino Uno**, **HC-SR04 ultrasonic sensor**, **DHT11 temperature & humidity sensor**, and a **MAX7219 LED matrix display**.

The system measures the distance to nearby objects and visually indicates safety levels using symbols on the LED matrix. Environmental data from the DHT11 sensor is used to dynamically adjust the speed of sound, improving distance accuracy compared to a fixed-value approach.

---

## Key Features

* Real-time ultrasonic distance measurement
* Temperature and humidity compensation for improved accuracy
* Median filtering of ultrasonic readings for stability
* Visual proximity alerts using an 8×8 LED matrix
* Multiple distance-based warning zones
* Modular and readable embedded C++ code



## Hardware Components

* Arduino Uno
* HC-SR04 Ultrasonic Sensor
* DHT11 Temperature & Humidity Sensor
* MAX7219 8×8 LED Matrix Module
* Jumper wires

---

## Pin Connections

### HC-SR04

* TRIG → Arduino D7
* ECHO → Arduino D8
* VCC → 5V
* GND → GND

### DHT11

* DATA → Arduino D5
* VCC → 5V
* GND → GND

### MAX7219 LED Matrix

* DIN → Arduino D10
* CLK → Arduino D13
* CS / LOAD → Arduino D12
* VCC → 5V
* GND → GND

---

## Distance Zones and Display Logic

| Distance (cm) | System State | Display Symbol |
| ------------- | ------------ | -------------- |
| > 100         | Safe         | Smiley face  |
| 50 – 100      | Caution      | Warning symbol |
| 20 – 50       | Warning      | Alert symbol   |
| < 20          | Danger       | Flashing X    |
| < 2 or > 400  | Invalid      | Dashed line    |

---

## How It Works

1. The Arduino triggers the HC-SR04 ultrasonic sensor.
2. The sensor emits an ultrasonic pulse and measures the echo return time.
3. The DHT11 sensor provides ambient temperature and humidity data.
4. The speed of sound is dynamically calculated using environmental data.
5. Distance is computed using the compensated speed of sound.
6. The LED matrix displays a symbol corresponding to the detected distance range.

---

## Accuracy Improvement

Instead of assuming a constant speed of sound, the system uses the formula:

> Speed of sound (m/s) = 331.4 + (0.606 × Temperature) + (0.0124 × Humidity)

This approach improves distance measurement accuracy under varying environmental conditions.

---

## Libraries Used

* LedControl (for MAX7219 LED matrix)
* NewPing (for ultrasonic sensor handling)
* DHT Sensor Library (Adafruit)

---

## Applications

* Parking assistance systems
* Obstacle detection for robotics
* Industrial safety proximity alerts
* Contactless warning systems

---

## Future Improvements

* Non-blocking timing using `millis()`
* Distance averaging with rolling buffers
* Displaying numeric distance values
* Adding audible alerts (buzzer)
* Chaining multiple LED matrices

---

## Author

[Ghena Alhosni]
Embedded Systems / Computer Engineering Student


