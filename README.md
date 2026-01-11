# CrowPanel E-Paper Driver Component

ESP-IDF component driver for CrowPanel E-Paper displays with comprehensive GUI functions including text rendering, geometric shapes, and display management.

## Supported Hardware

- **CrowPanel 4.2" E-Paper Display** (400x300 pixels)
- **CrowPanel 2.13" E-Paper Display** (250x122 pixels)

## Features

✅ Full SPI communication support  
✅ Configurable via `menuconfig`  
✅ Fast and standard refresh modes  
✅ Comprehensive GUI functions:
  - Text rendering (8px, 12px, 16px, 24px fonts)
  - Geometric shapes (lines, rectangles, circles)
  - Integer and floating-point number display
  - Partial and full screen updates
  - Window clearing functions
✅ Low-level pixel manipulation  
✅ Rotation support (0°, 90°, 180°, 270°)  
✅ Power management

## Installation

### Using ESP Component Registry (Recommended)

```bash
idf.py add-dependency "antunesls/crowpanel_epaper_driver_component"
```

### Manual Installation

Clone this repository into your project's `components` directory:

```bash
cd your-project/components
git clone https://github.com/antunesls/crowpanel_epaper_driver_component.git
```

## Configuration

Run `idf.py menuconfig` and navigate to **Component config → CrowPanel E-Paper Configuration**:

### Available Options

| Option | Description | Default |
|--------|-------------|---------|
| **E-Paper Display Model** | Select 4.2" or 2.13" display | 4.2" (400x300) |
| **SPI Host Number** | 1=SPI2_HOST, 2=SPI3_HOST | 1 (SPI2_HOST) |
| **SPI MOSI Pin** | GPIO for SPI MOSI | 11 |
| **SPI CLK Pin** | GPIO for SPI CLK | 12 |
| **SPI CS Pin** | GPIO for Chip Select | 45 |
| **DC Pin** | GPIO for Data/Command | 46 |
| **RST Pin** | GPIO for Reset | 47 |
| **BUSY Pin** | GPIO for BUSY signal | 48 |
| **Power Control Pin** | GPIO for power control (-1 to disable) | 7 |

## Quick Start

### Basic Example

```c
#include "epaper_driver.h"

// Buffer to hold the display image
static uint8_t image_buffer[EPD_W * EPD_H / 8];

void app_main(void) {
    // Initialize the E-Paper display
    EPD_GPIOInit();
    EPD_Init();
    
    // Create a paint buffer (white background)
    Paint_NewImage(image_buffer, EPD_W, EPD_H, ROTATE_0, WHITE);
    EPD_Full(WHITE);
    
    // Display text
    EPD_ShowString(10, 10, "Hello, World!", 16, BLACK);
    
    // Display a number
    EPD_ShowNum(10, 30, 42, 2, 16, BLACK);
    
    // Draw a rectangle
    EPD_DrawRectangle(10, 60, 100, 110, BLACK, 0);
    
    // Update the display
    EPD_Display(image_buffer);
}
```

### GUI Functions Example

For detailed GUI function examples, see [epaper_gui_example.c](examples/epaper_gui_example.c).

```c
#include "epaper_driver.h"

static uint8_t image_buffer[EPD_W * EPD_H / 8];

void display_telemetry(float temperature, float humidity) {
    // Initialize
    EPD_GPIOInit();
    EPD_Init();
    Paint_NewImage(image_buffer, EPD_W, EPD_H, ROTATE_0, WHITE);
    EPD_Full(WHITE);
    
    // Display title
    EPD_ShowString(50, 10, "Sensor Data", 24, BLACK);
    
    // Draw a dividing line
    EPD_DrawLine(10, 40, EPD_W - 10, 40, BLACK);
    
    // Display temperature
    EPD_ShowString(20, 60, "Temperature:", 16, BLACK);
    EPD_ShowFloatNum1(150, 60, temperature, 5, 2, 16, BLACK);
    EPD_ShowString(220, 60, "C", 16, BLACK);
    
    // Display humidity
    EPD_ShowString(20, 90, "Humidity:", 16, BLACK);
    EPD_ShowFloatNum1(150, 90, humidity, 5, 2, 16, BLACK);
    EPD_ShowString(220, 90, "%", 16, BLACK);
    
    // Draw a frame
    EPD_DrawRectangle(5, 5, EPD_W - 5, EPD_H - 5, BLACK, 0);
    
    // Update display
    EPD_Display(image_buffer);
}
```

## API Reference

### Initialization Functions

#### `EPD_GPIOInit()`
Initialize GPIO pins for E-Paper display communication.

```c
void EPD_GPIOInit(void);
```

#### `EPD_Init()`
Initialize the E-Paper display with standard refresh mode.

```c
void EPD_Init(void);
```

#### `EPD_Init_Fast()`
Initialize the E-Paper display with fast refresh mode.

```c
void EPD_Init_Fast(uint8_t mode);
// mode: Fast_Seconds_1_5s or Fast_Seconds_1_s
```

### Display Update Functions

#### `EPD_Display()`
Update the entire display with the provided image buffer.

```c
void EPD_Display(const uint8_t *Image);
```

