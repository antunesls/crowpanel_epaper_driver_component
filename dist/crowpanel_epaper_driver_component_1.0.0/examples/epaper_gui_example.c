/**
 * E-Paper Driver - GUI Functions Usage Example
 * 
 * This file demonstrates how to use the newly implemented GUI functions:
 * - EPD_ClearWindows: Clear a rectangular area
 * - EPD_DrawLine: Draw a line between two points
 * - EPD_DrawRectangle: Draw filled or outlined rectangle
 * - EPD_DrawCircle: Draw filled or outlined circle
 * - EPD_ShowChar: Display a single character
 * - EPD_ShowString: Display a string
 * - EPD_ShowNum: Display an integer number
 * - EPD_ShowFloatNum1: Display a floating point number
 */

#include "epaper_driver.h"
#include <string.h>

// Example buffer
static uint8_t image_buffer[EPD_W * EPD_H / 8];

void epaper_gui_example(void) {
    // Initialize hardware
    EPD_GPIOInit();
    EPD_Init();
    
    // Create a paint buffer
    Paint_NewImage(image_buffer, EPD_W, EPD_H, ROTATE_0, WHITE);
    
    // Fill the entire buffer with white
    EPD_Full(WHITE);
    
    // Example 1: Draw geometric shapes
    // Draw a rectangle (outline only)
    EPD_DrawRectangle(50, 50, 150, 100, BLACK, 0);
    
    // Draw a filled rectangle
    EPD_DrawRectangle(200, 50, 300, 100, BLACK, 1);
    
    // Draw a circle (outline only)
    EPD_DrawCircle(100, 150, 30, BLACK, 0);
    
    // Draw a filled circle
    EPD_DrawCircle(250, 150, 30, BLACK, 1);
    
    // Draw some lines
    EPD_DrawLine(50, 200, 300, 200, BLACK);
    EPD_DrawLine(50, 210, 300, 230, BLACK);
    
    // Example 2: Display text in different sizes
    // Display strings in different font sizes
    EPD_ShowString(10, 10, "8px Font", 8, BLACK);
    EPD_ShowString(10, 20, "12px Font", 12, BLACK);
    EPD_ShowString(10, 35, "16px Font", 16, BLACK);
    EPD_ShowString(10, 55, "24px Font", 24, BLACK);
    
    // Example 3: Display numbers
    EPD_ShowString(10, 250, "Integer: ", 16, BLACK);
    EPD_ShowNum(100, 250, 12345, 5, 16, BLACK);
    
    EPD_ShowString(10, 270, "Float: ", 16, BLACK);
    EPD_ShowFloatNum1(80, 270, 3.14159, 5, 3, 16, BLACK);
    
    // Example 4: Clear a specific window area
    EPD_ClearWindows(350, 10, 390, 50, WHITE);
    
    // Update the display with the buffer content
    EPD_Display(image_buffer);
    
    // Example 5: Partial update (if needed)
    // EPD_DrawRectangle(10, 10, 100, 50, BLACK, 1);
    // EPD_Display_Part(10, 10, 90, 40, image_buffer);
}

/**
 * Simple telemetry display example
 * Shows how to create a sensor data display
 */
void epaper_telemetry_example(float temperature, float humidity, int battery_percent) {
    // Create a paint buffer
    Paint_NewImage(image_buffer, EPD_W, EPD_H, ROTATE_0, WHITE);
    EPD_Full(WHITE);
    
    // Title
    EPD_ShowString(10, 10, "Sensor Data", 24, BLACK);
    EPD_DrawLine(10, 40, 380, 40, BLACK);
    
    // Temperature
    EPD_ShowString(20, 60, "Temperature:", 16, BLACK);
    EPD_ShowFloatNum1(180, 60, temperature, 4, 1, 16, BLACK);
    EPD_ShowString(240, 60, "C", 16, BLACK);
    
    // Humidity
    EPD_ShowString(20, 90, "Humidity:", 16, BLACK);
    EPD_ShowFloatNum1(180, 90, humidity, 4, 1, 16, BLACK);
    EPD_ShowString(240, 90, "%", 16, BLACK);
    
    // Battery
    EPD_ShowString(20, 120, "Battery:", 16, BLACK);
    EPD_ShowNum(180, 120, battery_percent, 3, 16, BLACK);
    EPD_ShowString(240, 120, "%", 16, BLACK);
    
    // Battery indicator (visual)
    EPD_DrawRectangle(20, 150, 200, 180, BLACK, 0);  // Battery outline
    EPD_DrawRectangle(200, 160, 210, 170, BLACK, 1); // Battery terminal
    
    // Fill battery based on percentage
    int fill_width = (battery_percent * 170) / 100;
    if (fill_width > 0) {
        EPD_DrawRectangle(25, 155, 25 + fill_width, 175, BLACK, 1);
    }
    
    // Update display
    EPD_Display(image_buffer);
}
