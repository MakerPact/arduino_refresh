# Fix for Calibration Drift Issue #32

## Problem Summary
This PR addresses the calibration drift issue described in [Issue #32](https://github.com/bogde/HX711/issues/32). When the Arduino resets with weight still present on the scale, the original library loses calibration and requires users to remove the weight, reset, and reapply the weight - which is impractical for heavy loads.

## Solution
Introduces `HX711_Persistent` class that extends the original `HX711` with EEPROM-based calibration storage.

### Key Changes
1. **Persistent Storage**: Scale and offset values are automatically saved to EEPROM
2. **Smart Tare**: New `smart_tare()` method allows setting zero point with existing weight
3. **Auto-Load**: Calibration data is automatically loaded on initialization
4. **Backward Compatible**: Extends rather than modifies the original class

### Files Added
- `src/HX711_Persistent.h` - Header file for persistent extension
- `src/HX711_Persistent.cpp` - Implementation
- `examples/PersistentCalibration/PersistentCalibration.ino` - Usage example
- `PERSISTENT_CALIBRATION_FIX.md` - Documentation

### Technical Details
- **EEPROM Usage**: Only 10 bytes (scale: 4, offset: 4, validity flag: 2)
- **Compatibility**: Works with all boards supporting EEPROM
- **Memory Impact**: Minimal - only adds storage when explicitly used

## Usage Example
```cpp
#include "HX711_Persistent.h"

HX711_Persistent scale;

void setup() {
    // Initialize with EEPROM support
    scale.begin_with_eeprom(A0, A1);
    
    // Calibration is automatically loaded if available
    if (!scale.has_valid_calibration()) {
        // Run calibration procedure
    }
}

void loop() {
    float weight = scale.get_units(5);
    // Weight reading maintains calibration across power cycles
}
```

## Testing
- ✅ Power cycle with weight present - maintains calibration
- ✅ Manual tare operations - works with auto-save
- ✅ Scale factor changes - works with auto-save
- ✅ First-time use - requires calibration as expected
- ✅ Multiple board types - AVR, ESP8266, ESP32

## Benefits
1. **Solves Issue #32**: No need to remove weight for power cycles
2. **Industrial Ready**: Suitable for commercial applications with heavy loads
3. **User Friendly**: Automatic save/load requires no code changes
4. **Reliable**: Valid flag ensures only good data is loaded

## Backward Compatibility
- Original `HX711` class unchanged - no breaking changes
- Existing code continues to work unchanged
- New functionality is opt-in via `HX711_Persistent`

## Request for Merge
This fix directly addresses the long-standing calibration drift issue while maintaining full backward compatibility. The implementation is minimal, well-tested, and ready for production use.

@bogde I'd appreciate your review and consideration for merging this enhancement. It solves a critical issue for commercial applications while keeping the original library intact.