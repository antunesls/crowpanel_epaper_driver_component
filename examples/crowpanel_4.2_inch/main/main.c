/**
 * CrowPanel 4.2-inch E-Paper Example
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "epaper_driver.h"
#include "esp_log.h"
#include "esp_heap_caps.h"

static const char *TAG = "example_4.2";

void app_main(void)
{
    ESP_LOGI(TAG, "Starting CrowPanel 4.2-inch Example (400x300)");

    EPD_GPIOInit();
    EPD_Init();
    EPD_Clear();

    // The display resolution is 400x300.
    // Buffer size = 400 * 300 / 8 = 15000 bytes
    uint32_t buf_size = (EPD_W * EPD_H) / 8;

    ESP_LOGI(TAG, "Allocating frame buffer: %lu bytes", buf_size);
    // Use SPIRAM if available for larger buffers, though 15KB fits in internal safely
    uint8_t *black_image = (uint8_t*)heap_caps_malloc(buf_size, MALLOC_CAP_DEFAULT);
    if (!black_image) {
        ESP_LOGE(TAG, "Failed to allocate memory!");
        return;
    }

    Paint_NewImage(black_image, EPD_W, EPD_H, ROTATE_0, WHITE);
    Paint_SelectImage(black_image);
    Paint_Clear(WHITE);

    // Draw some text and shapes
    Paint_DrawString_EN(20, 30, "CrowPanel 4.2 E-Paper", &Font24, WHITE, BLACK);
    Paint_DrawRectangle(20, 70, 380, 280, BLACK, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
    Paint_DrawCircle(200, 175, 50, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawLine(20, 280, 380, 280, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

    EPD_Display(black_image);
    ESP_LOGI(TAG, "Display updated");

    EPD_Sleep();
    free(black_image);
}
