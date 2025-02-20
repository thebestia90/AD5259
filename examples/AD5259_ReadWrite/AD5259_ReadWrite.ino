 /**
 * @file    AD5259_ReadWrite.ino
 * @brief   Example code for interfacing Arduino with AD5259 digital potentiometer.
 * @author  Thebestia90 
 * @date    20-Feb-2025
 * @details This example initializes the AD5259 via I2C, sets to a 
 *          mid-scale value (128), and reads back the values for verification.
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
  // ESP32 Default I2C pins: SDA = GPIO21, SCL = GPIO22
  Wire.begin(21, 22);
#elif defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_ARCH_MBED_RP2040) || defined(ARDUINO_ARCH_RP2350)
  // RP2040: Set custom SDA/ SCL pins (GP16, GP17)
  Wire.setSDA(16);
  Wire.setSCL(17);
  Wire.begin();
  // Set the I2C clock speed to 400kHz
  Wire.setClock(400000);
#else
  Wire.begin();
#endif

  // Check if AD5259 is connected
  if (digipot.begin()) {
    Serial.println("AD5259 Connected!");
  } else {
    Serial.println("AD5259 NOT found!");
    while (true) {
      delay(100);
    }
  }

  // Set RDAC to mid-scale (128)
  digipot.write(128);
  Serial.print("RDAC Value: ");
  Serial.println(digipot.read());
}

void loop() {
}