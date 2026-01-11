# CrowPanel E-Paper Driver - GUI Functions

This document describes the GUI and text rendering functions available in the E-Paper driver component.

## Available Functions

### Window Management

#### `EPD_ClearWindows`
```c
void EPD_ClearWindows(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t color);
```
Clears a rectangular area with the specified color.

**Parameters:**
- `xs`, `ys`: Starting coordinates (top-left corner)
- `xe`, `ye`: Ending coordinates (bottom-right corner)
- `color`: Fill color (`WHITE` or `BLACK`)

**Example:**
```c
EPD_ClearWindows(10, 10, 100, 50, WHITE);
```

---

### Shape Drawing Functions

#### `EPD_DrawLine`
```c
void EPD_DrawLine(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t Color);
```
Draws a line between two points using the Bresenham algorithm.

**Parameters:**
- `Xstart`, `Ystart`: Starting point
- `Xend`, `Yend`: Ending point
- `Color`: Line color (`WHITE` or `BLACK`)

**Example:**
```c
EPD_DrawLine(0, 0, 100, 100, BLACK);
```

---

#### `EPD_DrawRectangle`
```c
void EPD_DrawRectangle(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t Color, uint8_t mode);
```
Draws a rectangle, either filled or outlined.

**Parameters:**
- `Xstart`, `Ystart`: Top-left corner
- `Xend`, `Yend`: Bottom-right corner
- `Color`: Border/fill color (`WHITE` or `BLACK`)
- `mode`: `0` for outline only, `1` for filled

**Example:**
```c
// Outline rectangle
EPD_DrawRectangle(50, 50, 150, 100, BLACK, 0);

// Filled rectangle
EPD_DrawRectangle(200, 50, 300, 100, BLACK, 1);
```

---

#### `EPD_DrawCircle`
```c
void EPD_DrawCircle(uint16_t X_Center, uint16_t Y_Center, uint16_t Radius, uint16_t Color, uint8_t mode);
```
Draws a circle, either filled or outlined.

**Parameters:**
- `X_Center`, `Y_Center`: Center point
- `Radius`: Circle radius in pixels
- `Color`: Border/fill color (`WHITE` or `BLACK`)
- `mode`: `0` for outline only, `1` for filled

**Example:**
```c
// Outline circle
EPD_DrawCircle(100, 150, 30, BLACK, 0);

// Filled circle
EPD_DrawCircle(250, 150, 30, BLACK, 1);
```

---

### Text Rendering Functions

#### `EPD_ShowChar`
```c
void EPD_ShowChar(uint16_t x, uint16_t y, uint16_t chr, uint16_t size1, uint16_t color);
```
Displays a single ASCII character.

**Parameters:**
- `x`, `y`: Character position
- `chr`: ASCII character code
- `size1`: Font size (8, 12, 16, or 24)
- `color`: Text color (`WHITE` or `BLACK`)

**Example:**
```c
EPD_ShowChar(10, 10, 'A', 16, BLACK);
```

---

#### `EPD_ShowString`
```c
void EPD_ShowString(uint16_t x, uint16_t y, const char *chr, uint16_t size1, uint16_t color);
```
Displays a text string.

**Parameters:**
- `x`, `y`: Starting position
- `chr`: Null-terminated string
- `size1`: Font size (8, 12, 16, or 24)
- `color`: Text color (`WHITE` or `BLACK`)

**Example:**
```c
EPD_ShowString(10, 20, "Hello World!", 16, BLACK);
```

---

#### `EPD_ShowNum`
```c
void EPD_ShowNum(uint16_t x, uint16_t y, uint32_t num, uint16_t len, uint16_t size1, uint16_t color);
```
Displays an integer number.

**Parameters:**
- `x`, `y`: Starting position
- `num`: Number to display
- `len`: Number of digits to display
- `size1`: Font size (8, 12, 16, or 24)
- `color`: Text color (`WHITE` or `BLACK`)

**Example:**
```c
EPD_ShowNum(10, 50, 12345, 5, 16, BLACK);
```

---

#### `EPD_ShowFloatNum1`
```c
void EPD_ShowFloatNum1(uint16_t x, uint16_t y, float num, uint8_t len, uint8_t pre, uint8_t sizey, uint8_t color);
```
Displays a floating-point number.

**Parameters:**
- `x`, `y`: Starting position
- `num`: Number to display
- `len`: Total number of digits (including decimal places)
- `pre`: Number of decimal places
- `sizey`: Font size (8, 12, 16, or 24)
- `color`: Text color (`WHITE` or `BLACK`)

**Example:**
```c
// Display 3.14 (3 total digits, 2 decimal places)
EPD_ShowFloatNum1(10, 80, 3.14159, 3, 2, 16, BLACK);
```

---

## Font Sizes

The driver includes pre-rendered bitmap fonts in the following sizes:

| Size | Width x Height | Characters |
|------|----------------|------------|
| 8    | 6x8 pixels     | ASCII 32-126 |
| 12   | 6x12 pixels    | ASCII 32-126 |
| 16   | 8x16 pixels    | ASCII 32-126 |
| 24   | 12x24 pixels   | ASCII 32-126 |

---

## Complete Example

```c
#include "epaper_driver.h"

static uint8_t image_buffer[EPD_W * EPD_H / 8];

void app_main(void) {
    // Initialize hardware
    EPD_GPIOInit();
    EPD_Init();
    
    // Create paint buffer
    Paint_NewImage(image_buffer, EPD_W, EPD_H, ROTATE_0, WHITE);
    EPD_Full(WHITE);
    
    // Draw shapes
    EPD_DrawRectangle(10, 10, 100, 60, BLACK, 0);
    EPD_DrawCircle(200, 40, 25, BLACK, 1);
    EPD_DrawLine(10, 80, 390, 80, BLACK);
    
    // Display text
    EPD_ShowString(10, 100, "Temperature:", 16, BLACK);
    EPD_ShowFloatNum1(150, 100, 23.5, 4, 1, 16, BLACK);
    EPD_ShowString(200, 100, "C", 16, BLACK);
    
    EPD_ShowString(10, 130, "Status: OK", 24, BLACK);
    
    // Update display
    EPD_Display(image_buffer);
    
    // Sleep
    EPD_Sleep();
}
```

---

## Notes

1. **Font Data**: The font bitmaps are located in `epaper_fonts_data.c` and are included in the component build.

2. **Memory**: Ensure your `image_buffer` is sized correctly: `EPD_W * EPD_H / 8` bytes.

3. **Coordinate System**: Origin (0,0) is at the top-left corner.

4. **Colors**: Use the predefined macros `WHITE` (0xFF) and `BLACK` (0x00).

5. **Rotation**: Supported rotations are `ROTATE_0`, `ROTATE_90`, `ROTATE_180`, and `ROTATE_270`.

6. **Performance**: Drawing operations modify the framebuffer in RAM. Call `EPD_Display()` once after all drawing operations to update the physical display.

---

## References

- Original implementation based on CrowPanel E-Paper examples
- Font data ported from Waveshare/CrowPanel libraries
- Bresenham algorithms for line and circle drawing
