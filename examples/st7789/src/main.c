/*
 * Define the CPU frequency as 16MHz (16000000Hz).
 */
#define F_CPU 16000000UL

#include "main.h"

/**
 * @brief Sets up the initial configurations for the microcontroller.
 *
 */
static inline void setup() {
    ST77XX_Reset();
    ST77XX_InitDisplay();
    ST77XX_FillScreenWithColor(0x0000);
}

/**
 * @brief Continuously executes the main functionality of the program.
 *
 */
static inline void loop() {
    // Example 1: Drawing Buttons
    ST77XX_FillScreenWithColor(0x0000);  // Clear screen with black

    char op1[] = "Option 1";
    char op2[] = "Option 2";
    char op3[] = "Option 3";

    // Draw buttons with text
    ST77XX_DrawButtonWithText(20, 20, 100, 40, 0xF000, 0xFFFF, 0x0000, op1);
    ST77XX_FillButtonWithText(20, 80, 100, 40, 0xF81F, 0xFFFF, op2);
    ST77XX_DrawButtonWithText(20, 140, 100, 40, 0x00F0, 0xFFFF, 0x0000, op3);
    ST77XX_DelayMs(2000);  // Wait for 2 seconds

    // Example 2: Geometric Shapes
    ST77XX_FillScreenWithColor(0x0000);  // Clear screen with black

    // Draw filled rectangles
    ST77XX_FillRect(10, 10, 50, 30, 0xF800);   // Red
    ST77XX_FillRect(70, 10, 50, 30, 0x07E0);   // Green
    ST77XX_FillRect(130, 10, 50, 30, 0x001F);  // Blue

    // Draw circles
    ST77XX_DrawCircle(50, 90, 20, 0xFFFF);   // White
    ST77XX_FillCircle(150, 90, 20, 0xFFE0);  // Yellow

    // Draw lines
    ST77XX_DrawHLine(10, 140, 220, 0xF81F);  // Magenta
    ST77XX_DrawVLine(120, 160, 70, 0x07FF);  // Cyan

    // Draw diagonal line
    ST77XX_DrawDLine(20, 200, 100, M_PI_4, 0xFFE0);  // Yellow
    ST77XX_DelayMs(2000);                            // Wait for 2 seconds

    // Example 3: Polygons
    ST77XX_FillScreenWithColor(0x0000);  // Clear screen with black
    int16_t x1[] = {50, 100, 120, 70, 30};
    int16_t y1[] = {10, 20, 80, 100, 40};
    ST77XX_DrawPolygon(x1, y1, 5, 0xFFE0);  // Draw polygon in yellow
    ST77XX_DelayMs(1000);
    ST77XX_FillPolygon(x1, y1, 5, 0x001F);  // Fill polygon in blue
    ST77XX_DelayMs(2000);                   // Wait for 2 seconds

    // Example 4: Triangles
    ST77XX_FillScreenWithColor(0x0000);                       // Clear screen with black
    ST77XX_DrawTriangle(30, 150, 130, 30, 230, 150, 0x07E0);  // Draw triangle in green
    ST77XX_DelayMs(1000);
    ST77XX_FillTriangle(30, 230, 130, 110, 230, 230, 0xF810);  // Fill triangle in red
    ST77XX_DelayMs(2000);                                      // Wait for 2 seconds

    // Example 5: Drawing Table
    ST77XX_FillScreenWithColor(0x0000);  // Clear screen with black

    // Draw rectangles and fill them with different colors
    for (int i = 0; i < 12; i++) {
        int x = (i % 4) * 60;
        int y = (i / 4) * 60;
        uint16_t color = (i % 3 == 0) ? 0xF800 : (i % 3 == 1) ? 0x07E0 : 0x001F;
        ST77XX_DrawRect(x, y, 50, 50, color);
        ST77XX_FillRect(x + 10, y + 10, 30, 30, color);
    }

    ST77XX_DelayMs(2000);  // Wait for 2 seconds

    // Example 6: Text and Combined Shapes
    ST77XX_FillScreenWithColor(0x0000);  // Clear screen with black
    char text[] = "Hello, world!";
    ST77XX_DrawString(10, 10, text, 0xFFFF, 0x0000);  // White Text
    ST77XX_DrawChar(10, 30, 'A', 0xFFFF, 0x0000);     // White Character
    ST77XX_DrawHLine(10, 50, 100, 0xF81F);            // Magenta Horizontal Line
    ST77XX_DrawVLine(120, 50, 100, 0x07FF);           // Cyan Vertical Line
    ST77XX_DrawCircle(160, 100, 30, 0xFFE0);          // Yellow Circle
    ST77XX_DelayMs(2000);                             // Wait for 2 seconds

    // Draw random pixels to give an idea of module performance
    ST77XX_FillScreenWithColor(0x0000);  // Clear screen with black
    for (int i = 0; i < 100; i++) {
        ST77XX_DrawPixel(rand() % ST77XX_DISPLAY_WIDTH, rand() % ST77XX_DISPLAY_HEIGHT, 0xFFFF);
    }

    ST77XX_DelayMs(2000);  // Wait for 2 seconds

    // Clear screen for new demonstration cycle
    ST77XX_FillScreenWithColor(0x0000);  // Clear screen with black
}

/**
 * @brief The main function initializes the setup and then continuously executes
 * the loop.
 *
 * @return This function does not return any value.
 */
int main(void) {
    setup();
    while (1) {
        loop();
    }
    return 0;
}
