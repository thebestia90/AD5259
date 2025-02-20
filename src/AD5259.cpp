/**
 * @file AD5259.cpp
 * @brief Implementation of the AD5259 Arduino library.
 * @author thebestia90
 * @date 20-Feb-2025
 * @version 1.1
 */

#include "AD5259.h"

AD5259::AD5259(uint8_t i2c_address) : _i2c_address(i2c_address) {}

bool AD5259::begin() {
    return isConnected();
}

bool AD5259::isConnected() {
    Wire.beginTransmission(_i2c_address);
    return (Wire.endTransmission() == 0);
}

void AD5259::write(uint8_t value) {
    if (!isConnected()) return;
    
    Wire.beginTransmission(_i2c_address);
    Wire.write(RDAC);  // Select RDAC register
    Wire.write(value);  // Write value to RDAC
    Wire.endTransmission();
}

uint8_t AD5259::read() {
    if (!isConnected()) return 0;

    Wire.beginTransmission(_i2c_address);
    Wire.write(RDAC);  // Select RDAC register
    Wire.endTransmission();
    
    Wire.requestFrom(_i2c_address, (uint8_t)1);

    uint32_t startMillis = millis();
    while (!Wire.available()) {
        if (millis() - startMillis > 100) {  // Timeout after 100ms
            Serial.println("I2C Read Timeout!");
            return 0;
        }
    }
    
    return Wire.read();
}

void AD5259::writeEEPROM(uint8_t value) {
    if (!isConnected()) return;

    Wire.beginTransmission(_i2c_address);
    Wire.write(0x60);  // EEPROM write command
    Wire.write(value);
    Wire.endTransmission();
    
    delay(10);  // Wait for EEPROM write to complete

    // Verify written value
    if (readEEPROM() != value) {
        Serial.println("EEPROM Write Error!");
    }
}

uint8_t AD5259::readEEPROM() {
    if (!isConnected()) return 0;

    Wire.beginTransmission(_i2c_address);
    Wire.write(0xA0);  // EEPROM read command
    Wire.endTransmission(false);

    Wire.requestFrom(_i2c_address, (uint8_t)1);

    uint32_t startMillis = millis();
    while (!Wire.available()) {
        if (millis() - startMillis > 100) {  // Timeout after 100ms
            Serial.println("EEPROM Read Timeout!");
            return 0;
        }
    }

    return Wire.read();
}

void AD5259::resetEEPROM(uint8_t defaultValue) {
    writeEEPROM(defaultValue);
}
