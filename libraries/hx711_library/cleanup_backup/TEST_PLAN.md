# HX711 Persistent Calibration Test

This script tests the persistent calibration functionality to ensure it solves the calibration drift issue.

## Test Setup

### Hardware Requirements
- Arduino board (Uno, Mega, etc.)
- HX711 load cell amplifier
- Load cell
- Known calibration weight (e.g., 100g)
- Optional: Buttons for calibration/tare

### Wiring
```
HX711 VCC  -> Arduino 5V
HX711 GND  -> Arduino GND  
HX711 DOUT -> Arduino A0
HX711 PD_SCK -> Arduino A1
CAL Button -> Arduino D2 (with pullup)
TARE Button -> Arduino D3 (with pullup)
```

## Test Cases

### Test 1: Basic Functionality
1. Upload the PersistentCalibration example
2. Open Serial Monitor (9600 baud)
3. Verify "HX711 Persistent Calibration Example" message appears
4. Verify "No calibration found" message (first run)

**Expected Result**: System initializes without errors

### Test 2: Calibration Procedure
1. Remove all weight from scale
2. Press TARE button
3. Place known weight (e.g., 100g) on scale
4. Press TARE button again
5. Observe calibration values in Serial Monitor

**Expected Result**: 
- Scale factor is calculated and displayed
- "Calibration complete" message appears
- Values are saved to EEPROM

### Test 3: Persistence Test
1. Note the weight reading with calibration weight
2. Reset Arduino (power cycle or reset button)
3. Observe Serial Monitor output
4. Check weight reading after reset

**Expected Result**:
- "Loaded calibration from EEPROM" message appears
- Weight reading matches pre-reset value (within normal variation)
- No need to remove weight during reset

### Test 4: Smart Tare Function
1. Place arbitrary weight on scale
2. Note the current reading
3. Press TARE button
4. Observe new reading

**Expected Result**:
- Reading changes to approximately 0
- Existing weight is now the new zero point
- Calibration remains valid

### Test 5: Multiple Power Cycles
1. Calibrate scale with known weight
2. Perform 5 power cycles with weight present
3. Check reading after each cycle

**Expected Result**:
- Reading remains consistent across all cycles
- No calibration drift observed
- EEPROM data remains intact

## Expected Output

### First Run (No Calibration)
```
HX711 Persistent Calibration Example
No valid calibration found. Please calibrate.
Setup complete. Ready for measurements.
Press CALIBRATION button to start calibration process.
Press TARE button to set current weight as zero.
```

### After Calibration
```
=== CALIBRATION MODE ===
Remove all weight from scale
Press TARE button when ready
Setting offset...
Place known weight on scale
Expected weight: 100.00 g
Press TARE button when weight is placed
Raw value with weight: 123456
Calculated scale factor: 1234.56
Calibration complete!
Scale: 1234.56
Offset: 789012
Calibration saved to EEPROM
```

### After Power Cycle
```
HX711 Persistent Calibration Example
Loaded calibration from EEPROM
Scale: 1234.56
Offset: 789012
Setup complete. Ready for measurements.
Weight: 100.00 g
Weight: 100.01 g
Weight: 99.99 g
```

## Troubleshooting

### Issue: "EEPROM not available"
**Solution**: Ensure your board supports EEPROM. Most Arduino boards do, but some custom boards may not.

### Issue: Weight readings fluctuate
**Solution**: 
- Check wiring connections
- Ensure stable power supply
- Use averaging (get_units(10) instead of get_units(1))

### Issue: Calibration not loading after reset
**Solution**:
- Verify EEPROM.begin() is called
- Check EEPROM commit() returns true
- Ensure valid flag is written correctly

## Success Criteria

The fix is considered successful when:
1. ✅ Calibration survives power cycles with weight present
2. ✅ Weight readings are consistent across resets
3. ✅ No need to remove weight for power cycles
4. ✅ Smart tare function works with existing weight
5. ✅ Original HX711 functionality remains unchanged

## Comparison with Original Issue #32

| Aspect | Original Behavior | Fixed Behavior |
|--------|-------------------|-----------------|
| Power cycle with weight | Loses calibration | Maintains calibration |
| Reset required | Must remove weight | No weight removal needed |
| Calibration storage | Volatile (RAM only) | Persistent (EEPROM) |
| Tare with weight | Not possible | Possible with smart_tare() |
| Commercial suitability | Limited | Excellent |

This test plan verifies that the persistent calibration fix completely resolves the issues described in GitHub Issue #32.