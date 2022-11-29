/*
 Name:		MotorConfig.h
 Created:	11/29/2022
 Author:	CWhitt
 Description: This file holds the motor config params for the main file of this project. Any motor presets can be changed here to work with other hardware.
*/

// HARDWARE PIN SETTINGS
// ----------------------------------------------------------------------------------------------
// The following presets declare the pins to use on the arduino hardware
// ----------------------------------------------------------------------------------------------
const uint8_t wheelMotPin1 = 3; 
const uint8_t wheelMotPin2 = 5;
const uint8_t gantryMotPin = NULL; // TODO: Pick Gantry pwm pin



// ESC PWM SIGNAL SETTINGS
// ----------------------------------------------------------------------------------------------
// The following settings declare the settings to use when communicating with the ESC via PWM
// ----------------------------------------------------------------------------------------------
const int16_t escMinMicros = 1080;
const int16_t escMaxMicros = 1880;
const int16_t escReverseMicros = 1500;
const int16_t escArmDurationMicros = 8000;