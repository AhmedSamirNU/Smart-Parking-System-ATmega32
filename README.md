# 🚗 Smart Parking System | ITI Embedded Systems Final Project

<p align="center">
  <img src="images/cover_image.jpeg" width="900">
</p>

## 📌 Project Overview

The **Smart Parking System** is an Embedded Systems project developed as the final project of the **ITI Embedded Systems Track**.

The system is designed to automate a parking gate using an **ATmega32 Microcontroller**, providing automatic vehicle detection, slot management, gate control, emergency handling, and non-volatile memory storage.

The main goal of this project is to implement a real-world smart parking solution using different embedded peripherals and communication protocols.

---

# 🎯 Project Objectives

- Automate parking gate opening and closing.
- Manage available parking slots dynamically.
- Verify that vehicles actually entered the parking area.
- Provide user feedback through an LCD display.
- Save parking slots state after power failure using EEPROM.
- Implement an emergency evacuation mechanism.

---

# ⚙️ System Features

## 🚘 Vehicle Entry Management

1. A vehicle approaches the parking gate.
2. The ultrasonic sensor detects vehicle presence.
3. LCD displays:


4. The user presses the entry button.
5. The yellow LED turns ON and the system checks slot availability for 3 seconds.

### Available Slots:

- Green LED turns ON.
- LCD displays:


- Servo motor opens the gate.
- 7-Segment display starts countdown:



- After successful entrance:
  - Servo motor closes the gate.
  - Available slots are decreased.

Example:


---

# ⏳ Entry Timeout Handling

To prevent decreasing the number of available slots if a vehicle presses the entry button but does not actually enter:

An additional ultrasonic sensor is installed after the gate to detect vehicle movement inside the entrance path.

System behavior:

- Vehicle detected → Vehicle successfully entered → Slots count decreases.
- No vehicle detected → Timeout condition.

LCD displays:


Then the system returns to:


---

# 🅿️ Parking Slot Management

The system supports:


The available slots are updated automatically after every successful entry or exit.

When all parking spaces are occupied:

- Red LED turns ON.
- Buzzer generates an alert.
- LCD displays:


---

# 🚪 Emergency System

An emergency button is implemented for evacuation purposes.

When the emergency button is pressed:

- The gate opens immediately.
- The parking slots counter is cleared.
- Available slots are restored to:


---

# 💾 EEPROM Data Storage

EEPROM is used to store the current parking slots state.

This provides:

- Data persistence after power failure.
- Automatic restoration of the previous parking state after restarting the system.

---

# 🖥️ Proteus Simulation

<p align="center">
  <img src="images/proteus_simulation.png" width="900">
</p>

The complete system was simulated using **Proteus** before hardware implementation.

The simulation includes:

- ATmega32 Microcontroller
- LCD 16x2
- Servo Motor
- LEDs
- Push Buttons
- 7-Segment Display
- Ultrasonic Sensors
- EEPROM

---

# 🔩 Hardware Implementation

## Initial Parking State

<p align="center">
  <img src="images/initial_slots_state.jpeg" width="500">
</p>

The system starts with:


---

## Entry Button Testing

<p align="center">
  <img src="images/entry_button.jpeg" width="500">
</p>

The entry button is used to request gate opening after vehicle detection.

---

## Exit & Emergency Buttons

<p align="center">
  <img src="images/exit_emergency_buttons.jpeg" width="500">
</p>

The system contains:

- Exit button for vehicle leaving.
- Emergency button for instant gate opening and parking reset.

---

## Real Hardware Connections

<p align="center">
  <img src="images/real_hardware_connections.jpeg" width="900">
</p>

The complete circuit was implemented on real hardware and tested successfully.

---

# 🔄 System Flowchart

<p align="center">
  <img src="images/system_flowchart.jpeg" width="700">
</p>

The flowchart explains the complete system operation starting from vehicle detection until updating parking slots.

---

# 🏗️ Software Architecture

<p align="center">
  <img src="images/software_architecture.jpeg" width="900">
</p>

The project follows a layered embedded software architecture:

## Application Layer (APP)

Responsible for:

- Main system logic.
- Parking slots management.
- Entry sequence.
- Exit sequence.
- Emergency handling.

---

## Hardware Abstraction Layer (HAL)

Includes drivers for:

- LCD
- Servo Motor
- Ultrasonic Sensor
- EEPROM
- 7-Segment Display
- Buttons

---

## Microcontroller Abstraction Layer (MCAL)

Includes low-level drivers for:

- GPIO
- Timers
- PWM
- I2C
- Interrupts

---

# 🛠️ Hardware Components

| Component | Description |
|-----------|-------------|
| ATmega32 | Main Microcontroller |
| LCD 16x2 | User Interface Display |
| HC-SR04 Ultrasonic Sensor | Vehicle Detection |
| Servo Motor | Gate Control |
| LEDs | System Status Indicators |
| Buzzer | Parking Full Alert |
| 7-Segment Display | Gate Countdown |
| EEPROM | Data Storage |
| Push Buttons | Entry / Exit / Emergency Control |

---

# 💻 Development Environment

- **Microcontroller:** ATmega32
- **Programming Language:** Embedded C
- **IDE:** Eclipse
- **Simulation Tool:** Proteus
- **Compiler:** AVR-GCC

---

# 📂 Project Structure


---

# 🚀 Future Improvements

- Add RFID authentication for vehicles.
- Replace push buttons with mobile application control.
- Add multiple parking levels.
- Add cloud monitoring dashboard.
- Implement automatic individual slot detection.

---

# 👨‍💻 Developed By

**Ahmed Samir**  
**Hana Yasser**  
**Mohamed Aboelkasem**  
**Rawan Ayman**

**ITI Embedded Systems Track**

---

# ⭐ Project Highlights

✔ Layered Embedded Software Architecture  
✔ HAL & MCAL Drivers Implementation  
✔ EEPROM Data Persistence  
✔ PWM Servo Motor Control  
✔ Ultrasonic Distance Measurement  
✔ Real Hardware Implementation  
✔ Proteus Simulation  
✔ Embedded C Development

