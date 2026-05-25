# Automatic Plant Watering System (Arduino)

A moisture-based irrigation system built with an Arduino that monitors soil moisture and provides feedback for potential automated watering. The system uses calibrated sensor thresholds, noise filtering, and timed measurement cycles to evaluate soil conditions.

---

## Project Overview

This project was built to explore embedded systems concepts such as:
- Analog sensor reading
- Signal filtering and averaging
- Non-blocking timing with `millis()`
- Hardware power control
- Calibration of real-world sensors

The system measures soil moisture every minute and classifies soil conditions from soaked to very dry based on calibrated reference values.

An LED blinks during each measurement cycle to show when the system is actively reading sensor data.

---

## Features

- Timed sensor readings (once every 60 seconds)
- Noise reduction using averaging (10 samples per reading)
- Sensor power control (only powered during measurement)
- LED indicator during measurement cycles
- Moisture classification based on calibrated values

---

## Moisture Calibration

The system is calibrated using two reference points:

| Condition | Value |
|----------|------|
| Wet soil (water reference) | ~270 |
| Dry soil (air reference)   | ~504 |

### Moisture classification ranges:

- Soaked: < 270  
- Wet: 270 – 347  
- Damp: 348 – 425  
- Dry: 426 – 503  
- Very dry: ≥ 504  

These values are split evenly between the two calibration points.

---

## Measurement Cycle

Every 60 seconds, the system:

1. Powers on the soil moisture sensor  
2. Blinks an LED to show a measurement is happening  
3. Takes 10 readings from the sensor  
4. Averages the readings  
5. Powers off the sensor  
6. Classifies the moisture level  
7. Prints the result to the Serial Monitor  

---

## Hardware Setup

Arduino Uno is connected to:

- Soil moisture sensor connected to analog pin A0  
  - Sensor is powered using a digital pin (sensor power control)

- Relay module controlling a 12V water pump  
  - Pump powered from external 12V supply

- LED connected to a digital pin  
  - Used to indicate when measurements are being taken

- 12V power supply connected to pump through relay

- Water reservoir connected to pump via tubing

---

## Code Concepts Used

### Non-blocking timing
Uses `millis()` instead of `delay()` to ensure the system runs continuously while still taking readings at fixed intervals.

### Noise reduction
Each measurement is based on the average of 10 analog readings to stabilize sensor output.

### Sensor power control
The soil moisture sensor is only powered during readings to reduce corrosion and improve measurement stability.

### LED feedback
The LED turns on or blinks during measurement cycles to show the system is actively working.

---

## Limitations

- Moisture thresholds are simplified and linearly divided
- No hysteresis between states, so values near boundaries may switch categories
- Pump automation logic is not yet implemented (system is currently monitoring only)

---

## Challenges Faced

### Sensor calibration
Finding stable dry and wet reference values required testing in real conditions.

### Noisy readings
Raw sensor values fluctuated, so averaging was needed to stabilize results.

### Timing system
Switching from delay-based code to millis-based timing was necessary to keep the system responsive.

### Wiring complexity
Combining low-voltage logic with a 12V pump system required careful wiring and debugging.

---

## Lessons Learned

- Real sensors require calibration to be useful
- Averaging improves stability of analog readings
- millis() is important for non-blocking embedded systems
- Powering sensors only when needed improves reliability
- Hardware debugging is often harder than software debugging
- System design must consider both code and physical wiring

---

## Future Improvements

- Refactor code into a state machine (IDLE, MEASURE, WATERING, COOLDOWN)
- Add pump automation with safe runtime limits
- Add hysteresis to prevent rapid switching near thresholds
- Move wiring from breadboard to perfboard or PCB
- Add calibration mode using a button
- Add timed watering modes (e.g. 30 min, 1 hour, 2 hours)

The full code is available here:
[View soure Code](Code/Main.ino)
