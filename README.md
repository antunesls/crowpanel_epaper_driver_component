# CrowPanel E-Paper Driver Component

ESP-IDF component driver for CrowPanel E-Paper displays with comprehensive GUI functions including text rendering, geometric shapes, and display management.

## Supported Hardware

- **CrowPanel 4.2" E-Paper Display** (400x300 pixels)
- **CrowPanel 2.13" E-Paper Display** (250x122 pixels)

## Features

✅ Support for multiple display sizes (2.13" and 4.2")  
✅ Unified driver with auto-configuration  
✅ Full SPI communication support  
✅ Configurable via `menuconfig` (Kconfig)  
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
✅ **Ready-to-use Examples** included

## Installation

### Using ESP Component Registry (Recommended)

```bash
idf.py add-dependency "antunesls/crowpanel_epaper_driver_component"
```

Or add to your `idf_component.yml`:

```yaml
dependencies:
  antunesls/crowpanel_epaper_driver_component:
    version: "^1.0.0"
```

### Manual Installation

Clone this repository into your project's `components` directory (or `managed_components` if managed manually):

```bash
cd your-project/components
git clone https://github.com/antunesls/crowpanel_epaper_driver_component.git
```

## Configuration

Run `idf.py menuconfig` and navigate to **Component config → CrowPanel E-Paper Configuration**:

### Available Options

| Option | Description | Default |
|--------|-------------|---------|
| **E-Paper Display Model** | Select 4.2" (400x300) or 2.13" (250x122) | 4.2" |
| **SPI Host Number** | 1=SPI2_HOST, 2=SPI3_HOST | 1 (SPI2_HOST) |
| **SPI MOSI Pin** | GPIO for SPI MOSI | 11 |
| **SPI CLK Pin** | GPIO for SPI CLK | 12 |
| **SPI CS Pin** | GPIO for Chip Select | 45 (4.2") / 14 (2.13") |
| **DC Pin** | GPIO for Data/Command | 46 (4.2") / 13 (2.13") |
| **RST Pin** | GPIO for Reset | 47 (4.2") / 41 (2.13") |
| **BUSY Pin** | GPIO for BUSY signal | 48 (4.2") / 42 (2.13") |
| **Power Control Pin** | GPIO for power control (-1 to disable) | 7 |

*Note: Default pin configurations update automatically when you select the Display Model in menuconfig.*

## Examples

This component comes with ready-to-use examples for both supported displays located in the `examples/` directory.

### Running the 2.13" Example
```bash
cd managed_components/antunesls__crowpanel_epaper_driver_component/examples/crowpanel_2.13_inch
idf.py set-target esp32s3
idf.py build flash monitor
```

### Running the 4.2" Example
```bash
cd managed_components/antunesls__crowpanel_epaper_driver_component/examples/crowpanel_4.2_inch
idf.py set-target esp32s3
idf.py build flash monitor
```

## Quick Start (Code snippet)

```c
#include "epaper_driver.h"

// Buffer to hold the display image
// Size is automatically determined by the selected configuration in menuconfig
static uint8_t image_buffer[EPD_W * EPD_H / 8];

void app_main(void) {
    // Initialize GPIO and E-Paper display
    EPD_GPIOInit();
    EPD_Init();
    
    // Clear screen first
    EPD_Clear();

    // Create a paint buffer (white background)
    // EPD_W and EPD_H are defined based on CONFIG_CROWPANEL_EPAPER_...
    Paint_NewImage(image_buffer, EPD_W, EPD_H, ROTATE_0, WHITE);
    Paint_SelectImage(image_buffer);
    Paint_Clear(WHITE);
    
    // Draw string
    // x, y, text, font_size, visible_color, (background_color is assumed WHITE in some APIs or transparent)
    // For EPD_ShowString, the last arg is color.
    EPD_ShowString(10, 10, "Hello, CrowPanel!", 16, BLACK);
    
    // Draw a number
    EPD_ShowNum(10, 40, 1234, 4, 16, BLACK);
    
    // Draw a rectangle
    EPD_DrawRectangle(10, 70, 100, 120, BLACK, 0);
    
    // Update the display with the buffer
    EPD_Display(image_buffer);
    
    // Put display to sleep to save power
    EPD_Sleep();
}
```

## Troubleshooting

- **Display not updating?** Check if `EPD_PowerOn` (which toggles the power control pin) is needed for your specific board revision, or if the "Power Control Pin" is correctly configured.
- **Garbage pixels?** Ensure the buffer allocated matches `EPD_W * EPD_H / 8` and that you cleared it with `Paint_Clear(WHITE)`.
- **Busy Timeout?** Double check the `BUSY` pin connection.
