#pragma once

/**
 * @file AD5259.h
 * @brief Library for interfacing Arduino with the AD5259 digital potentiometer.
 * @author thebestia90 
 * @date 20-Feb-2025
 * @version 1.1
 * @details Provides functions to read and write RDAC and EEPROM over I²C.
 */

#ifndef AD5259_H
#define AD5259_H

#include <Arduino.h>
#include <Wire.h>

/**
 * @class AD5259
 * @brief A class to interface with the AD5259 digital potentiometer using I²C.
 */
class AD5259 {
public:
    /**
     * @brief Constructor to initialize the AD5259.
     * @param i2c_address The I2C address of the AD5259 (default: 0x18).
     */
    explicit AD5259(uint8_t i2c_address = 0x18);

    /**
     * @brief Initializes the AD5259 by checking if the device is connected.
     * @return True if the device is detected, false otherwise.
     */
    bool begin();

    /**
     * @brief Checks if the AD5259 is connected over I2C.
     * @return True if the device is responding, false otherwise.
     */
    bool isConnected();

    /**
     * @brief Writes a value to the RDAC register.
     * @param value The 8-bit value to write (0-255).
     */
    void write(uint8_t value);

    /**
     * @brief Reads the value from the RDAC register.
     * @return The 8-bit value read from RDAC (0-255).
     */
    uint8_t read();

    /**
     * @brief Writes a value to the EEPROM.
     * @param value The 8-bit value to store in EEPROM (0-255).
     */
    void writeEEPROM(uint8_t value);

    /**
     * @brief Reads the stored value from EEPROM.
     * @return The 8-bit value read from EEPROM.
     */
    uint8_t readEEPROM();

    /**
     * @brief Resets EEPROM to a default value.
     * @param defaultValue The value to reset EEPROM to (default: 128).
     */
    void resetEEPROM(uint8_t defaultValue = 128);

private:
    uint8_t _i2c_address;  ///< I2C address of the AD5259 device.

    static constexpr uint8_t RDAC = 0x00; ///< RDAC register address.
};

#endif // AD5259_H
