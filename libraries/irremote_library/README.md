# IRremote Library Improvements

## Overview
Focused project to fix specific issues in the Arduino IRremote library, starting with the RC5 toggle bit bug (Issue #1347).

## Current Focus: RC5 Toggle Bit Fix

**Issue**: When `aEnableAutomaticToggle = false`, the toggle bit in RC5 protocol is never set, regardless of the `sLastSendToggleValue`.

**Impact**: Users who need manual control over the RC5 toggle bit cannot properly implement their protocols.

## Repository Structure

```
arduino_refresh/
└── libraries/
    └── irremote_library/       # Main project folder
        ├── README.md            # Project overview
        ├── src/                 # Source code
        ├── examples/            # Example sketches
        ├── hermes/              # ✨ Hermes-specific files ✨
        │   ├── analysis/        # Analysis scripts
        │   ├── testing/         # Test scripts
        │   ├── documentation/  # Project docs
        │   └── tools/           # Custom tools
        ├── docs/                # Documentation
        └── original/            # Original library backup
```

## Project Status

### Completed
- ✅ Project structure created
- ✅ Issue research completed
- ✅ Top 3 issues identified
- ✅ Hermes folder organization established

### In Progress
- 🔄 RC5 toggle bit bug analysis
- 🔄 Solution implementation planning

### Next Steps
- 📌 Create reproduction test for RC5 issue
- 📌 Implement toggle bit fix
- 📌 Develop comprehensive test suite
- 📌 Document solution

## Identified Issues (Priority Order)

### 1. RC5 Toggle Bit Bug (Issue #1347) ⭐ CURRENT FOCUS
- **Severity**: Medium
- **Complexity**: Very Low
- **Status**: Analysis complete, ready for implementation
- **Files affected**: `src/IRremote.cpp` (sendRC5 function)

### 2. ReceiveDemo Compilation Bug (Issue #1306)
- **Severity**: Low
- **Complexity**: Very Low
- **Status**: Identified, queued for after RC5 fix
- **Files affected**: `examples/ReceiveDemo/ReceiveDemo.ino`

### 3. 8-bit Overflow Bug (Issue #1214)
- **Severity**: Medium
- **Complexity**: Low
- **Status**: Identified, queued for future
- **Files affected**: `src/IRremote.cpp` (loop counters)

### 4. Sharp Frame Marker Bug (Issue #1272)
- **Severity**: Low
- **Complexity**: Medium
- **Status**: Identified, lower priority
- **Files affected**: `src/IRremote.cpp` (Sharp decoder)

### 5. ESP32 Core 3.x Compatibility
- **Severity**: Medium
- **Complexity**: Medium
- **Status**: Identified, future consideration
- **Files affected**: Platform-specific files

## Current Issue: RC5 Toggle Bit Bug

### Problem Analysis

**Current Code** (in `sendRC5()`):
```cpp
if (aEnableAutomaticToggle) {
    sLastSendToggleValue = !sLastSendToggleValue;
}
// Toggle bit is only set when aEnableAutomaticToggle = true
```

**Expected Behavior**:
- Toggle bit should be set based on `sLastSendToggleValue` regardless of `aEnableAutomaticToggle`
- `aEnableAutomaticToggle` should only control automatic toggling, not prevent manual toggle bit setting

### Solution Approach

**Proposed Fix**:
```cpp
// Always set toggle bit based on current value
bool toggleBit = sLastSendToggleValue;

// Only auto-toggle if enabled
if (aEnableAutomaticToggle) {
    sLastSendToggleValue = !sLastSendToggleValue;
}

// Use toggleBit in protocol encoding
```

### Implementation Plan

1. **Create reproduction test** (`hermes/analysis/rc5_toggle_test.ino`)
2. **Develop fix** in `src/IRremote_improved.cpp`
3. **Create comprehensive test suite** (`hermes/testing/`)
4. **Document solution** (`hermes/documentation/`)
5. **Verify backward compatibility**

## Next Actions

1. **Clone original IRremote library** to `original/` directory
2. **Create RC5 toggle bit test** to reproduce the issue
3. **Implement the fix** in improved version
4. **Test thoroughly** with various RC5 devices
5. **Document the solution**

## Related Projects

- [[arduino-cleanup]] — Main Arduino Library Refresh Project
- [[max7219-ghosting-fix]] — Previous LED matrix project
- [[hx711-persistent-calibration]] — EEPROM calibration example

## See Also

- [[arduino-library-analysis]] — Analysis methodology
- [[arduino-coding-standards]] — Best practices