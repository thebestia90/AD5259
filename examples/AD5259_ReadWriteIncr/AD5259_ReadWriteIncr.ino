/**
 * @file    AD5259_ReadWriteIncr.ino
 * @brief   Example code for interfacing Arduino with AD5259 digital potentiometer.
 * @author  Thebestia90 
 * @date    20-Feb-2025
 * @details This example initializes the AD5259 via I2C, sets the initial 
 *          RDAC value to 0, then increments up to 255 and back down to 0.
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

  // Set initial RDAC value to 0
  digipot.write(0);
  Serial.print("RDAC Value: ");
  Serial.println(digipot.read());
}

void loop() {
  // Increment the value from 0 to 255
  for (int val = 0; val <= 255; val++) {
    digipot.write(val); // Write current value
    Serial.print("RDAC Value: ");
    Serial.println(digipot.read()); // Read and print the value
    delay(100); // Wait 100ms before the next increment
  }

  // Decrement the value from 255 to 0
  for (int val = 255; val >= 0; val--) {
    digipot.write(val); // Write current value
    Serial.print("RDAC Value: ");
    Serial.println(digipot.read()); // Read and print the value
    delay(100); // Wait 100ms before the next decrement
  }
}
