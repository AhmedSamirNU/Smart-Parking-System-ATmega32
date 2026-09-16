# 🚗 Smart Parking System — ATmega32 Embedded Project

[![Microcontroller](https://img.shields.io/badge/Microcontroller-ATmega32-blue.svg)](https://www.microchip.com/)
[![Language](https://img.shields.io/badge/Language-Embedded%20C-orange.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![IDE](https://img.shields.io/badge/IDE-Eclipse%20%2F%20Microchip%20Studio-brightgreen.svg)](https://www.eclipse.org/)
[![Simulation](https://img.shields.io/badge/Simulation-Proteus%208%20Professional-red.svg)](https://www.labcenter.com/)

An automated, robust **Embedded Smart Parking System** developed as the final graduation project for the **Information Technology Institute (ITI)** Embedded Systems Training Program. The system manages entry gate access, slot availability tracking with double-verification, emergency override protocols, non-volatile state persistence, and real-time visual/auditory hardware feedback.

---

![Project Cover Header](images/cover_image.jpeg)

---

## 📌 Key Features & Highlights

- **🚦 Entry Access Control & Ultrasonic Detection:**
  - Entrance Ultrasonic Sensor detects approaching vehicles and prompts drivers via a 16x2 LCD display (`WELCOME` $\rightarrow$ `PRESS ENTER BUTTON`).
  - Pressing the **Entry Button** triggers a **3-second diagnostic check** (Yellow LED illuminated) to verify slot availability.

- **🛡️ Double-Verification Anti-Cheating / Entry Detection Logic:**
  - Gate servo opens (Green LED ON, LCD displays `GATE OPEN`) and a 7-Segment Display counts down from `9` to `0`.
  - **Secondary Ultrasonic Sensor** mounted above the inner entryway measures overhead height-to-ground distance.
  - If a vehicle physically enters, the distance drop confirms passage $\rightarrow$ Gate closes, slot count decrements.
  - **Timeout Safeguard:** If no vehicle passes through after opening, the system aborts entry, displays `TIME OUT / TRY AGAIN`, resets to `PRESS ENTER BUTTON`, and preserves the existing slot counter.

- **💾 Non-Volatile State Memory (EEPROM Integration):**
  - Current occupied/available slot count is permanently logged into external/internal **EEPROM**.
  - Restores precise slot status instantly upon power loss or system reset.

- **🚨 Emergency Override Protocol:**
  - Dedicated **Emergency Button** triggers immediate evacuation mode.
  - Instantly opens the barrier servo and clears/resets all 5 parking slots.

- **🚫 Full Capacity Management:**
  - When all 5 slots are occupied, the system switches to `FULL` status on the LCD, turns on the **Red Warning LED**, and activates an **Auditory Buzzer**.

---

## 🏗️ Layered Software Architecture

The software is structured following **Layered Embedded C Architecture** (MCAL, HAL, App) to ensure strict modularity, clean hardware abstraction, and ease of porting:
