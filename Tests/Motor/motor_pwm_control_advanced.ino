/*
 Name:		motor_pwm_control_advanced.ino
 Created:	9/10/2022
 Author:	CWhitt
 Description: This is for testing basic motor functionality using analog input and output to motor using the mor advanced Servo Library
*/

//these values copied from the BlHeli configuration
#define ESC_MIN_THROTTLE		        1080
#define ESC_MAX_THROTTLE		        1880
#define ESC_REVERSE_THROTTLE	        1480

#define ESC_ARM_SIGNAL			        1480
#define ESC_ARM_TIME			        2000

#define ESC1_PIN                           3

#define ESC_DEADZONE_RANGE                0

#define SENSOR_PIN                        A0

#include <Servo.h>

Servo Esc;

void setup()
{
    Serial.begin(115200);
    Serial.println("Initializing");

    Esc.attach(ESC1_PIN, ESC_MIN_THROTTLE, ESC_MAX_THROTTLE);
    InitEsc();

    Serial.println("Done");
}

void loop()
{
	int valueRaw = analogRead(SENSOR_PIN);
	int valueSpeed = map(valueRaw, 0, 1024, ESC_MIN_THROTTLE, ESC_MAX_THROTTLE);
	WriteSpeed(valueSpeed);
} 

void InitEsc()
{
    Esc.writeMicroseconds(ESC_ARM_SIGNAL);
    unsigned long now = millis();
    while (millis() < now + ESC_ARM_TIME) {
		// wait
    }
}

bool IsDeadzone(int speed)
{
    if (speed >= (ESC_REVERSE_THROTTLE - ESC_DEADZONE_RANGE/2) && speed <= (ESC_REVERSE_THROTTLE + ESC_DEADZONE_RANGE/2)) {
        return true;
    }
    return false;
}

void WriteSpeed(int rawSpeed)
{
	int curSpeed = Esc.readMicroseconds();
	int newSpeed = rawSpeed;

	// Deadzone check, and rescaling
    if (IsDeadzone(newSpeed)) { // keep motor off, if in deadzone
    	newSpeed = ESC_REVERSE_THROTTLE;
    } 
	else if (newSpeed > ESC_REVERSE_THROTTLE) { //rescale motor output with deadzone range
		newSpeed = map(newSpeed, (ESC_REVERSE_THROTTLE + ESC_DEADZONE_RANGE/2), ESC_MAX_THROTTLE, ESC_REVERSE_THROTTLE, ESC_MAX_THROTTLE);
	} 
	else if (newSpeed < ESC_REVERSE_THROTTLE) {
		newSpeed = map(newSpeed, ESC_MIN_THROTTLE, (ESC_REVERSE_THROTTLE - ESC_DEADZONE_RANGE/2), ESC_MIN_THROTTLE, ESC_REVERSE_THROTTLE);
	}

    Esc.writeMicroseconds(newSpeed);
	
	Serial.print("| Raw Speed: ");
	Serial.print(rawSpeed);
	Serial.print("\t\t | Out Speed: ");
	Serial.println(newSpeed);
}