/**
 * HX711 Persistent Calibration Example
 * 
 * Demonstrates the solution to GitHub Issue #32: "last known weight lost on reset"
 * 
 * This example shows how to use the HX711_Persistent class to maintain
 * calibration across power cycles, eliminating the need to remove weight
 * during Arduino resets.
 * 
 * Key Features Demonstrated:
 * 1. Automatic EEPROM storage of scale and offset values
 * 2. Persistent calibration across power cycles
 * 3. Smart tare functionality for zeroing with existing weight
 * 4. Automatic save/load of calibration changes
 * 5. Button-based calibration procedure
 *
 * Hardware Setup:
 * HX711.DOUT  -> Arduino pin A0
 * HX711.PD_SCK -> Arduino pin A1  
 * CAL Button   -> Arduino pin D2 (with pullup resistor)
 * TARE Button  -> Arduino pin D3 (with pullup resistor)
 * 
 * Calibration Requirements:
 * - Known calibration weight (default: 100g)
 * - Stable power supply
 * - Load cell properly connected
 *
 * Usage:
 * 1. Upload sketch to Arduino
 * 2. Open Serial Monitor (9600 baud)
 * 3. Follow on-screen instructions for calibration
 * 4. Test power cycle resilience by resetting with weight on scale
 *
 * Expected Behavior:
 * - Calibration survives power cycles
 * - Weight readings remain accurate across resets
 * - No need to remove weight during power cycles
 *
 * Author: Arduino Refresh Project
 * Date: 2026
 * License: MIT (compatible with original HX711 library)
 *
 * Copyright (c) 2026 Arduino Refresh Project
 * This software is provided "as is" without warranty of any kind.
 */

#include "HX711_Persistent.h"

HX711_Persistent scale;

// Calibration button pin
const int CALIBRATION_BUTTON_PIN = 2;
const int TARE_BUTTON_PIN = 3;

// Known calibration weight in grams
const float CALIBRATION_WEIGHT = 100.0; // 100g calibration weight

void setup() {
    Serial.begin(9600);
    Serial.println("HX711 Persistent Calibration Example");
    
    // Initialize buttons
    pinMode(CALIBRATION_BUTTON_PIN, INPUT_PULLUP);
    pinMode(TARE_BUTTON_PIN, INPUT_PULLUP);
    
    // Initialize HX711 with EEPROM support
    // If EEPROM has valid calibration data, it will be loaded automatically
    scale.begin_with_eeprom(A0, A1);
    
    // Check if we have valid calibration
    if (scale.has_valid_calibration()) {
        Serial.println("Loaded calibration from EEPROM");
        Serial.print("Scale: ");
        Serial.println(scale.get_scale());
        Serial.print("Offset: ");
        Serial.println(scale.get_offset());
    } else {
        Serial.println("No valid calibration found. Please calibrate.");
    }
    
    Serial.println("Setup complete. Ready for measurements.");
    Serial.println("Press CALIBRATION button to start calibration process.");
    Serial.println("Press TARE button to set current weight as zero.");
}

void loop() {
    // Check for calibration button press
    if (digitalRead(CALIBRATION_BUTTON_PIN) == LOW) {
        calibrate_scale();
        delay(500); // Debounce
    }
    
    // Check for tare button press  
    if (digitalRead(TARE_BUTTON_PIN) == LOW) {
        Serial.println("Taring...");
        scale.smart_tare(10); // Smart tare considers existing weight
        Serial.println("Tare complete. Current weight is now zero.");
        delay(500); // Debounce
    }
    
    // Read and display weight
    if (scale.is_ready()) {
        float weight = scale.get_units(5);
        Serial.print("Weight: ");
        Serial.print(weight, 2);
        Serial.println(" g");
    } else {
        Serial.println("HX711 not ready");
    }
    
    delay(500);
}

void calibrate_scale() {
    Serial.println("=== CALIBRATION MODE ===");
    Serial.println("Remove all weight from scale");
    Serial.println("Press TARE button when ready");
    
    // Wait for tare
    while (digitalRead(TARE_BUTTON_PIN) == HIGH) {
        delay(100);
    }
    delay(500); // Debounce
    
    Serial.println("Setting offset...");
    scale.smart_tare(10);
    
    Serial.println("Place known weight on scale");
    Serial.print("Expected weight: ");
    Serial.print(CALIBRATION_WEIGHT);
    Serial.println(" g");
    Serial.println("Press TARE button when weight is placed");
    
    // Wait for weight placement
    while (digitalRead(TARE_BUTTON_PIN) == HIGH) {
        delay(100);
    }
    delay(500); // Debounce
    
    // Read the raw value with the known weight
    long raw_value = scale.read_average(10);
    
    // Calculate scale factor
    // scale_factor = raw_value / known_weight
    // But we need: weight = (raw_value - offset) / scale_factor
    // So: scale_factor = (raw_value - offset) / known_weight
    float new_scale = (raw_value - scale.get_offset()) / CALIBRATION_WEIGHT;
    
    Serial.print("Raw value with weight: ");
    Serial.println(raw_value);
    Serial.print("Calculated scale factor: ");
    Serial.println(new_scale);
    
    scale.set_scale(new_scale);
    
    Serial.println("Calibration complete!");
    Serial.print("Scale: ");
    Serial.println(scale.get_scale());
    Serial.print("Offset: ");
    Serial.println(scale.get_offset());
    Serial.println("Calibration saved to EEPROM");
}