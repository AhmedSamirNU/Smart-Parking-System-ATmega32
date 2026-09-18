# 🚗 Smart Parking System

> An embedded systems final project built on the **ATmega32** microcontroller, developed as part of the **ITI (Information Technology Institute)** embedded systems track.

![Cover](images/cover_image.jpeg)

---

## 📋 Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [System Flow](#system-flow)
- [Hardware Components](#hardware-components)
- [Pin Configuration](#pin-configuration)
- [Software Architecture](#software-architecture)
- [Proteus Simulation](#proteus-simulation)
- [Real Hardware](#real-hardware)
- [Team](#team)

---

## Project Overview

The Smart Parking System automates gate control and real-time slot management for a 5-slot parking lot. A car approaching the entrance is detected by an ultrasonic sensor; the driver presses a button to request entry, the system checks availability, opens the gate via a servo motor, and confirms the car has actually passed through using a second ultrasonic sensor mounted above the gateway. Slot count is persisted in EEPROM so it survives power cycles.

---

## Features

| Feature | Details |
|---|---|
| 🚘 Car Detection | HC-SR04 ultrasonic sensor detects cars at the entrance (< 20 cm) |
| ✅ Slot Availability Check | 3-second visual check with Yellow LED before opening gate |
| 🚦 Traffic LEDs | Green = available / Yellow = checking / Red = full or denied |
| 🔁 Servo Gate Control | SG90 servo opens and closes the barrier automatically |
| ⏱ 7-Segment Countdown | Counts down 9 → 0 while gate is open |
| 🔍 Entry Confirmation | Second ultrasonic sensor above the gateway confirms the car entered |
| ⏰ Timeout Handling | If car doesn't pass through, shows TIME OUT → TRY AGAIN |
| 🚪 Exit Flow | Exit button opens gate, increments slot count, saves to EEPROM |
| 🚨 Emergency Override | Emergency button opens gate immediately and releases one slot |
| 💾 EEPROM Persistence | Slot count saved to AT24C02 via I²C — survives power loss |
| 📟 UART Logging | All system events streamed to terminal for debugging |

---

## System Flow

![Flowchart](images/system_flowchart.jpeg)

### Entry Flow

Car detected by US1 (< 20 cm)
│
▼
LCD: "WELCOME"
LCD: "PRESS ENTER BUTTON"
│
[ENTRY button pressed]
│
▼
Yellow LED ON → CHECKING (3 s)
│
┌────┴────┐
│ │
SLOTS > 0 SLOTS = 0
│ │
▼ ▼
Green LED Red LED + Buzzer
GATE OPEN LCD: "PARKING FULL"
Servo 90°
7-Seg: 9→0
│
▼
US2 detects car passed?
│
┌─┴─┐
YES NO
│ │
▼ ▼
SLOTS-- TIME OUT
EEPROM TRY AGAIN
saved
Gate closes
LCD: SLOTS=N


### Exit Flow

[EXIT button pressed]
│
▼
LCD: "BYE BYE / DRIVE SAFE"
Gate opens → countdown 9→0
Gate closes → SLOTS++
EEPROM saved → LCD: SLOTS=N


### Emergency Flow

[EMERGENCY button pressed]
│
▼
Red + Yellow LEDs ON
LCD: "! EMERGENCY !"
Gate opens immediately
Hold 3 s after release
Gate closes → SLOTS++
EEPROM saved → LCD: SLOTS=N


---

## Hardware Components

| Component | Role |
|---|---|
| ATmega32 @ 8 MHz | Main microcontroller |
| HC-SR04 (×2) | US1: entrance detection / US2: passage confirmation |
| SG90 Servo Motor | Gate actuator |
| LCD 16×2 (HD44780) | Status display — 4-bit mode |
| 7-Segment Display | Gate-open countdown (9 → 0) |
| LEDs ×3 (R/Y/G) | Traffic-light style status indicators |
| Active Buzzer | Audio alert for full parking / denied entry |
| Push Buttons ×3 | Entry / Exit / Emergency |
| AT24C02 EEPROM | Non-volatile slot count storage via I²C |

---

## Pin Configuration

| Port | Pin | Connected To |
|---|---|---|
| PORTA | PA0 | LCD RS |
| PORTA | PA1 | LCD RW |
| PORTA | PA2 | LCD EN |
| PORTA | PA3 | Buzzer |
| PORTA | PA4 | LED RED |
| PORTA | PA5 | LED YELLOW |
| PORTA | PA6 | LED GREEN |
| PORTA | PA7 | US2 TRIG |
| PORTB | PB0–PB6 | 7-Segment (a–g) |
| PORTC | PC2 | US1 TRIG |
| PORTC | PC3 | US1 ECHO |
| PORTC | PC4–PC7 | LCD D4–D7 |
| PORTD | PD2 | US2 ECHO |
| PORTD | PD3 | EMERGENCY Button (pull-up) |
| PORTD | PD5 | Servo PWM (OC1A — Timer1) |
| PORTD | PD6 | ENTRY Button (pull-up) |
| PORTD | PD7 | EXIT Button (pull-up) |

---

## Software Architecture

![Software Architecture](images/software_architecture.jpeg)

The codebase follows a strict **3-layer embedded architecture**:

┌─────────────────────────────┐
│ APP Layer │ PARKING_program.c / config / interface
│ (Application Logic) │ State machine — calls HAL only
├─────────────────────────────┤
│ HAL Layer │ LCD · LED · BUZZER · SERVO
│ (Hardware Abstraction) │ SEVEN_SEG · ULTRASONIC · BUTTON · EEPROM
├─────────────────────────────┤
│ MCAL Layer │ DIO · TIMER · PWM · UART · I2C
│ (MCU Abstraction) │ Direct register manipulation
└─────────────────────────────┘


Each driver follows the naming convention:

<MODULE>_program.c — implementation
<MODULE>_interface.h — public API
<MODULE>_config.h — user-configurable defines


### MCAL Drivers Used

| Driver | Why |
|---|---|
| **DIO** | GPIO abstraction for all ports — SET/CLR/GET bit macros |
| **TIMER1** | Fast PWM Mode 14, 50 Hz → servo angle control via OC1A |
| **PWM** | Thin wrapper over TIMER1 for duty-cycle → angle mapping |
| **UART** | 9600 baud 8N1 — debug telemetry for all system events |
| **I²C / TWI** | 100 kHz standard mode — AT24C02 EEPROM read/write |

---

## Proteus Simulation

![Proteus Simulation](images/proteus_simulation.png)

Full circuit simulated in **Proteus 8** before hardware assembly.  
Virtual instruments used: oscilloscope (PWM signal), virtual terminal (UART log).

---

## Real Hardware

### Initial State — 5 Slots Available

![Slots = 5](images/initial_slots_state.jpeg)

### Entry Button

![Entry Button](images/entry_button.jpeg)

### Exit & Emergency Buttons

![Exit and Emergency Buttons](images/exit_emergency_buttons.jpeg)

### Hardware Connections

![Real Hardware Connections](images/real_hardware_connections.jpeg)

---

## Project Structure

FINAL_PARKING_PROJECT/
├── main.c
├── STD_TYPES.h
├── BIT_MATH.h
├── APP/
│ └── PARKING/
│ ├── PARKING_program.c
│ ├── PARKING_interface.h
│ └── PARKING_config.h
├── HAL/
│ ├── LCD/
│ ├── LED/
│ ├── BUZZER/
│ ├── SERVO/
│ ├── SEVEN_SEG/
│ ├── ULTRASONIC/
│ ├── BUTTON/
│ └── EEPROM/
├── MCAL/
│ ├── DIO/
│ ├── TIMER/
│ ├── PWM/
│ ├── UART/
│ └── I2C/
└── proteus simulation/


---

## Team

| Name |
|---|
| Ahmed Samir |
| Hana Yasser |
| Mohamed Aboelkasem |
| Rawan Ayman |

**Instructors:** Mahmoud Fared · Mostafa Aladly

**Program:** ITI — Information Technology Institute · Embedded Systems Track · 2026
