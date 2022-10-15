/*
* File: PWM_BLDC_Control.cpp
*
* Description: This is a library for the advanced control of PWM for BLDC motors. Based on bi-directional BLHeli_S.
*
* Author: Carson Whitt, 09/15/2022
*/

#include "PWM_BLDC_Control.h"
#include <Arduino.h>
#include <Servo.h>

PWM_BLDC_Control::PWM_BLDC_Control(Servo &esc, int16_t escMinMicros, int16_t escMaxMicros, int16_t escDeadzoneMicros, int16_t escReverseMicros) {
    /* Class constructor: Initialize necessary class inputs
        - escMin/MaxMicros: Min and max PWM signal range in (us) to represent 0 to 100% duty cycle
        - escArmSignalMicros: PWM (us) signal to send to ESC for arming
        - escArmSignalMillis: Time in (us) to send the arm signal
        - escDeadzoneMicros: Range in (us) around the reverse PWM signal to send 0% duty cycle to motor
        - escReverseMicros: PWM signal midpoint in (us) that corresponds to the bi-directional point
    */
   Esc = esc;
   escMinThrottle = escMinMicros;
   escMaxThrottle = escMaxMicros;
   escDeadzoneRange = escDeadzoneMicros;
   escReverseThrottle = escReverseMicros;
   escCenterThrottle = escReverseMicros - 20; // BLHeli_S has 40us below reverse throttle reserved for arming
   
}

int8_t PWM_BLDC_Control::readDutyCycle(void) {
    /* readDutyCycle: Get current throttle input scaled between -100% and 100%
    */
    return map(Esc.readMicroseconds(), escMinThrottle, escMaxThrottle, -100, 100);
}

void PWM_BLDC_Control::writeDutyCycle(int8_t speed) {
    /* writeDutyCycle: Control motor using duty cycle
        - speed: Value from -100% to 100% duty cycle
    */
    if (speed > 100) { speed = 100; }
    if (speed < -100) {speed = -100; }

    writeSpeed( map(speed, -100, 100, escMinThrottle, escMaxThrottle) );
}

bool PWM_BLDC_Control::isDeadzone(uint16_t speed) {
    /* isDeadzone: Check if speed is within the deadzone range, if so return true, else false.
        - speed: The PWM signal (us)
    */ 
    if (speed >= (escCenterThrottle - escDeadzoneRange/2) && speed <= (escCenterThrottle + escDeadzoneRange/2)) {
        return true;
    }
    return false;
}

void PWM_BLDC_Control::writeSpeed(uint16_t rawSpeed) {
    /* writeSpeed: Control PWM signal sent to motor
        - rawSpeed: PWM signal (us) to send to motor
    */
    uint16_t curSpeed = Esc.readMicroseconds();
	uint16_t newSpeed = rawSpeed;

	// Deadzone check, and rescaling
    if (isDeadzone(newSpeed)) { // keep motor off, if in deadzone
    	newSpeed = escCenterThrottle;
    } 
	else if (newSpeed > escCenterThrottle) { // rescale motor output with deadzone range
		newSpeed = map(newSpeed, (escCenterThrottle + escDeadzoneRange/2), escMaxThrottle, escCenterThrottle, escMaxThrottle);
	} 
	else if (newSpeed < escCenterThrottle) {
		newSpeed = map(newSpeed, escMinThrottle, (escCenterThrottle - escDeadzoneRange/2), escMinThrottle, escCenterThrottle);
	}

    Esc.writeMicroseconds(newSpeed);
}