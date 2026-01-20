/**
 * E-Paper Driver - Get Started Example
 * 
 * This example demonstrates basic initialization and painting on the e-paper display.
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "epaper_driver.h"
#include "esp_log.h"

static const char *TAG = "example";

// Allocate buffer in PSRAM if available, otherwise in Heap
// For 4.2" (400x300), buffer is ~15KB (1-bit), small enough for internal RAM
static uint8_t *image_buffer = NULL;

void app_main(void)
{
    ESP_LOGI(TAG, "Starting E-Paper Example...");

    // 1. Initialize GPIO pins used by the display
    EPD_GPIOInit();

    // 2. Initialize the display hardware
    EPD_Init();
    
    // 3. Clear the display to white
    EPD_Clear();

    // 4. Allocate memory for the image buffer
    // Width and Height are available from the driver headers/macros
    uint16_t width = EPD_W;
    uint16_t height = EPD_H;
    uint32_t buf_size = (width * height) / 8;
    
    // Ensure width is byte-aligned for buffer calculation
    if (width % 8 != 0) {
        buf_size = ((width / 8) + 1) * height;
    }

    ESP_LOGI(TAG, "Allocating buffer size: %lu bytes", buf_size);
    image_buffer = (uint8_t*)malloc(buf_size);
    if (!image_buffer) {
        ESP_LOGE(TAG, "Failed to allocate memory for image buffer");
        return;
    }

    // 5. Initialize the Paint tool (graphics library)
    // We create a canvas that maps to our allocated buffer
    Paint_NewImage(image_buffer, width, height, ROTATE_0, WHITE);
    
    // 6. Draw something!
    Paint_SelectImage(image_buffer);
    Paint_Clear(WHITE);

    // Draw a rectangle
    Paint_DrawRectangle(10, 10, 100, 60, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    
    // Draw a string
    Paint_DrawString_EN(15, 20, "Hello World", &Font16, WHITE, BLACK);
    
    // Draw some lines using the unified GUI functions directly
    // (Optional: if the driver exposes direct drawing commands)
    // EPD_DrawLine(...); // Example function invocation

    // 7. Send the buffer to the display
    EPD_Display(image_buffer);

    ESP_LOGI(TAG, "Display updated. Going to sleep.");

    // 8. Put display to sleep to save power
    EPD_Sleep();

    // Free memory
    free(image_buffer);
    
    ESP_LOGI(TAG, "Example finished.");
}
