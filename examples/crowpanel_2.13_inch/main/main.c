/**
 * CrowPanel 2.13-inch E-Paper Example
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "epaper_driver.h"
#include "esp_log.h"

static const char *TAG = "example_2.13";

void app_main(void)
{
    ESP_LOGI(TAG, "Starting CrowPanel 2.13-inch Example (122x250)");

    EPD_GPIOInit();
    EPD_Init();
    EPD_Clear();

    // The display resolution is 122(W) x 250(H) but driver handles buffer alignment
    // Buffer size calculation logic handling byte alignment:
    uint16_t w_bytes = (EPD_W % 8 == 0) ? (EPD_W / 8) : (EPD_W / 8 + 1);
    uint32_t buf_size = w_bytes * EPD_H;

    ESP_LOGI(TAG, "Allocating frame buffer: %lu bytes", buf_size);
    uint8_t *black_image = (uint8_t*)heap_caps_malloc(buf_size, MALLOC_CAP_DMA);
    if (!black_image) {
        ESP_LOGE(TAG, "Failed to allocate memory!");
        return;
    }

    Paint_NewImage(black_image, EPD_W, EPD_H, ROTATE_0, WHITE);
    Paint_SelectImage(black_image);
    Paint_Clear(WHITE);

    // Draw some text and shapes
    Paint_DrawString_EN(10, 10, "CrowPanel 2.13", &Font16, BLACK, WHITE);
    Paint_DrawRectangle(10, 40, 100, 80, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(60, 150, 30, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);

    EPD_Display(black_image);
    ESP_LOGI(TAG, "Display updated");

    EPD_Sleep();
    free(black_image);
}
