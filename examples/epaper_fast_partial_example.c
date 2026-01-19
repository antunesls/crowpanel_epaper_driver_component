/**
 * E-Paper Driver - Fast & Partial Refresh Example
 * 
 * This example demonstrates the correct usage of partial and fast refresh modes
 * based on the Arduino EPD library reference implementation.
 * 
 * Key points:
 * 1. Always do a full clear and initialization before using partial/fast refresh
 * 2. Initialize Paint buffer and fill with white background
 * 3. Use EPD_Display_Part to establish the baseline image
 * 4. Then use EPD_Init_Fast to enable fast refresh mode
 * 5. Finally use EPD_Display_Fast for quick updates
 */

#include "epaper_driver.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "epaper_example";

// Image buffer - allocate enough space for the entire screen
static uint8_t Image_BW[EPD_W * EPD_H / 8];

/**
 * Example 1: Basic Fast Refresh
 * This demonstrates the minimal sequence needed for fast refresh to work
 */
void example_fast_refresh_basic(void) {
    ESP_LOGI(TAG, "Starting fast refresh basic example");
    
    // Step 1: Initialize GPIO and power on
    EPD_GPIOInit();
    
    // Step 2: Clear the screen completely (full refresh)
    EPD_Clear();
    
    // Step 3: Initialize paint buffer
    Paint_NewImage(Image_BW, EPD_W, EPD_H, 0, WHITE);
    EPD_Full(WHITE);
    
    // Step 4: Display the initial white canvas using partial update
    // This establishes the baseline for fast refresh
    EPD_Display_Part(0, 0, EPD_W, EPD_H, Image_BW);
    
    // Step 5: Initialize fast mode (1.5 seconds refresh)
    EPD_Init_Fast(Fast_Seconds_1_5s);
    
    // Step 6: Draw something on the buffer
    EPD_DrawRectangle(50, 50, 150, 100, BLACK, 1);
    EPD_ShowString(60, 60, "Fast Mode", 16, BLACK);
    
    // Step 7: Display with fast refresh
    EPD_Display_Fast(Image_BW);
    
    // Step 8: Put display to sleep
    EPD_Sleep();
    
    ESP_LOGI(TAG, "Fast refresh basic example complete");
}

/**
 * Example 2: Multiple Fast Updates
 * Shows how to do multiple consecutive fast refreshes
 */
void example_fast_refresh_multiple(void) {
    ESP_LOGI(TAG, "Starting multiple fast refresh example");
    
    // Initial setup
    EPD_GPIOInit();
    EPD_Clear();
    Paint_NewImage(Image_BW, EPD_W, EPD_H, 0, WHITE);
    EPD_Full(WHITE);
    EPD_Display_Part(0, 0, EPD_W, EPD_H, Image_BW);
    
    // Enable fast mode
    EPD_Init_Fast(Fast_Seconds_1_s); // Use 1 second mode for faster updates
    
    // Update 1: Draw a rectangle
    EPD_DrawRectangle(10, 10, 100, 60, BLACK, 1);
    EPD_ShowString(20, 25, "Update 1", 16, BLACK);
    EPD_Display_Fast(Image_BW);
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    // Update 2: Add more content
    EPD_DrawCircle(200, 40, 30, BLACK, 1);
    EPD_ShowString(170, 80, "Update 2", 16, BLACK);
    EPD_Display_Fast(Image_BW);
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    // Update 3: Add a counter
    for (int i = 0; i < 5; i++) {
        EPD_ClearWindows(10, 100, 100, 120, WHITE);
        EPD_ShowString(10, 100, "Count:", 16, BLACK);
        EPD_ShowNum(70, 100, i, 1, 16, BLACK);
        EPD_Display_Fast(Image_BW);
        vTaskDelay(pdMS_TO_TICKS(1500));
    }
    
    EPD_Sleep();
    ESP_LOGI(TAG, "Multiple fast refresh example complete");
}

/**
 * Example 3: Partial Refresh Without Fast Mode
 * Demonstrates partial updates for updating small areas
 */
