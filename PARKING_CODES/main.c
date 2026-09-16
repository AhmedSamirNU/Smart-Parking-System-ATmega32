/*
 * main.c
 *
 * Smart Parking System — ITI Final Project
 * Author : AHMED SAMIR
 * Date   : Sep 2026
 *
 * ============================================================
 * PIN MAP  (ATmega32 @ 8 MHz)
 * ============================================================
 *
 *  LCD (8-bit mode)
 *      RS  -> PA0
 *      RW  -> PA1
 *      EN  -> PA2
 *      D0..D7 -> PC0..PC7
 *
 *  LEDs
 *      RED    -> PA4
 *      YELLOW -> PA5
 *      GREEN  -> PA6
 *
 *  BUZZER  -> PA3
 *
 *  SERVO   -> PD5  (OC1A — Timer1 Fast PWM 50 Hz)
 *
 *  7-SEGMENT (common anode)
 *      PB0..PB6  (segments a..g)
 *      NOTE: PB7 is reserved for US2 TRIG — do NOT connect segment dp
 *
 *  ULTRASONIC 1  (gate entrance — detects approaching car)
 *      TRIG -> PD0
 *      ECHO -> PD1
 *
 *  ULTRASONIC 2  (passage sensor — confirms car entered garage)
 *      TRIG -> PB7
 *      ECHO -> PD2
 *
 *  BUTTONS (active-LOW, internal pull-up enabled)
 *      ENTRY -> PD6
 *      EXIT  -> PD7
 *
 * ============================================================
 */

#define F_CPU 8000000UL

#include "STD_TYPES.h"
#include "APP/PARKING/PARKING_interface.h"


int main(void)
{
    /* Initialise all peripherals and show splash screen */
    PARKING_Init();

    /* Main loop — runs the parking state machine forever */
    while(1)
    {
        PARKING_SystemRun();
    }

    return 0;
}
