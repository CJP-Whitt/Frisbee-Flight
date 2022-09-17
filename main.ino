
#include <PWM_BLDC_Control.h>

PWM_BLDC_Control* Motor1;
PWM_BLDC_Control* Motor2;

void setup()
{
    Serial.begin(115200);
    Serial.println("Initializing...");
    Motor1 = new PWM_BLDC_Control(5, 1080, 1880, 1480, 4000, 0, 1500);
    Motor2 = new PWM_BLDC_Control(3, 1080, 1880, 1480, 4000, 0, 1500);
    Serial.println("Done");
    
    unsigned long now = millis();
    while (millis() < now + 8000) {
        Motor1->writeDutyCycle(0);
        Motor2->writeDutyCycle(0);
    }
}

void loop()
{
    int valueRaw = analogRead(A0);
    int valueDC = map(valueRaw, 0, 1024, -100, 100);
    Motor1->writeDutyCycle(valueDC);
    Motor2->writeDutyCycle(valueDC);

    Serial.print("RawIn: ");
    Serial.print(valueRaw);
    Serial.print("\t\t| PWMOut(ms): ");
    Serial.print( map( valueDC, -100, 100, 1080, 1880) );
    Serial.print("\t\t| DutyCycle: ");
    Serial.println(valueDC);

} 