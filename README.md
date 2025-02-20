# AD5259 Arduino Library

## Overview
The `AD5259` library allows Arduino users to interface with the Analog Devices AD5259 digital potentiometer via I²C. This library provides functions to read and write values to the RDAC register, store settings in EEPROM, and reset stored values.

## Features
- Read and write RDAC values (0-255)
- Store and retrieve values from EEPROM
- Check device connection over I²C
- Reset EEPROM to a default value
- Built-in timeout handling for I²C communication

## Installation
1. Download or clone this repository.
2. Copy the `AD5259` folder into your Arduino `libraries` directory.
3. Restart the Arduino IDE.

## Usage
### Include the Library
```cpp
#include <Wire.h>
#include "AD5259.h"
```

### Initialize the Device
```cpp
AD5259 potentiometer(0x18); // Default I2C address

void setup() {
    Serial.begin(115200);
    Wire.begin();
    
    if (potentiometer.begin()) {
        Serial.println("AD5259 detected!");
    } else {
        Serial.println("AD5259 not found!");
    }
}
```

### Write and Read RDAC Value
```cpp
potentiometer.write(128); // Set RDAC to midpoint
uint8_t value = potentiometer.read();
Serial.print("RDAC Value: ");
Serial.println(value);
```

### Store and Retrieve Value from EEPROM
```cpp
potentiometer.writeEEPROM(200); // Save value to EEPROM
uint8_t storedValue = potentiometer.readEEPROM();
Serial.print("Stored EEPROM Value: ");
Serial.println(storedValue);
```

### Reset EEPROM to Default Value
```cpp
potentiometer.resetEEPROM(128); // Reset to 128
```

## License
This library is released under the MIT License.

## Contributions
Pull requests and improvements are welcome! Feel free to contribute via GitHub.

## Author
Developed by **thebestia90**.

## Disclaimer
This software is provided "as is" without any warranties. Always verify values before use in critical applications.

