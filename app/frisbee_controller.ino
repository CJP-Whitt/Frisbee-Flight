/*
    Name:       frisbee_controller.ino
    Created:    9/1/2022
    Author:     CWhitt
    Description: This is the main file for running the Frisbee Flight app and firmware functionality. Work in progress. 
    Copyright 2023 Carson Whitt
*/

#include <Servo.h>
#include <PWM_BLDC_Control.h>


// TODO(CWhitt): Move configurable params to config file or struct
const uint8_t wheelMotPin1 = 3;
const uint8_t wheelMotPin2 = 5;
const uint8_t gantryMotPin = NULL;  // TODO(CWhitt): Pick Gantry pwm pin
const int16_t escMinMicros = 1080;
const int16_t escMaxMicros = 1880;
const int16_t escReverseMicros = 1500;
const int16_t escArmDurationMicros = 8000;
Servo wheelMot1, wheelMot2, gantryMot;
PWM_BLDC_Control *wheelMot1Controller;
PWM_BLDC_Control *wheelMot2Controller;
PWM_BLDC_Control *gantryMotController;


void setup() {
    Serial.begin(115200);

    // Initialize motors
    Serial.print("Initializing Motors...");
    wheelMot1.attach(wheelMotPin1, escMinMicros, escMaxMicros);
    wheelMot2.attach(wheelMotPin2, escMinMicros, escMaxMicros);
    gantryMot.attach(gantryMotPin, escMinMicros, escMaxMicros);
    wheelMot1Controller = new PWM_BLDC_Control(wheelMot1, escMinMicros, escMaxMicros, 0,
                                               escReverseMicros);
    wheelMot2Controller = new PWM_BLDC_Control(wheelMot2, escMinMicros, escMaxMicros, 0,
                                               escReverseMicros);
    gantryMotController = new PWM_BLDC_Control(gantryMot, escMinMicros, escMaxMicros, 0,
                                               escReverseMicros);
    Serial.println("Done\n");
    Serial.print("Arming Motors...");
    uint64_t now = millis();
    while (millis() < now + escArmDurationMicros) {  // Arm motors
        wheelMot1Controller->writeDutyCycle(0);
        wheelMot2Controller->writeDutyCycle(0);
        gantryMotController->writeDutyCycle(0);
    }
    Serial.println("Done\n");
}

void loop()
{
    int value_raw = analogRead(A0);
    int duty_cylce = map(valueRaw, 0, 1024, -100, 100);
    wheelMot1Controller->writeDutyCycle(duty_cylce);
    wheelMot2Controller->writeDutyCycle(duty_cylce);

    Serial.print("RawIn: ");
    Serial.print(value_raw);
    Serial.print("\t\t| PWMOut(ms): ");
    Serial.print( map( valueDC, -100, 100, 1080, 1880) );
    Serial.print("\t\t| DutyCycle: ");
    Serial.println(duty_cylce);

}
