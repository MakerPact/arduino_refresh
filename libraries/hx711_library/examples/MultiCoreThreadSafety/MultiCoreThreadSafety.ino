/**
 * HX711 Multi-Core Thread Safety Example for ESP32
 * 
 * Demonstrates thread-safe access to HX711 from multiple CPU cores
 * Addresses GitHub Issue #257: "HX711 not thread safe?"
 * 
 * This example shows how to safely access HX711 from different CPU cores
 * using the thread-safe methods in HX711_Persistent class.
 *
 * Hardware Setup:
 * HX711.DOUT  -> ESP32 pin GPIO32
 * HX711.PD_SCK -> ESP32 pin GPIO33
 *
 * Features Demonstrated:
 * 1. Thread-safe HX711 access from multiple cores
 * 2. Mutex protection for shared hardware resource
 * 3. Concurrent weight reading without race conditions
 * 4. Safe calibration operations across threads
 */

#include "HX711_Persistent.h"

// Global HX711 instance
HX711_Persistent scale;

// Shared variables with protection
portMUX_TYPE weightMutex = portMUX_INITIALIZER_UNLOCKED;
float core0_weight = 0.0;
float core1_weight = 0.0;

/**
 * Task running on Core 0
 * Reads weight every 500ms and updates core0_weight
 */
void core0_task(void *parameter) {
    while(1) {
        // Use thread-safe method to read weight
        float weight = scale.get_units_thread_safe(5);
        
        // Safely update shared variable
        portENTER_CRITICAL(&weightMutex);
        core0_weight = weight;
        portEXIT_CRITICAL(&weightMutex);
        
        Serial.print("Core 0: ");
        Serial.print(weight, 2);
        Serial.println(" g");
        
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

/**
 * Task running on Core 1
 * Reads weight every 300ms and updates core1_weight
 */
void core1_task(void *parameter) {
    while(1) {
        // Use thread-safe method to read weight
        float weight = scale.get_units_thread_safe(3);
        
        // Safely update shared variable
        portENTER_CRITICAL(&weightMutex);
        core1_weight = weight;
        portEXIT_CRITICAL(&weightMutex);
        
        Serial.print("Core 1: ");
        Serial.print(weight, 2);
        Serial.println(" g");
        
        vTaskDelay(300 / portTICK_PERIOD_MS);
    }
}

/**
 * Calibration task (can be called from any core)
 * Demonstrates thread-safe calibration
 */
void calibrate_scale() {
    Serial.println("=== CALIBRATION MODE ===");
    
    // Thread-safe tare operation
    scale.smart_tare(10);
    Serial.println("Tare complete");
    
    // Thread-safe scale setting
    scale.set_scale(12345.6); // Example scale factor
    Serial.print("Scale set to: ");
    Serial.println(scale.get_scale());
    
    Serial.println("Calibration complete!");
}

void setup() {
    Serial.begin(115200);
    while (!Serial); // Wait for serial monitor
    
    Serial.println("HX711 Multi-Core Thread Safety Example");
    Serial.println("Addressing GitHub Issue #257");
    
    // Initialize HX711 with EEPROM support
    scale.begin_with_eeprom(32, 33); // DOUT=GPIO32, PD_SCK=GPIO33
    
    // Check for existing calibration
    if (scale.has_valid_calibration()) {
        Serial.println("✅ Loaded calibration from EEPROM");
    } else {
        Serial.println("ℹ️  No calibration found - running calibration");
        calibrate_scale();
    }
    
    // Create tasks and pin to specific cores
    xTaskCreatePinnedToCore(
        core0_task,   // Task function
        "Core0Task",  // Task name
        4096,         // Stack size
        NULL,        // Parameters
        1,            // Priority
        NULL,        // Task handle
        0            // Core 0
    );
    
    xTaskCreatePinnedToCore(
        core1_task,   // Task function
        "Core1Task",  // Task name
        4096,         // Stack size
        NULL,        // Parameters
        1,            // Priority
        NULL,        // Task handle
        1            // Core 1
    );
    
    Serial.println("✅ Multi-core tasks started successfully");
    Serial.println("Both cores are safely accessing HX711 simultaneously");
}

void loop() {
    // Main loop - monitor shared variables
    portENTER_CRITICAL(&weightMutex);
    float avg_weight = (core0_weight + core1_weight) / 2.0;
    portEXIT_CRITICAL(&weightMutex);
    
    Serial.print("Average: ");
    Serial.print(avg_weight, 2);
    Serial.println(" g");
    
    delay(1000);
}