/*
 * Include the header files for the ST77XX display and SPI module.
 */
#include "st77xx.h"

#include "../spi/spi.h"

/*
 * @brief Sends a data byte to the ST77XX display via SPI.
 *
 * @param data The data byte to be sent.
 *
 * This function sends a data byte to the ST77XX display via SPI communication.
 */
void ST77XX_SendData(uint8_t data) {
    // Activate the Chip Select (CS) of the display
    ST77XX_PORT &= ~(1 << ST77XX_DD_CS);

    // Set the Data/Command (DC) pin to 1 to send data
    ST77XX_PORT |= (1 << ST77XX_DD_DC);

    SPI_MasterTransmit(data);

    // Deactivate the Chip Select (CS) of the display
    ST77XX_PORT |= (1 << ST77XX_DD_CS);
}

/*
 * @brief Sends a command byte to the ST77XX display via SPI.
 *
 * @param command The command byte to be sent.
 *
 * This function sends a command byte to the ST77XX display via SPI
 * communication.
 */
void ST77XX_SendCommand(uint8_t command) {
    // Activate the Chip Select (CS) of the display
    ST77XX_PORT &= ~(1 << ST77XX_DD_CS);

    // Set the Data/Command (DC) pin to 0 to send a command
    ST77XX_PORT &= ~(1 << ST77XX_DD_DC);

    SPI_MasterTransmit(command);

    // Deactivate the Chip Select (CS) of the display
    ST77XX_PORT |= (1 << ST77XX_DD_CS);
}

/*
 * @brief Resets the ST77XX display.
 *
 * This function resets the ST77XX display.
 */
void ST77XX_Reset() {
    // Reset the display
    ST77XX_PORT |= (1 << ST77XX_DD_RES);
    _delay_ms(5);

    ST77XX_PORT &= ~(1 << ST77XX_DD_RES);
    _delay_ms(5);

    ST77XX_PORT |= (1 << ST77XX_DD_RES);
    _delay_ms(120);

    ST77XX_PORT &= ~(1 << ST77XX_DD_RES);  // Pull reset low
    _delay_ms(10);

    ST77XX_PORT |= (1 << ST77XX_DD_RES);  // Pull reset high
    _delay_ms(120);
}

/*
 * @brief Structure to hold commands in program memory.
 */
typedef struct {
    uint8_t command;
    uint8_t dataCount;
    uint8_t data[16];  // Maximum number of data bytes per command
    uint16_t delayMs;  // Delay in milliseconds
} ST77XX_Command;

/*
 * @brief Initialization commands stored in program memory.
 */
