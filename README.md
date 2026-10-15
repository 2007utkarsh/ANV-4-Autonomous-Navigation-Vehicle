# ANV-4 | Autonomous Navigation Vehicle

### Arduino IDE Source Code
**HORIZON 2.0 — BUILDATHON | Problem Statement 02**

## Project Overview
ANV-4 is an Arduino-based autonomous robotic vehicle designed to detect obstacles and navigate independently without continuous human intervention.

This repository contains the Arduino IDE source code responsible for sensor integration, navigation decisions, servo scanning, and motor control.

## Hardware Requirements

| Component | Purpose |
|---|---|
| Arduino UNO | Main controller |
| HC-SR04 | Obstacle detection |
| L298N Motor Driver | Motor control |
| SG90 Servo Motor | Directional scanning |
| 4 DC Gear Motors | Vehicle movement |
| Battery Pack | Power supply |
| Robot Chassis | Structural support |

## Software Requirements
- Arduino IDE
- Embedded C/C++
- Arduino Servo Library

## Working Principle

The proposed control sequence follows:

**START → INITIALIZE → SENSE → DECIDE → ACT → REPEAT**

1. Arduino initializes the sensors and motors.
2. Ultrasonic sensor measures the distance ahead.
3. If the path is clear, the vehicle moves forward.
4. If an obstacle is detected, the vehicle stops.
5. Servo scans the left and right directions.
6. The vehicle turns toward the clearer direction.
7. The navigation cycle repeats continuously.

## Navigation Logic

| Sensor Condition | Action |
|---|---|
| Distance > 20 cm | Move Forward |
| Distance ≤ 20 cm | Stop |
| Obstacle Detected | Scan Surroundings |
| Clear Direction Found | Turn |
| No Safe Path | Remain Stopped |

*The distance threshold can be adjusted according to testing conditions.*

## How to Run the Code

1. Download and install Arduino IDE.
2. Open the ANV-4 `.ino` source file.
3. Connect Arduino UNO using a USB cable.
4. Select the correct board and COM port.
5. Install the required Servo library if needed.
6. Verify and upload the program.
7. Disconnect USB and power the robot using its designated supply.
8. Place the vehicle in a controlled testing environment.

## Key Features

- Real-time obstacle detection.
- Autonomous navigation.
- Servo-based directional scanning.
- Automatic motor control.
- Emergency stopping logic.
- Continuous sensor monitoring.

## UN SDG Connection

**SDG 9 — Industry, Innovation and Infrastructure**

ANV-4 demonstrates practical engineering innovation through embedded programming, intelligent sensing, and autonomous robotic mobility.

## Future Improvements

- Advanced path-planning algorithms.
- Camera-based object detection.
- Wireless monitoring.
- Improved navigation accuracy.
- Energy-efficient motor control.

---

**Developed for HORIZON 2.0 BUILDATHON**

*ANV-4 — Sense. Decide. Navigate.*
