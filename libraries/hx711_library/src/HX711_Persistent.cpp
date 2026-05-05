/**
 *
 * HX711 Persistent Calibration Extension
 * Adds EEPROM storage for scale and offset values to survive power cycles
 * https://github.com/bogde/HX711
 *
 * MIT License
 * (c) 2026 Arduino Refresh Project
 *
 **/
#include <Arduino.h>
#include "HX711_Persistent.h"

HX711_Persistent::HX711_Persistent() : HX711() {
    // Constructor
    #if defined(ARDUINO_ARCH_ESP32) || defined(IS_FREE_RTOS)
    // Initialize mutex for thread-safe EEPROM operations
    eeprom_mutex = xSemaphoreCreateMutex();
    if (eeprom_mutex == NULL) {
        // Mutex creation failed - this could be critical for thread safety
        // For now, we'll continue without mutex protection
        // In a production environment, you might want to handle this more robustly
    }
    #endif
}

void HX711_Persistent::begin_with_eeprom(byte dout, byte pd_sck, byte gain, int eeprom_size) {
    // Initialize the base HX711
    HX711::begin(dout, pd_sck, gain);
    
    // Initialize EEPROM
    EEPROM.begin(eeprom_size);
    eeprom_available = true;
    
    // Try to load existing calibration
    if (has_valid_calibration()) {
        load_calibration();
    }
}

bool HX711_Persistent::has_valid_calibration() {
    if (!eeprom_available) return false;
    
    #if defined(ARDUINO_ARCH_ESP32) || defined(IS_FREE_RTOS)
    if (eeprom_mutex != NULL && xSemaphoreTake(eeprom_mutex, portMAX_DELAY) == pdTRUE) {
    #endif
    
    int flag;
    EEPROM.get(EEPROM_VALID_FLAG_ADDRESS, flag);
    
    #if defined(ARDUINO_ARCH_ESP32) || defined(IS_FREE_RTOS)
    if (eeprom_mutex != NULL) {
        xSemaphoreGive(eeprom_mutex);
    }
    #endif
    
    return (flag == EEPROM_VALID_FLAG);
}

bool HX711_Persistent::save_calibration() {
    if (!eeprom_available) return false;
    
    #if defined(ARDUINO_ARCH_ESP32) || defined(IS_FREE_RTOS)
    if (eeprom_mutex != NULL && xSemaphoreTake(eeprom_mutex, portMAX_DELAY) == pdTRUE) {
    #endif
    
    // Save scale factor
    float current_scale = get_scale();
    EEPROM.put(EEPROM_SCALE_ADDRESS, current_scale);
    
    // Save offset
    long current_offset = get_offset();
    EEPROM.put(EEPROM_OFFSET_ADDRESS, current_offset);
    
    // Save valid flag
    int flag = EEPROM_VALID_FLAG;
    EEPROM.put(EEPROM_VALID_FLAG_ADDRESS, flag);
    
    // Commit to EEPROM
    bool result = EEPROM.commit();
    
    #if defined(ARDUINO_ARCH_ESP32) || defined(IS_FREE_RTOS)
    if (eeprom_mutex != NULL) {
        xSemaphoreGive(eeprom_mutex);
    }
    #endif
    
    return result;
}

bool HX711_Persistent::load_calibration() {
    if (!has_valid_calibration()) return false;
    
    #if defined(ARDUINO_ARCH_ESP32) || defined(IS_FREE_RTOS)
    if (eeprom_mutex != NULL && xSemaphoreTake(eeprom_mutex, portMAX_DELAY) == pdTRUE) {
    #endif
    
    float scale;
    long offset;
    
    // Load scale factor
    EEPROM.get(EEPROM_SCALE_ADDRESS, scale);
    
    // Load offset
    EEPROM.get(EEPROM_OFFSET_ADDRESS, offset);
    
    // Apply loaded values
    set_scale(scale);
    set_offset(offset);
    
    #if defined(ARDUINO_ARCH_ESP32) || defined(IS_FREE_RTOS)
    if (eeprom_mutex != NULL) {
        xSemaphoreGive(eeprom_mutex);
    }
    #endif
    
    return true;
}

void HX711_Persistent::smart_tare(byte times) {
    // Read current value with existing weight
    double current_value = get_value(times);
    
    // Calculate new offset that would make current reading = 0
    // This preserves the existing weight as the new zero point
    long new_offset = get_offset() + static_cast<long>(current_value);
    
    set_offset(new_offset);
}

// Thread-safe wrapper for base class read method
long HX711_Persistent::read_thread_safe() {
    #if defined(ARDUINO_ARCH_ESP32) || defined(IS_FREE_RTOS)
    if (eeprom_mutex != NULL && xSemaphoreTake(eeprom_mutex, portMAX_DELAY) == pdTRUE) {
    #endif
    
    long result = HX711::read();
    
    #if defined(ARDUINO_ARCH_ESP32) || defined(IS_FREE_RTOS)
    if (eeprom_mutex != NULL) {
        xSemaphoreGive(eeprom_mutex);
    }
    #endif
    
    return result;
}

// Thread-safe wrapper for get_value method
double HX711_Persistent::get_value_thread_safe(byte times) {
    #if defined(ARDUINO_ARCH_ESP32) || defined(IS_FREE_RTOS)
    if (eeprom_mutex != NULL && xSemaphoreTake(eeprom_mutex, portMAX_DELAY) == pdTRUE) {
    #endif
    
    double result = HX711::get_value(times);
    
    #if defined(ARDUINO_ARCH_ESP32) || defined(IS_FREE_RTOS)
    if (eeprom_mutex != NULL) {
        xSemaphoreGive(eeprom_mutex);
    }
    #endif
    
    return result;
}

// Thread-safe wrapper for get_units method
float HX711_Persistent::get_units_thread_safe(byte times) {
    #if defined(ARDUINO_ARCH_ESP32) || defined(IS_FREE_RTOS)
    if (eeprom_mutex != NULL && xSemaphoreTake(eeprom_mutex, portMAX_DELAY) == pdTRUE) {
    #endif
    
    float result = HX711::get_units(times);
    
    #if defined(ARDUINO_ARCH_ESP32) || defined(IS_FREE_RTOS)
    if (eeprom_mutex != NULL) {
        xSemaphoreGive(eeprom_mutex);
    }
    #endif
    
    return result;
}

void HX711_Persistent::set_scale(float scale) {
    #if defined(ARDUINO_ARCH_ESP32) || defined(IS_FREE_RTOS)
    if (eeprom_mutex != NULL && xSemaphoreTake(eeprom_mutex, portMAX_DELAY) == pdTRUE) {
    #endif
    
    HX711::set_scale(scale);
    if (eeprom_available && has_valid_calibration()) {
        save_calibration();
    }
    
    #if defined(ARDUINO_ARCH_ESP32) || defined(IS_FREE_RTOS)
    if (eeprom_mutex != NULL) {
        xSemaphoreGive(eeprom_mutex);
    }
    #endif
}

void HX711_Persistent::set_offset(long offset) {
    #if defined(ARDUINO_ARCH_ESP32) || defined(IS_FREE_RTOS)
    if (eeprom_mutex != NULL && xSemaphoreTake(eeprom_mutex, portMAX_DELAY) == pdTRUE) {
    #endif
    
    HX711::set_offset(offset);
    if (eeprom_available && has_valid_calibration()) {
        save_calibration();
    }
    
    #if defined(ARDUINO_ARCH_ESP32) || defined(IS_FREE_RTOS)
    if (eeprom_mutex != NULL) {
        xSemaphoreGive(eeprom_mutex);
    }
    #endif
}