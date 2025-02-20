/**
 * @file    AD5259_ReadWriteEEPROM.ino
 * @brief   Example code for interfacing Arduino with AD5259 digital potentiometer.
 * @author  Thebestia90 
 * @date    20-Feb-2025
 * @details This example demonstrates how to initialize and communicate with the AD5259 digital potentiometer via I2C. It shows how to write a value to the potentiometer, store it in EEPROM, and then read it back from EEPROM to set the RDAC value.
 */
 #include <Wire.h>
#include <AD5259.h>

// Select the correct I2C address based on AD0 and AD1 pin connections
#define DIGIPOT_ADDR 0x18  ///< AD0 = GND, AD1 = GND
// #define DIGIPOT_ADDR 0x19 ///< AD0 = VDD, AD1 = GND
// #define DIGIPOT_ADDR 0x1A ///< AD0 = GND, AD1 = VDD
// #define DIGIPOT_ADDR 0x1B ///< AD0 = VDD, AD1 = VDD

AD5259 digipot(DIGIPOT_ADDR);

void setup() {
  Serial.begin(115200);
#if defined(ESP32)
  Wire.begin(21, 22);
#elif defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_ARCH_MBED_RP2040) || defined(ARDUINO_ARCH_RP2350)
  Wire.setSDA(16);
  Wire.setSCL(17);
  Wire.begin();
  Wire.setClock(400000);
#else
  Wire.begin();
#endif

  if (digipot.begin()) {
    Serial.println("AD5259 Connected!");
  } else {
    Serial.println("AD5259 NOT found!");
    while (true) {
      delay(100);
    }
  }

  // Write a value to EEPROM (e.g. 128)
  digipot.write(128); // Set the RDAC value
  digipot.writeEEPROM(128); // Store the value in EEPROM
  Serial.println("Written 128 to EEPROM");

  // Read the value from EEPROM
  int storedVal = digipot.readEEPROM();
  Serial.print("Stored RDAC Value from EEPROM: ");
  Serial.println(storedVal);

  // Set the RDAC to the value read from EEPROM
  digipot.write(storedVal);
  Serial.print("RDAC Value set to: ");
  Serial.println(digipot.read());
}

void loop() {
  // No further action needed in the loop for this test
}