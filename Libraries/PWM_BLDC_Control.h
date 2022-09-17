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
        PWM_BLDC_Control();
        PWM_BLDC_Control(uint8_t pin, int16_t escMinMicros, int16_t escMaxMicros, int16_t escArmSignalMicros, 
                                        int16_t escArmLengthMillis, int16_t escDeadzoneMicros, int16_t escReverseMicros);
        int8_t readDutyCycle(void);
        void writeDutyCycle(int8_t speed);
        void escArm(void);

    private:
        bool isDeadzone(uint16_t speed);
        void writeSpeed(uint16_t rawSpeed);

        Servo Esc;
        int16_t escMinThrottle;
        int16_t escMaxThrottle;
        int16_t escArmSignal;
        int16_t escArmTime;
        int16_t escDeadzoneRange;
        int16_t escReverseThrottle;
        int16_t escCenterThrottle;
        uint8_t pwmPin;

};

#endif // PWM_BLDC_CONTROL_H