void example_partial_refresh(void) {
    ESP_LOGI(TAG, "Starting partial refresh example");
    
    // Initial setup
    EPD_GPIOInit();
    EPD_Clear();
    Paint_NewImage(Image_BW, EPD_W, EPD_H, 0, WHITE);
    EPD_Full(WHITE);
    
    // Draw a static frame
    EPD_DrawRectangle(0, 0, EPD_W - 1, EPD_H - 1, BLACK, 0);
    EPD_ShowString(10, 10, "Partial Refresh Demo", 16, BLACK);
    
    // Full display to set the baseline
    EPD_Display_Part(0, 0, EPD_W, EPD_H, Image_BW);
    
    // Now update only a small region
    uint16_t update_x = 50;
    uint16_t update_y = 50;
    uint16_t update_w = 100;
    uint16_t update_h = 40;
    
    for (int i = 0; i < 10; i++) {
        // Clear the update region
        EPD_ClearWindows(update_x, update_y, update_x + update_w, update_y + update_h, WHITE);
        
        // Draw new content
        EPD_ShowString(update_x + 5, update_y + 5, "Value:", 12, BLACK);
        EPD_ShowNum(update_x + 50, update_y + 5, i * 10, 3, 12, BLACK);
        
        // Update only that region
        EPD_Display_Part(update_x, update_y, update_w, update_h, Image_BW);
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
    EPD_Sleep();
    ESP_LOGI(TAG, "Partial refresh example complete");
}

/**
 * Example 4: Complete Sequence (Clear -> Fast Updates -> Clear)
 * Shows the full lifecycle including proper cleanup
 */
void example_complete_sequence(void) {
    ESP_LOGI(TAG, "Starting complete sequence example");
    
    // === INITIALIZATION ===
    EPD_GPIOInit();
    
    // Full clear
    EPD_Clear();
    Paint_NewImage(Image_BW, EPD_W, EPD_H, 0, WHITE);
    EPD_Full(WHITE);
    EPD_Display_Part(0, 0, EPD_W, EPD_H, Image_BW);
    
    // === FAST REFRESH PHASE ===
    EPD_Init_Fast(Fast_Seconds_1_5s);
    
    // Draw some content
    EPD_ShowString(10, 10, "Starting...", 24, BLACK);
    EPD_Display_Fast(Image_BW);
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    // Update content
    EPD_ClearWindows(10, 10, 300, 40, WHITE);
    EPD_ShowString(10, 10, "Running...", 24, BLACK);
    EPD_Display_Fast(Image_BW);
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    // Final update
    EPD_ClearWindows(10, 10, 300, 40, WHITE);
    EPD_ShowString(10, 10, "Complete!", 24, BLACK);
    EPD_Display_Fast(Image_BW);
    
    // === SLEEP ===
    EPD_Sleep();
    vTaskDelay(pdMS_TO_TICKS(5000));
    
    // === FINAL CLEAR ===
    clear_all();
    
    ESP_LOGI(TAG, "Complete sequence example finished");
}

/**
 * Example 5: Sensor Data Display with Fast Refresh
 * Practical example showing live sensor data updates
 */
void example_sensor_display(void) {
    ESP_LOGI(TAG, "Starting sensor display example");
    
    // Initial setup
    EPD_GPIOInit();
    EPD_Clear();
    Paint_NewImage(Image_BW, EPD_W, EPD_H, 0, WHITE);
    EPD_Full(WHITE);
    
    // Draw static UI elements
    EPD_DrawRectangle(0, 0, EPD_W - 1, EPD_H - 1, BLACK, 0);
    EPD_ShowString(10, 10, "Sensor Monitor", 24, BLACK);
    EPD_DrawLine(10, 40, EPD_W - 10, 40, BLACK);
    
    EPD_ShowString(20, 60, "Temperature:", 16, BLACK);
    EPD_ShowString(20, 90, "Humidity:", 16, BLACK);
    EPD_ShowString(20, 120, "Pressure:", 16, BLACK);
    
    // Display the static content
    EPD_Display_Part(0, 0, EPD_W, EPD_H, Image_BW);
    
    // Enable fast mode for value updates
    EPD_Init_Fast(Fast_Seconds_1_s);
    
    // Simulate sensor readings
    for (int i = 0; i < 20; i++) {
        // Simulate sensor values
        float temp = 20.0f + (i % 10);
        float humidity = 45.0f + (i % 15);
        int pressure = 1013 + (i % 5);
        
        // Clear value areas
        EPD_ClearWindows(180, 60, 280, 76, WHITE);
        EPD_ClearWindows(180, 90, 280, 106, WHITE);
        EPD_ClearWindows(180, 120, 280, 136, WHITE);
        
        // Draw new values
        EPD_ShowFloatNum1(180, 60, temp, 4, 1, 16, BLACK);
        EPD_ShowString(240, 60, "C", 16, BLACK);
        
        EPD_ShowFloatNum1(180, 90, humidity, 4, 1, 16, BLACK);
        EPD_ShowString(240, 90, "%", 16, BLACK);
        
        EPD_ShowNum(180, 120, pressure, 4, 16, BLACK);
        EPD_ShowString(240, 120, "hPa", 16, BLACK);
        
        // Fast update
        EPD_Display_Fast(Image_BW);
        
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
    
    EPD_Sleep();
    vTaskDelay(pdMS_TO_TICKS(3000));
    clear_all();
    
    ESP_LOGI(TAG, "Sensor display example complete");
}

/**
 * Main application entry point
 * Uncomment the example you want to run
 */
void app_main(void) {
    ESP_LOGI(TAG, "E-Paper Fast & Partial Refresh Examples");
    
    // Run one example at a time
    // example_fast_refresh_basic();
    // example_fast_refresh_multiple();
    // example_partial_refresh();
    example_complete_sequence();
    // example_sensor_display();
    
    ESP_LOGI(TAG, "All examples completed");
}
