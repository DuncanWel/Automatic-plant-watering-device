# Automatic Plant Watering System (Arduino)

An Arduino-based automatic plant watering system that monitors soil moisture and activates a water pump when the soil becomes dry. The system uses sensor thresholds, noise filtering, and state cycles to evaluate soil conditions and water plants.

---

## Project Overview

This project was built to learn embedded systems concepts such as:
- Analog sensor reading
- Signal filtering and averaging
- Using `millis()` to create non-blocking timers instead of `delay()` when needed
- Hardware power control
- State machines

The system measures soil moisture every minute and converts the sensor readings into a calibrated moisture percentage before classifying the soil as wet or dry.

An LED blinks during each measurement cycle to show when the system is actively reading sensor data.

The circuit includes a button to disable the cycle and reduce power consumption.

---

## Features

- Finite state machine loop
- Timed sensor readings (once every 60 seconds)
- Noise reduction using averaging (10 samples per reading)
- Sensor power control (only powered during measurement)
- LED indicator during measurement cycles
- Moisture classification based on calibrated values

---

## Moisture Levels & Calibration

During calibration, the sensor reading in the air was measured at 504, while the reading for water was recorded at 270. Sensor readings are converted into a moisture percentage, where 0% represents the calibrated air value and 100% represents the calibrated water value.


---

## Measurement Cycle

Every 60 seconds, the system:

1. Powers on the soil moisture sensor  
2. Blinks an LED to show a measurement is happening  
3. Takes 10 readings from the sensor  
4. Averages the readings  
5. Powers off the sensor  
6. Moves on to the next state

---

## Hardware Setup

The system consists of:

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

### State machine
Uses a finite state machine to separate measuring, classifying, watering and standby behavior. This makes the program easier to read, maintain and expand, compared to placing all the logic inside `loop()`.

### Non-blocking timing
Uses `millis()` to schedule timed measurements instead of relying on blocking delays.

### Noise reduction
Each measurement is based on the average of 10 analog readings to stabilize sensor output.

### Sensor power control
The soil moisture sensor is only powered during readings to reduce corrosion and improve measurement stability.

### LED feedback
The LED turns on or blinks during measurement cycles to show the system is actively working.

---

## Limitations

- Precalibrated values for wet and dry moisture levels.
- Moisture thresholds are simplified and split evenly
- No hysteresis between states, so values near boundaries may switch categories

---

## Challenges Faced

### Sensor calibration
Finding stable dry and wet reference values required testing in real conditions.

### Noisy readings
Raw sensor values fluctuated, so averaging was needed to stabilize results.

### Timing system
Switching from delay-based code to millis-based timing was necessary to keep the system responsive.

### Wiring complexity
Combining low-voltage logic with a 12V pump system required new wiring.

---

## Lessons Learned

- Real sensors require calibration to be useful
- Averaging improves stability of analog readings
- using `millis()` is important for non-blocking embedded systems
- Powering sensors only when needed improves reliability
- Hardware debugging is often harder than software debugging
- System design must consider both code and physical wiring

---

## Future Improvements

- Add hysteresis to prevent rapid switching near thresholds
- Move wiring from breadboard to perfboard or PCB
- Add calibration mode using a button
- Add timed watering modes (e.g. 30 min, 1 hour, 2 hours)

## Images, Diagram and Important Notes About the Diagram

Images of the automatic watering device can be found here:
[View the images](Diagrams/)

The wiring diagram is available here:
[View the wiring diagram](Diagrams/Wiring.png)

### Note on Wiring Diagram
This wiring diagram was created using Tinkercad for simulation purposes.
Since Tinkercad does not include all real-world components, some parts are represented using equivalent placeholders (e.g. DC motor for pump, generic relay model).
The physical build uses an SRD-05VDC-SL-C relay module with built-in driver and protection circuitry.
The diagram is intended to show system logic and connections rather than an exact physical layout.

## Code
The full code is available here:
[View source Code](Code/Main.ino)
