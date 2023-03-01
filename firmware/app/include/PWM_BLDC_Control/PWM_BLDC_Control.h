/*
* File: PWM_BLDC_Control.h
*
* Description: This is a library for the advanced control of PWM for BLDC motors. Based on bi-directional BLHeli_S.
*
* Author: Carson Whitt, 09/15/2022
*/

#ifndef PWM_BLDC_CONTROL_H
#define PWM_BLDC_CONTROL_H

#include <Arduino.h>
#include <Servo.h>


class PWM_BLDC_Control {
    public:
        PWM_BLDC_Control(Servo &esc, int16_t escMinMicros, int16_t escMaxMicros, int16_t escDeadzoneMicros,
            int16_t escReverseMicros);
        int8_t readDutyCycle(void);
        void writeDutyCycle(int8_t speed);

    private:
        bool isDeadzone(uint16_t speed);
        void writeSpeed(uint16_t rawSpeed);

        Servo Esc;
        int16_t escMinThrottle;
        int16_t escMaxThrottle;
        int16_t escDeadzoneRange;
        int16_t escReverseThrottle;
        int16_t escCenterThrottle;

};

#endif  // PWM_BLDC_CONTROL_H