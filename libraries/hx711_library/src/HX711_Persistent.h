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
#ifndef HX711_PERSISTENT_h
#define HX711_PERSISTENT_h

#include "HX711.h"
#include <EEPROM.h>

// Forward declaration for FreeRTOS mutex
#if defined(ARDUINO_ARCH_ESP32) || defined(IS_FREE_RTOS)
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#endif

class HX711_Persistent : public HX711
{
private:
    // EEPROM addresses for storing calibration data
    static const int EEPROM_SCALE_ADDRESS = 0;
    static const int EEPROM_OFFSET_ADDRESS = 4;
    static const int EEPROM_VALID_FLAG_ADDRESS = 8;
    static const int EEPROM_VALID_FLAG = 0xA5A5;
    
    bool eeprom_available = false;
    
    // Mutex for thread-safe EEPROM operations
    #if defined(ARDUINO_ARCH_ESP32) || defined(IS_FREE_RTOS)
    SemaphoreHandle_t eeprom_mutex;
    #endif

public:
    HX711_Persistent();
    
    // Initialize with EEPROM support
    void begin_with_eeprom(byte dout, byte pd_sck, byte gain = 128, int eeprom_size = 512);
    
    // Save current scale and offset to EEPROM
    bool save_calibration();
    
    // Load scale and offset from EEPROM
    bool load_calibration();
    
    // Smart tare that considers existing weight
    void smart_tare(byte times = 10);
    
    // Check if EEPROM has valid calibration data
    bool has_valid_calibration();
    
    // Override set_scale to auto-save
    void set_scale(float scale = 1.f) override;
    
    // Override set_offset to auto-save  
    void set_offset(long offset = 0) override;
    
    // Thread-safe wrapper methods for base class
    long read_thread_safe();
    double get_value_thread_safe(byte times = 1);
    float get_units_thread_safe(byte times = 1);
};

#endif /* HX711_PERSISTENT_h */