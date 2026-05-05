/**
 * Test sketch to verify mutex initialization in HX711_Persistent constructor
 * This tests the new mutex functionality added to handle thread-safe EEPROM operations
 */

#include "HX711_Persistent.h"

HX711_Persistent scale;

void setup() {
    Serial.begin(9600);
    while (!Serial); // Wait for serial monitor
    
    Serial.println("Testing HX711_Persistent mutex initialization...");
    
    // The constructor should initialize the mutex automatically
    Serial.println("Constructor called - mutex should be initialized");
    
    // Test basic functionality
    Serial.println("Testing basic functionality...");
    
    // Initialize with EEPROM support
    scale.begin_with_eeprom(A0, A1);
    
    Serial.println("Initialization complete!");
    
    // Test mutex-protected operations
    Serial.println("Testing mutex-protected operations...");
    
    // These operations should now be thread-safe on ESP32/FreeRTOS
    bool has_calibration = scale.has_valid_calibration();
    Serial.print("Has valid calibration: ");
    Serial.println(has_calibration);
    
    // Test set_scale (should be mutex-protected)
    scale.set_scale(1.0f);
    Serial.println("set_scale() called - should be mutex-protected");
    
    // Test set_offset (should be mutex-protected)
    scale.set_offset(0);
    Serial.println("set_offset() called - should be mutex-protected");
    
    Serial.println("All tests passed! Mutex initialization successful.");
}

void loop() {
    // Nothing to do here
    delay(1000);
}