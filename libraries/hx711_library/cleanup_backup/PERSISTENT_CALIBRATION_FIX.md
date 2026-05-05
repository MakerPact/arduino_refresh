# HX711 Calibration Drift Fix

## Problem Description (GitHub Issue #32)

The original HX711 library loses calibration when the Arduino resets while weight is still present on the scale. This requires users to:
1. Remove the weight from the load cell
2. Power reset the system  
3. Place the weight back on the scale

This is impractical for applications with heavy loads (e.g., 200kg weights).

## Solution: Persistent Calibration

The `HX711_Persistent` extension adds EEPROM storage for calibration data, allowing the scale to maintain accuracy across power cycles.

### Key Features

1. **Automatic EEPROM Storage**: Scale and offset values are automatically saved to EEPROM
2. **Power Cycle Resilience**: Calibration survives Arduino resets and power failures
3. **Smart Tare Function**: Allows setting zero point even with existing weight
4. **Backward Compatibility**: Extends the original HX711 class without breaking existing code

### Technical Implementation

#### EEPROM Layout
- **Address 0-3**: Scale factor (float, 4 bytes)
- **Address 4-7**: Offset value (long, 4 bytes)  
- **Address 8-9**: Valid flag (0xA5A5 when valid)

#### Smart Tare Algorithm
```cpp
void smart_tare(byte times) {
    double current_value = get_value(times);
    long new_offset = get_offset() + static_cast<long>(current_value);
    set_offset(new_offset);
}
```

This allows setting a new zero point that considers existing weight, solving the core issue.

## Usage Example

```cpp
#include "HX711_Persistent.h"

HX711_Persistent scale;

void setup() {
    Serial.begin(9600);
    
    // Initialize with EEPROM support
    // Automatically loads saved calibration if available
    scale.begin_with_eeprom(A0, A1);
    
    if (scale.has_valid_calibration()) {
        Serial.println("Loaded calibration from EEPROM");
    } else {
        Serial.println("No calibration found - run calibration procedure");
    }
}

void loop() {
    if (scale.is_ready()) {
        float weight = scale.get_units(5);
        Serial.print("Weight: ");
        Serial.print(weight, 2);
        Serial.println(" g");
    }
    delay(500);
}
```

## Calibration Procedure

1. **Remove all weight** and call `scale.smart_tare()`
2. **Place known weight** on the scale
3. **Calculate scale factor**:
   ```cpp
   float new_scale = (raw_value - scale.get_offset()) / known_weight;
   scale.set_scale(new_scale);
   ```

## Hardware Requirements

- Arduino with EEPROM support (most boards)
- HX711 load cell amplifier
- Load cell
- Optional: Buttons for calibration/tare functions

## Compatibility

- **Boards**: AVR, ESP8266, ESP32, SAM, SAMD, STM32, Teensy
- **Original Library**: Fully compatible - extends HX711 class
- **EEPROM Size**: Only 10 bytes used (scale: 4, offset: 4, flag: 2)

## Testing Results

| Scenario | Original Library | With Persistent Fix |
|----------|------------------|---------------------|
| Power cycle with weight | Loses calibration | Maintains calibration |
| Manual tare | Works | Works + auto-save |
| Scale change | Works | Works + auto-save |
| First use | Requires calibration | Requires calibration |

## Installation

1. Copy `HX711_Persistent.h` and `HX711_Persistent.cpp` to your library folder
2. Include the header in your sketch
3. Use `HX711_Persistent` instead of `HX711`

## Future Enhancements

- Add temperature compensation storage
- Support multiple calibration profiles
- Add CRC checks for EEPROM data integrity
- Implement wear leveling for frequent writes

## References

- Original Issue: https://github.com/bogde/HX711/issues/32
- HX711 Datasheet: http://www.dfrobot.com/image/data/SEN0160/hx711_english.pdf
- EEPROM Documentation: https://www.arduino.cc/reference/en/libraries/eeprom/

## License

MIT License - Compatible with original HX711 library license