const ST77XX_Command initCommands[] PROGMEM = {
    {ST77XX_NOP, 0, {0}, 120},
    {ST77XX_SWRESET, 0, {0}, 120},
    {ST77XX_SLPIN, 0, {0}, 120},
    {ST77XX_PTLON, 0, {0}, 120},
    {ST77XX_NORON, 0, {0}, 120},
    {ST77XX_INVON, 0, {0}, 120},
    // {ST77XX_INVOFF, 0, {0}, 120},
    {ST77XX_GAMSET, 1, {0x01}, 10},
    {ST77XX_DISPOFF, 0, {0}, 10},
    {ST77XX_DISPON, 0, {0}, 10},
    {ST77XX_PTLAR, 4, {0x00, 0x9F, 0x83, 0xA1}, 10},
    {ST77XX_SCRLAR, 6, {0x00, 0x00, 0x00, 0xA2, 0x00, 0x00}, 10},
    {ST77XX_TEOFF, 0, {0}, 10},
    {ST77XX_SCRLAR, 1, {0x00}, 10},
    {ST77XX_VSCSAD, 2, {0x00, 0x00}, 10},
    {ST77XX_IDMON, 0, {0}, 10},
    {ST77XX_IDMOFF, 0, {0}, 10},
    {ST77XX_COLMOD, 1, {0x65}, 10},
    {ST77XX_FRMCTR1, 3, {0x05, 0x3A, 0x3A}, 10},
    {ST77XX_FRMCTR2, 3, {0x05, 0x3A, 0x3A}, 10},
    {ST77XX_FRMCTR3, 6, {0x05, 0x3A, 0x3A, 0x05, 0x3A, 0x3A}, 10},
    {ST77XX_INVCTR, 1, {0xB4}, 10},
    {ST77XX_PWCTR1, 3, {0xA8, 0x08, 0x84}, 10},
    {ST77XX_PWCTR2, 1, {0xC1}, 10},
    {ST77XX_PWCTR3, 2, {0x0A, 0x00}, 10},
    {ST77XX_PWCTR4, 2, {0x8A, 0x26}, 10},
    {ST77XX_PWCTR5, 2, {0x8A, 0xEE}, 10},
    {ST77XX_VMCTR1, 1, {0xC5}, 10},
    {ST77XX_VMCTR1, 1, {0xC7}, 10},
    {ST77XX_NVFCTR1, 1, {0xD9}, 10},
    {ST77XX_NVFCTR3, 2, {0x3A, 0xC5}, 10},
    {ST77XX_GAMCTRP1,
     16,
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
     10},
    {ST77XX_GAMCTRN1,
     16,
     {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
     10},
    {ST77XX_GCV, 1, {0xFC}, 10},
    {ST77XX_SLPOUT, 0, {0}, 10},
    {ST77XX_CASET, 4, {0x00, 0x00, 0x00, ST77XX_DISPLAY_WIDTH}, 120},
    {ST77XX_RASET, 4, {0x00, 0x00, 0x00, ST77XX_DISPLAY_HEIGHT}, 120},
    {ST77XX_RAMWR, 0, {0}, 120},
};

/*
 * @brief Delays execution for the given number of milliseconds.
 *
 * @param ms The number of milliseconds to delay.
 */
void ST77XX_DelayMs(uint16_t ms) {
    while (ms--) {
        _delay_ms(1);
    }
}

/*
 * @brief Initializes the ST77XX display.
 *
 * This function initializes the ST77XX display by configuring the control pins,
 * resetting the display, and sending initialization commands.
 */
void ST77XX_InitDisplay() {
    // Set the control pins as output
    ST77XX_DDR |= (1 << ST77XX_DD_BLK) | (1 << ST77XX_DD_CS) | (1 << ST77XX_DD_DC) | (1 << ST77XX_DD_RES);

    ST77XX_Reset();  // Reset the display

    // Turn on backlight
    ST77XX_PORT |= (1 << ST77XX_DD_BLK);

    SPI_MasterInit(2);  // Initialize SPI

    // Iterate through the initCommands array stored in PROGMEM
    for (uint8_t i = 0; i < sizeof(initCommands) / sizeof(ST77XX_Command); i++) {
        // Read the command from PROGMEM
        uint8_t command = pgm_read_byte(&(initCommands[i].command));
        uint8_t dataCount = pgm_read_byte(&(initCommands[i].dataCount));
        uint16_t delayMs = pgm_read_word(&(initCommands[i].delayMs));

        // Send the command
        ST77XX_SendCommand(command);

        // If there are accompanying data bytes, send them as well
        for (uint8_t j = 0; j < dataCount; j++) {
            ST77XX_SendData(pgm_read_byte(&(initCommands[i].data[j])));
        }

        // Wait for the specified delay
        if (delayMs > 0) {
            ST77XX_DelayMs(delayMs);
        }
    }

    // ST77XX_FillScreenWithColor(0x0000);  // Clear screen with color
    _delay_ms(120);
}

/*
 * @brief Draws a pixel on the ST77XX display.
 *
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color of the pixel.
 *
 * This function draws a pixel at the specified coordinates with the specified
 * color on the ST77XX display.
 */
void ST77XX_DrawPixel(int16_t x, int16_t y, uint16_t color) {
    // Check if the coordinate is out of bounds of the display
    if (x < 0 || x >= ST77XX_DISPLAY_WIDTH || y < 0 || y >= ST77XX_DISPLAY_HEIGHT) return;

    // Setting the column (X) address
    ST77XX_SendCommand(ST77XX_CASET);
    ST77XX_SendData(0x00);
    ST77XX_SendData(x + ST77XX_DISPLAY_X_OFFSET);  // XSTART with offset
    ST77XX_SendData(0x00);
    ST77XX_SendData(x + ST77XX_DISPLAY_X_OFFSET);  // XEND with offset

    // Setting the row (Y) address
    ST77XX_SendCommand(ST77XX_RASET);
    ST77XX_SendData(0x00);
    ST77XX_SendData(y + ST77XX_DISPLAY_Y_OFFSET);  // YSTART
    ST77XX_SendData(0x00);
    ST77XX_SendData(y + ST77XX_DISPLAY_Y_OFFSET);  // YEND

    // Command to write to RAM
    ST77XX_SendCommand(ST77XX_RAMWR);

    // Sending the high and low bytes of the color
    ST77XX_SendData((uint8_t)(color >> 8));  // High byte of color
    ST77XX_SendData((uint8_t)color);         // Low byte of color
}

/*
 * @brief Draws a character on the ST77XX display.
 *
 * @param x The x-coordinate of the character.
 * @param y The y-coordinate of the character.
 * @param c The character to be drawn.
 * @param textColor The color of the character.
 * @param backgroundColor The background color behind the character.
 *
 * This function draws a character at the specified coordinates with the
 * specified color and background color on the ST77XX display.
 */
void ST77XX_DrawChar(int16_t x, int16_t y, char c, int16_t textColor, int16_t backgroundColor) {
    // Check if the character is out of the display bounds
    if (x >= ST77XX_DISPLAY_WIDTH || y >= ST77XX_DISPLAY_HEIGHT || (x + 5) < 0 || (y + 7) < 0) return;

    uint8_t pixelColumn;  // Column of pixels of the character
    int32_t columnIndex, rowIndex;

    // Iterate over the columns of the character
    for (columnIndex = 0; columnIndex < 6; columnIndex++) {
        if (columnIndex == 5) {
            pixelColumn = 0x0;  // Empty space between characters
        } else {
            // Use pgm_read_byte to read from flash memory
            pixelColumn = pgm_read_byte(&FONT[(c * 5) + columnIndex]);
        }

        // Iterate over the rows of the character
        for (rowIndex = 0; rowIndex < 8; rowIndex++) {
            if (pixelColumn & 0x1) {
                ST77XX_DrawPixel(x + columnIndex, y + rowIndex,
                                 textColor);  // Draw character pixel
            } else if (backgroundColor != textColor) {
                ST77XX_DrawPixel(x + columnIndex, y + rowIndex,
                                 backgroundColor);  // Draw background pixel
            }
            pixelColumn >>= 1;  // Move to the next bit of the column
        }
    }
}

/*
 * @brief Draws a string on the ST77XX display.
 *
 * @param x The x-coordinate of the starting position of the string.
 * @param y The y-coordinate of the starting position of the string.
 * @param str The string to be drawn.
 * @param textColor The color of the string.
 * @param backgroundColor The background color behind the string.
 *
 * @return The width of the drawn string in pixels.
 *
 * This function draws a string at the specified coordinates with the specified
 * color and background color on the ST77XX display and returns the width of the
 * drawn string in pixels.
 */
int16_t ST77XX_DrawString(uint16_t x, uint16_t y, char *str, int16_t textColor, int16_t backgroundColor) {
    while (*str) {
        if (x + 6 >= ST77XX_DISPLAY_WIDTH) {
            x = 0;   // Start of the new line
            y += 8;  // Move to the next line
            if (y >= ST77XX_DISPLAY_HEIGHT) {
                break;  // Exit if visible area is exceeded
            }
        }
        ST77XX_DrawChar(x, y, *str, textColor, backgroundColor);
        x += 6;  // Move to the next character position
        str++;
    }
    return (int16_t)((y << 8) | x);
}

/*
 * @brief Fills the entire ST77XX display with a specified color.
 *
 * @param color The color to fill the screen with.
 *
 * This function sets the column and row addresses to cover the entire screen
 * and then fills the screen with the specified color by writing the color data
 * to the display memory.
 */
void ST77XX_FillScreenWithColor(uint16_t color) {
    ST77XX_SendCommand(ST77XX_CASET);  // Column address set
    ST77XX_SendData(0x00);
    ST77XX_SendData(ST77XX_DISPLAY_X_OFFSET);
    ST77XX_SendData(0x00);
    ST77XX_SendData(ST77XX_DISPLAY_WIDTH + ST77XX_DISPLAY_X_OFFSET);

    ST77XX_SendCommand(ST77XX_RASET);  // Row address set
    ST77XX_SendData(0x00);
    ST77XX_SendData(ST77XX_DISPLAY_Y_OFFSET);  // Start row
    ST77XX_SendData(0x00);
    ST77XX_SendData(ST77XX_DISPLAY_HEIGHT + ST77XX_DISPLAY_Y_OFFSET);

    ST77XX_SendCommand(ST77XX_RAMWR);  // Memory write
    for (uint32_t i = 0; i < ((uint32_t)ST77XX_DISPLAY_WIDTH * (uint32_t)ST77XX_DISPLAY_HEIGHT); i++) {
        ST77XX_SendData(color >> 8);    // Send the most significant byte of the color
        ST77XX_SendData(color & 0xFF);  // Send the least significant byte of the color
    }
}

/*
 * @brief Draw a line between two points on the display.
 *
 * @param x0 Starting x-coordinate.
 * @param y0 Starting y-coordinate.
 * @param x1 Ending x-coordinate.
 * @param y1 Ending y-coordinate.
 * @param color Color of the line.
 */
void ST77XX_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    int16_t dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int16_t dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int16_t err = dx + dy, e2;

    while (1) {
        ST77XX_DrawPixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

/*
 * @brief Draw a horizontal line on the display.
 *
 * @param x Starting x-coordinate.
 * @param y Starting y-coordinate.
 * @param w Width of the line.
 * @param color Color of the line.
 */
void ST77XX_DrawHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    for (int16_t i = x; i < x + w; i++) {
        ST77XX_DrawPixel(i, y, color);
    }
}

/*
 * @brief Draw a vertical line on the display.
 *
 * @param x Starting x-coordinate.
 * @param y Starting y-coordinate.
 * @param h Height of the line.
 * @param color Color of the line.
 */
void ST77XX_DrawVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    for (int16_t i = y; i < y + h; i++) {
        ST77XX_DrawPixel(x, i, color);
    }
}

