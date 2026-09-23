# 💻 Control Logic & Source Code

## 📝 Overview
This folder contains the core automation script (`propeller_car.ino`) that drives the intelligent behavior of the vehicle. The code is written in C++ for the Arduino Nano microcontroller.

## ⚙️ Core Automation Algorithm (State Machine)
The vehicle autonomously adjusts its speed based on real-time distance tracking utilizing an HC-SR04 Ultrasonic Sensor and the `NewPing` library for noise filtering:

1. **Acceleration (Distance > 170 cm):** 
   * Triggers a linear PWM ramp (0 → 255) in step increments to provide smooth acceleration, significantly reducing mechanical stress on the motor and chassis.
2. **Deceleration (120 cm < Distance ≤ 170 cm):** 
   * Gradually reduces the PWM duty cycle, conserving energy and preparing the momentum for a potential stop.
3. **Emergency Braking (Distance ≤ 120 cm):** 
   * Activates a hardware short-brake mechanism via the L298N motor driver (`IN1 = HIGH`, `IN2 = HIGH`), halting the vehicle rapidly with a precision of ±5 cm.

## 🚀 How to Use
Upload the `.ino` file to an Arduino Nano. Ensure the L298N ENA pin is connected to a PWM-capable pin (Pin 9) to allow for variable speed control.