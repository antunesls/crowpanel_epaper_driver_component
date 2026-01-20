# CrowPanel 2.13-inch E-Paper Example

This example demonstrates how to use the CrowPanel 2.13-inch E-Paper display (122x250 pixels) with the driver component.

## Hardware Required

- ESP32 development board (ESP32, ESP32-S3, etc.)
- CrowPanel 2.13-inch E-Paper display (122x250)
- USB cable for programming and power

## Pin Configuration

The default pin configuration can be found in the component's Kconfig. You can modify these pins using `idf.py menuconfig`:

```
Component config → CrowPanel E-Paper Driver Configuration
```

Default pins:
- BUSY: GPIO 7
- RST: GPIO 8
- DC: GPIO 9
- CS: GPIO 10
- SCK: GPIO 11
- MOSI: GPIO 12

## How to Use

### Build and Flash

Navigate to this example directory and run:

```bash
idf.py build
idf.py flash monitor
```

Or use the ESP-IDF extension in VS Code.

### What This Example Does

1. Initializes the E-Paper display
2. Clears the screen
3. Allocates a frame buffer (3813 bytes for 122x250 display)
4. Draws:
   - Text using Font20
   - A rectangle
   - A circle
   - A diagonal line
5. Updates the display with the drawn content
6. Puts the display in sleep mode

## Output

The display will show:
- "CrowPanel 2.13" text at the top
- A rectangular border
- A circle in the center
- A diagonal line

## Memory Requirements

The 2.13-inch display requires approximately 3.8KB frame buffer (122 × 250 ÷ 8 ≈ 3813 bytes). This easily fits in ESP32's internal RAM.

## Troubleshooting

- **Display not updating**: Check your pin connections and verify they match the Kconfig settings
- **Memory allocation failed**: Ensure your ESP32 has sufficient free heap (at least 4KB)
- **Partial content**: Make sure you're using the correct rotation and display dimensions

## See Also

- [Main README](../../README.md) - Component overview and features
- [GUI Functions](../../GUI_FUNCTIONS.md) - Complete drawing functions reference
- [Get Started Example](../get_started/) - Basic usage example
- [4.2-inch Example](../crowpanel_4.2_inch/) - Larger display example