#### `EPD_Display_Part()`
Update a specific rectangular area of the display.

```c
void EPD_Display_Part(uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey, const uint8_t *Image);
```

#### `EPD_Display_Fast()`
Fast update of the entire display.

```c
void EPD_Display_Fast(const uint8_t *Image);
```

### Drawing Functions

#### `EPD_DrawLine()`
Draw a line between two points.

```c
void EPD_DrawLine(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t Color);
```

#### `EPD_DrawRectangle()`
Draw a rectangle (outline or filled).

```c
void EPD_DrawRectangle(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t Color, uint8_t mode);
// mode: 0 = outline, 1 = filled
```

#### `EPD_DrawCircle()`
Draw a circle (outline or filled).

```c
void EPD_DrawCircle(uint16_t X_Center, uint16_t Y_Center, uint16_t Radius, uint16_t Color, uint8_t mode);
// mode: 0 = outline, 1 = filled
```

### Text Rendering Functions

#### `EPD_ShowString()`
Display a text string.

```c
void EPD_ShowString(uint16_t x, uint16_t y, const char *chr, uint16_t size1, uint16_t color);
// size1: 8, 12, 16, or 24 (font size in pixels)
```

#### `EPD_ShowChar()`
Display a single character.

```c
void EPD_ShowChar(uint16_t x, uint16_t y, uint16_t chr, uint16_t size1, uint16_t color);
```

#### `EPD_ShowNum()`
Display an integer number.

```c
void EPD_ShowNum(uint16_t x, uint16_t y, uint32_t num, uint16_t len, uint16_t size1, uint16_t color);
// len: number of digits to display
```

#### `EPD_ShowFloatNum1()`
Display a floating-point number.

```c
void EPD_ShowFloatNum1(uint16_t x, uint16_t y, float num, uint8_t len, uint8_t pre, uint8_t sizey, uint8_t color);
// len: total digits, pre: decimal places
```

### Utility Functions

#### `EPD_Clear()`
Clear the entire display.

```c
void EPD_Clear(void);
```

#### `EPD_ClearWindows()`
Clear a rectangular area.

```c
void EPD_ClearWindows(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t color);
```

#### `EPD_Full()`
Fill the entire image buffer with a color.

```c
void EPD_Full(uint8_t Color);
// Color: WHITE or BLACK
```

#### `EPD_Sleep()`
Put the display into sleep mode.

```c
void EPD_Sleep(void);
```

#### `EPD_PowerOn()`
Turn on display power (if power control pin is configured).

```c
void EPD_PowerOn(void);
```

### Paint Functions

#### `Paint_NewImage()`
Initialize the paint buffer.

```c
void Paint_NewImage(uint8_t *image, uint16_t Width, uint16_t Height, uint16_t Rotate, uint16_t Color);
// Rotate: ROTATE_0, ROTATE_90, ROTATE_180, ROTATE_270
```

#### `Paint_SetPixel()`
Set a pixel at specific coordinates.

```c
void Paint_SetPixel(uint16_t Xpoint, uint16_t Ypoint, uint16_t Color);
```

## Constants

### Colors
```c
#define WHITE 0xFF
#define BLACK 0x00
```

### Rotation
```c
#define ROTATE_0   0
#define ROTATE_90  90
#define ROTATE_180 180
#define ROTATE_270 270
```

### Fast Refresh Modes
```c
#define Fast_Seconds_1_5s 1
#define Fast_Seconds_1_s  2
```

## Hardware Connection

The default pin configuration is optimized for ESP32-S3 with CrowPanel:

| Function | GPIO Pin |
|----------|----------|
| MOSI     | 11 |
| CLK      | 12 |
| CS       | 45 |
| DC       | 46 |
| RST      | 47 |
| BUSY     | 48 |
| Power    | 7 |

> **Note:** These pins can be configured via `menuconfig`.

## Additional Documentation

- [GUI_FUNCTIONS.md](GUI_FUNCTIONS.md) - Detailed GUI functions documentation with examples

## Performance Notes

- **Standard Mode**: Better image quality, slower refresh (~2-3 seconds)
- **Fast Mode**: Faster refresh (~1-1.5 seconds), may show ghosting
- **Partial Update**: Only updates specific areas, very fast

## Troubleshooting

### Display not updating
- Check BUSY pin connection
- Verify SPI pin configuration
- Ensure power pin is correctly configured

### Ghosting on display
- Use `EPD_Clear()` before major updates
- Use standard mode instead of fast mode
- Power cycle the display

### Text not displaying
- Ensure font size is supported (8, 12, 16, 24)
- Check if coordinates are within display bounds
- Verify color (BLACK on WHITE or vice versa)

## License

MIT License - see [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## Credits

Based on the CrowPanel E-Paper display specifications and adapted for ESP-IDF.

## Support

For issues and questions:
- GitHub Issues: https://github.com/antunesls/crowpanel_epaper_driver_component/issues

## Changelog

### v1.0.0 (2026-01-11)
- Initial release
- Support for 4.2" and 2.13" displays
- Complete GUI function library
- Text rendering with multiple font sizes
- Geometric shape drawing
- Configurable via menuconfig
