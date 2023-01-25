#include <PWM_BLDC_Control.h>


const uint8_t wheelMotPin1 = 3;
const uint8_t wheelMotPin2 = 5;
const uint8_t gantryMotPin = NULL;
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
    Serial.print("Initializing...");

    // Initialize servo objects
    wheelMot1.attach(wheelMotPin1, escMinMicros, escMaxMicros);
    wheelMot2.attach(wheelMotPin2, escMinMicros, escMaxMicros);
    gantryMot.attach(gantryMotPin, escMinMicros, escMaxMicros);

    // Instantiate motor controllers
    wheelMot1Controller = new PWM_BLDC_Control(wheelMot1, escMinMicros, escMaxMicros, 0,
                                               escReverseMicros);
    wheelMot2Controller = new PWM_BLDC_Control(wheelMot2, escMinMicros, escMaxMicros, 0,
                                               escReverseMicros);
    gantryMotController = new PWM_BLDC_Control(gantryMot, escMinMicros, escMaxMicros, 0,
                                               escReverseMicros);
    Serial.println("Done\n");

    // Arm motors
    Serial.print("Arming Motors...");
    uint64_t now = millis();
    while (millis() < now + escArmDurationMicros) {
        wheelMot1Controller->writeDutyCycle(0);
        wheelMot2Controller->writeDutyCycle(0);
        gantryMotController->writeDutyCycle(0);
    }
    Serial.println("Done\n");
}

void loop() {
    int valueRaw = analogRead(A0);
    int valueDC = map(valueRaw, 0, 1024, -100, 100);
    wheelMot1Controller->writeDutyCycle(valueDC);
    wheelMot2Controller->writeDutyCycle(valueDC);

    Serial.print("RawIn: ");
    Serial.print(valueRaw);
    Serial.print("\t\t| PWMOut(ms): ");
    Serial.print(map( valueDC, -100, 100, 1080, 1880));
    Serial.print("\t\t| DutyCycle: ");
    Serial.println(valueDC);
}