/*
 * @brief Draw a diagonal line on the display.
 *
 * @param x0 Starting x-coordinate.
 * @param y0 Starting y-coordinate.
 * @param length Length of the line.
 * @param angle Angle of the line in radians.
 * @param color Color of the line.
 */
void ST77XX_DrawDLine(int16_t x0, int16_t y0, int16_t length, float angle, uint16_t color) {
    int16_t x1 = x0 + length * cos(angle);
    int16_t y1 = y0 + length * sin(angle);
    ST77XX_DrawLine(x0, y0, x1, y1, color);
}

/*
 * @brief Draw a rectangle on the display.
 *
 * @param x Top-left x-coordinate.
 * @param y Top-left y-coordinate.
 * @param width Width of the rectangle.
 * @param height Height of the rectangle.
 * @param color Color of the rectangle.
 */
void ST77XX_DrawRect(int x, int y, int width, int height, uint16_t color) {
    for (int i = 0; i < width; i++) {
        ST77XX_DrawPixel(x + i, y, color);
        ST77XX_DrawPixel(x + i, y + height - 1, color);
    }
    for (int i = 0; i < height; i++) {
        ST77XX_DrawPixel(x, y + i, color);
        ST77XX_DrawPixel(x + width - 1, y + i, color);
    }
}

