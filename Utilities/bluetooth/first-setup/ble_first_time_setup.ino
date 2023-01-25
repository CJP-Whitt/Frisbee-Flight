#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif

#define BUFSIZE                        128   // Size of the read buffer for incoming data
#define VERBOSE_MODE                   true  // If set to 'true' enables debug output
#define BLUEFRUIT_UART_MODE_PIN        12    // Set to -1 if unused
#define BLUEFRUIT_SPI_CS               8
#define BLUEFRUIT_SPI_IRQ              7
#define BLUEFRUIT_SPI_RST              4    // Optional but recommended, set to -1 if unused
#define FACTORYRESET_ENABLE            1    // Optional

#ifdef Serial1    // this makes it not complain on compilation if there's no Serial1
  #define BLUEFRUIT_HWSERIAL_NAME      Serial1
#endif

/* ...hardware SPI, using SCK/MOSI/MISO hardware SPI pins and then user selected CS/IRQ/RST */
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1) {};
}

void setup(void) {
  while (!Serial) {};  // required for Flora & Micro
  delay(500);

  Serial.begin(115200);
  Serial.println(F("Adafruit Bluefruit First Time Setup"));
  Serial.println(F("-------------------------------------"));

  /* Initialise the module */
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) ) {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println(F("OK!"));

  if ( FACTORYRESET_ENABLE ) {
    /* Perform a factory reset to make sure everything is in a known state */
    Serial.println(F("Performing a factory reset: "));
    if (!ble.factoryReset()) {
      error(F("Couldn't factory reset"));
    }
  }

  ble.echo(true);  // Disable command echo from Bluefruit

  Serial.println("Requesting Bluefruit info:");
  ble.info();  // Print Bluefruit information
  Serial.println("Updating BLE Module Settings...");
  Serial.println("- Setting BLE Power to Max...");
  ble.println("AT+BLEPOWERLEVEL=4");  // Maximize BLE power level for longest range
  Serial.println("- Setting BLE Public name to @Frisbee Flight BLE");
  ble.println("AT+GAPDEVNAME=Frisbee Flight BLE");  // Update devices advertised name
  Serial.println("Updating BLE Module Settings...DONE");
  Serial.println("\nEntering command mode, enter AT commands at will.");
}

void loop(void) {
  // Display command prompt
  Serial.print(F("AT > "));

  // Check for user input and echo it back if anything was found
  char command[BUFSIZE+1];
  getUserInput(command, BUFSIZE);

  // Send command
  ble.println(command);

  // Check response status
  ble.waitForOK();
}

void getUserInput(char buffer[], uint8_t maxSize) {
  memset(buffer, 0, maxSize);
  while (Serial.available() == 0) {
    delay(1);
  }

  uint8_t count = 0;

  do {
    count += Serial.readBytes(buffer+count, maxSize);
    delay(2);
  } while ((count < maxSize) && !(Serial.available() == 0));
}
