/*
 Name:		motor_pwm_control_basic.ino
 Created:	9/10/2022
 Author:	CWhitt
 Description: This is for testing basic motor functionality using analog input and analog output using built in arduino functionality.
*/

int const sensorPin = A0;    // select the input pin for the potentiometer
float static sensorValue = 0.0;  // variable to store the value coming from the sensor

int const pwmPin = 3;
float static pwmValue = 0;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(pwmPin, OUTPUT);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  pwmValue = 255*(sensorValue/1024.0f);

  // keep value in 0-255 range
  if (pwmValue < 0){
    pwmValue = 0;
  }
  if (pwmValue > 255){
    pwmValue = 255;
  }

  // offset range for forward (0->127) reverse (127->255)
  
  analogWrite(pwmPin, pwmValue);
  Serial.println(pwmValue);
}