/*
 * @brief Fill a rectangle on the display.
 *
 * @param x Top-left x-coordinate.
 * @param y Top-left y-coordinate.
 * @param width Width of the rectangle.
 * @param height Height of the rectangle.
 * @param color Color of the rectangle.
 */
void ST77XX_FillRect(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color) {
    for (int16_t i = x; i < x + width; i++) {
        for (int16_t j = y; j < y + height; j++) {
            ST77XX_DrawPixel(i, j, color);
        }
    }
}

/*
 * @brief Draw a circle on the display.
 *
 * @param x0 Center x-coordinate.
 * @param y0 Center y-coordinate.
 * @param r Radius of the circle.
 * @param color Color of the circle.
 */
void ST77XX_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    ST77XX_DrawPixel(x0, y0 + r, color);
    ST77XX_DrawPixel(x0, y0 - r, color);
    ST77XX_DrawPixel(x0 + r, y0, color);
    ST77XX_DrawPixel(x0 - r, y0, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        ST77XX_DrawPixel(x0 + x, y0 + y, color);
        ST77XX_DrawPixel(x0 - x, y0 + y, color);
        ST77XX_DrawPixel(x0 + x, y0 - y, color);
        ST77XX_DrawPixel(x0 - x, y0 - y, color);
        ST77XX_DrawPixel(x0 + y, y0 + x, color);
        ST77XX_DrawPixel(x0 - y, y0 + x, color);
        ST77XX_DrawPixel(x0 + y, y0 - x, color);
        ST77XX_DrawPixel(x0 - y, y0 - x, color);
    }
}

