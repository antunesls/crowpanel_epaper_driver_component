# Get Started Example

This is the basic "Hello World" example for the CrowPanel E-Paper Driver Component. It demonstrates the minimal code needed to initialize and display content on the E-Paper screen.

## Hardware Required

- ESP32 development board (ESP32, ESP32-S3, etc.)
- CrowPanel E-Paper display (4.2-inch or 2.13-inch)
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

1. Initializes the GPIO pins for the E-Paper display
2. Initializes the E-Paper driver
3. Clears the display (makes it all white)
4. Allocates a frame buffer
5. Creates a new image/canvas
6. Draws "Hello World!" text
7. Displays the content on the E-Paper screen
8. Puts the display in sleep mode to save power

## Output

The display will show "Hello World!" text on a white background.

## Code Structure

```c
// 1. Initialize hardware
EPD_GPIOInit();
EPD_Init();
EPD_Clear();

// 2. Allocate buffer
uint8_t *image = malloc(buffer_size);

// 3. Setup canvas
Paint_NewImage(image, width, height, rotation, color);
Paint_SelectImage(image);
Paint_Clear(WHITE);

// 4. Draw content
Paint_DrawString_EN(x, y, "Text", &Font, bg, fg);

// 5. Display
EPD_Display(image);

// 6. Sleep & cleanup
EPD_Sleep();
free(image);
```

## Next Steps

After trying this example, check out:

- [GUI Functions Documentation](../../GUI_FUNCTIONS.md) - Learn all available drawing functions
- [4.2-inch Example](../crowpanel_4.2_inch/) - More complex example with shapes
- [2.13-inch Example](../crowpanel_2.13_inch/) - Example for smaller display

## Troubleshooting

- **Display not responding**: Verify pin connections match Kconfig settings
- **Blank screen**: Ensure proper power supply and check BUSY pin behavior
- **Memory errors**: Check available heap memory before allocating buffer

## See Also

- [Main README](../../README.md) - Component overview and installation
- [Publishing Guide](../../PUBLISHING.md) - For component development