/*
 * @brief Fill a circle on the display.
 *
 * @param x0 Center x-coordinate.
 * @param y0 Center y-coordinate.
 * @param r Radius of the circle.
 * @param color Color of the circle.
 */
void ST77XX_FillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
    ST77XX_DrawVLine(x0, y0 - r, 2 * r + 1, color);
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        ST77XX_DrawVLine(x0 + x, y0 - y, 2 * y + 1, color);
        ST77XX_DrawVLine(x0 - x, y0 - y, 2 * y + 1, color);
        ST77XX_DrawVLine(x0 + y, y0 - x, 2 * x + 1, color);
        ST77XX_DrawVLine(x0 - y, y0 - x, 2 * x + 1, color);
    }
}

/*
 * @brief Draw a polygon on the display.
 *
 * @param x Array of x-coordinates for each vertex.
 * @param y Array of y-coordinates for each vertex.
 * @param num_sides Number of sides (or vertices) of the polygon.
 * @param color Color of the polygon.
 */
void ST77XX_DrawPolygon(int16_t *x, int16_t *y, uint16_t num_sides, uint16_t color) {
    for (uint16_t i = 0; i < num_sides - 1; i++) {
        ST77XX_DrawLine(x[i], y[i], x[i + 1], y[i + 1], color);
    }
    ST77XX_DrawLine(x[num_sides - 1], y[num_sides - 1], x[0], y[0], color);
}

/*
 * @brief Fill a polygon on the display.
 *
 * @param x Array of x-coordinates for each vertex.
 * @param y Array of y-coordinates for each vertex.
 * @param num_sides Number of sides (or vertices) of the polygon.
 * @param color Color of the polygon.
 */
void ST77XX_FillPolygon(int16_t *x, int16_t *y, uint16_t num_sides, uint16_t color) {
    if (num_sides < 3) return;

    int16_t minY = y[0], maxY = y[0];

    for (uint16_t i = 1; i < num_sides; i++) {
        if (y[i] < minY) minY = y[i];
        if (y[i] > maxY) maxY = y[i];
    }

    for (int16_t currentY = minY; currentY <= maxY; currentY++) {
        int16_t intersections[num_sides];
        uint16_t num_intersections = 0;

        for (uint16_t i = 0; i < num_sides; i++) {
            int16_t x0 = x[i], y0 = y[i];
            int16_t x1 = x[(i + 1) % num_sides], y1 = y[(i + 1) % num_sides];
            if ((y0 < currentY && y1 >= currentY) || (y1 < currentY && y0 >= currentY)) {
                if (y0 == y1) {
                    intersections[num_intersections++] = x0;
                } else {
                    intersections[num_intersections++] = x0 + (currentY - y0) * (x1 - x0) / (y1 - y0);
                }
            }
        }

        for (uint16_t i = 0; i < num_intersections - 1; i++) {
            for (uint16_t j = i + 1; j < num_intersections; j++) {
                if (intersections[i] > intersections[j]) {
                    int16_t temp = intersections[i];
                    intersections[i] = intersections[j];
                    intersections[j] = temp;
                }
            }
        }

        for (uint16_t i = 0; i < num_intersections; i += 2) {
            if (i + 1 < num_intersections) {
                ST77XX_DrawHLine(intersections[i], currentY, intersections[i + 1] - intersections[i] + 1, color);
            }
        }
    }
}

/*
 * @brief Draw a triangle on the display.
 *
 * @param x0 x-coordinate of the first vertex.
 * @param y0 y-coordinate of the first vertex.
 * @param x1 x-coordinate of the second vertex.
 * @param y1 y-coordinate of the second vertex.
 * @param x2 x-coordinate of the third vertex.
 * @param y2 y-coordinate of the third vertex.
 * @param color Color of the triangle.
 */
void ST77XX_DrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    ST77XX_DrawLine(x0, y0, x1, y1, color);
    ST77XX_DrawLine(x1, y1, x2, y2, color);
    ST77XX_DrawLine(x2, y2, x0, y0, color);
}

/*
 * @brief Fill a triangle on the display.
 *
 * @param x0 x-coordinate of the first vertex.
 * @param y0 y-coordinate of the first vertex.
 * @param x1 x-coordinate of the second vertex.
 * @param y1 y-coordinate of the second vertex.
 * @param x2 x-coordinate of the third vertex.
 * @param y2 y-coordinate of the third vertex.
 * @param color Color of the triangle.
 */
void ST77XX_FillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    int16_t x[3], y[3];
    x[0] = x0;
    y[0] = y0;
    x[1] = x1;
    y[1] = y1;
    x[2] = x2;
    y[2] = y2;
    ST77XX_FillPolygon(x, y, 3, color);
}

/*
 * @brief Fills the button with the border color and draws the text at the center of the button.
 *
 * @param x The x-coordinate of the top-left corner of the button.
 * @param y The y-coordinate of the top-left corner of the button.
 * @param width The width of the button.
 * @param height The height of the button.
 * @param borderColor The color of the button's border.
 * @param textColor The color of the button's text.
 * @param label The text to be displayed on the button.
 */
void ST77XX_FillButtonWithText(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t borderColor,
                               int16_t textColor, char *label) {
    ST77XX_FillRect(x, y, width, height, borderColor);
    int16_t textX = x + (width - strlen(label) * 6) / 2;
    ST77XX_DrawString(textX, y + height / 2 - 6, label, textColor, borderColor);
}

/*
 * @brief Draws the button's outline with the border color, fills the background with the background color, and draws
 * the text at the center of the button.
 *
 * @param x The x-coordinate of the top-left corner of the button.
 * @param y The y-coordinate of the top-left corner of the button.
 * @param width The width of the button.
 * @param height The height of the button.
 * @param borderColor The color of the button's border.
 * @param textColor The color of the button's text.
 * @param backgroundColor The background color of the button.
 * @param label The text to be displayed on the button.
 */
void ST77XX_DrawButtonWithText(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t borderColor,
                               int16_t textColor, int16_t backgroundColor, char *label) {
    ST77XX_DrawRect(x, y, width, height, borderColor);
    int16_t textX = x + (width - strlen(label) * 6) / 2;
    ST77XX_DrawString(textX, y + height / 2 - 6, label, textColor, backgroundColor);
}