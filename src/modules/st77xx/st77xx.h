/*
 * Header guard to prevent multiple inclusions of the "st77xx.h" header file.
 */
#ifndef ST77XX_H
#define ST77XX_H

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

#include "glcdfont.h"

#define ST77XX_DDR DDRB
#define ST77XX_PORT PORTB

#define ST77XX_DD_BLK PB0  // Backlight pin
#define ST77XX_DD_CS PB1   // Chip select pin
#define ST77XX_DD_DC PB2   // Data/command pin
#define ST77XX_DD_RES PB3  // Reset pin

#ifndef ST77XX_DISPLAY_WIDTH
#define ST77XX_DISPLAY_WIDTH 240
#endif

#ifndef ST77XX_DISPLAY_HEIGHT
#define ST77XX_DISPLAY_HEIGHT 240
#endif

#ifndef ST77XX_DISPLAY_X_OFFSET
#define ST77XX_DISPLAY_X_OFFSET 0
#endif

#ifndef ST77XX_DISPLAY_Y_OFFSET
#define ST77XX_DISPLAY_Y_OFFSET 0
#endif

// ST77XX System Function Command List and Description
#define ST77XX_NOP 0x00         // No Operation
#define ST77XX_SWRESET 0x01     // Software Reset
#define ST77XX_RDDID 0x04       // Read Display ID
#define ST77XX_RDDST 0x09       // Read Display Status
#define ST77XX_RDDPM 0x0A       // Read Display Power Mode
#define ST77XX_RDDMADCTL 0x0B   // Read Display MADCTL
#define ST77XX_RDDCOLMODL 0x0C  // Read Display Pixel Format
#define ST77XX_RDDIM 0x0D       // Read Display Image Mode
#define ST77XX_RDDSM 0x0E       // Read Display Signal Mode
#define ST77XX_RDDSDR 0x0F      // Read Display Self-diagnostic result
#define ST77XX_SLPIN 0x10       // Sleep In & Booster Off
#define ST77XX_SLPOUT 0x11      // Sleep Out & Booster On
#define ST77XX_PTLON 0x12       // Partial Mode On
#define ST77XX_NORON 0x13       // Partial Off (Normal)
#define ST77XX_INVOFF 0x20      // Display Inversion Off (Normal)
#define ST77XX_INVON 0x21       // Display Inversion On
#define ST77XX_GAMSET 0x26      // Gamma Curve Select
#define ST77XX_DISPOFF 0x28     // Display Off
#define ST77XX_DISPON 0x29      // Display On
#define ST77XX_CASET 0x2A       // Column Address Set
#define ST77XX_RASET 0x2B       // Row Address Set
#define ST77XX_RAMWR 0x2C       // Memory Write
#define ST77XX_RGBSET 0x2D      // LUT for 4k,65k,262k Color display
#define ST77XX_RAMRD 0x2E       // Memory Read
#define ST77XX_PTLAR 0x30       // Partial Start/End Address Set
#define ST77XX_SCRLAR 0x33      // Scroll area set
#define ST77XX_TEOFF 0x34       // Tearing effect line off
#define ST77XX_TEON 0x35        // Tearing Effect Mode Set & on
#define ST77XX_MADCTL 0x36      // Memory Data Access Control
#define ST77XX_VSCSAD 0x37      // Scroll Start Address of RAM
#define ST77XX_IDMOFF 0x38      // Idle Mode Off
#define ST77XX_IDMON 0x39       // Idle Mode On
#define ST77XX_COLMOD 0x3A      // Interface Pixel Format
#define ST77XX_RDID1 0xDA       // Read ID1
#define ST77XX_RDID2 0xDB       // Read ID2
#define ST77XX_RDID3 0xDC       // Read ID3

// ST77XX Panel Function Command List and Description
#define ST77XX_FRMCTR1 0xB1   // In Normal Mode (Full Colors)
#define ST77XX_FRMCTR2 0xB2   // In Idle Mode (8-colors)
#define ST77XX_FRMCTR3 0xB3   // In Partial Mode + Full Colors
#define ST77XX_INVCTR 0xB4    // Display Inversion Control
#define ST77XX_PWCTR1 0xC0    // Power Control Setting
#define ST77XX_PWCTR2 0xC1    // Power Control Setting
#define ST77XX_PWCTR3 0xC2    // In Normal Mode (Full Colors)
#define ST77XX_PWCTR4 0xC3    // In Idle Mode (8-colors)
#define ST77XX_PWCTR5 0xC4    // In Partial Mode + Full colors
#define ST77XX_VMCTR1 0xC5    // VCOM Control 1
#define ST77XX_VMOFCTR 0xC7   // Set VCOM Offset control
#define ST77XX_WRID2 0xD1     // Set LCM Version Code
#define ST77XX_WRID3 0xD2     // Customer Project Code
#define ST77XX_NVFCTR1 0xD9   // NVM Control Status
#define ST77XX_NVFCTR2 0xDE   // NVM Read Command
#define ST77XX_NVFCTR3 0xDF   // NVM Write Command Action Code
#define ST77XX_GAMCTRP1 0xE0  // Set Gamma Adjustment (+ Polarity)
#define ST77XX_GAMCTRN1 0xE1  // Set Gamma Adjustment (- Polarity)
#define ST77XX_GCV 0xFC       // Gate Pump Clock Frequency Variable

/*
 * @brief Sends data to the ST77XX display.
 *
 * @param data The data byte to be sent.
 *
 * This function sends a single byte of data to the ST77XX display.
 */
void ST77XX_SendData(uint8_t data);

/*
 * @brief Sends a command to the ST77XX display.
 *
 * @param command The command byte to be sent.
 *
 * This function sends a single byte command to the ST77XX display.
 */
void ST77XX_SendCommand(uint8_t command);

/*
 * @brief Resets the ST77XX display.
 *
 * This function resets the ST77XX display by toggling the reset pin.
 */
void ST77XX_Reset();

/*
 * @brief Initializes the ST77XX display.
 *
 * This function initializes the ST77XX display by configuring its control pins
 * and sending initialization commands.
 */
void ST77XX_InitDisplay();

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
void ST77XX_DrawPixel(int16_t x, int16_t y, uint16_t color);

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
void ST77XX_DrawChar(int16_t x, int16_t y, char c, int16_t textColor, int16_t backgroundColor);

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
int16_t ST77XX_DrawString(uint16_t x, uint16_t y, char *str, int16_t textColor, int16_t backgroundColor);

/*
 * @brief Fills the entire ST77XX display with a specified color.
 *
 * @param color The color to fill the screen with.
 *
 * This function sets the column and row addresses to cover the entire screen
 * and then fills the screen with the specified color by writing the color data
 * to the display memory.
 */
void ST77XX_FillScreenWithColor(uint16_t color);

/*
 * @brief Delays execution for the given number of milliseconds.
 *
 * @param ms The number of milliseconds to delay.
 */
void ST77XX_DelayMs(uint16_t ms);

/*
 * @brief Draw a line between two points on the display.
 *
 * @param x0 Starting x-coordinate.
 * @param y0 Starting y-coordinate.
 * @param x1 Ending x-coordinate.
 * @param y1 Ending y-coordinate.
 * @param color Color of the line.
 */
void ST77XX_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

/*
 * @brief Draw a horizontal line on the display.
 *
 * @param x Starting x-coordinate.
 * @param y Starting y-coordinate.
 * @param w Width of the line.
 * @param color Color of the line.
 */
void ST77XX_DrawHLine(int16_t x, int16_t y, int16_t w, uint16_t color);

/*
 * @brief Draw a vertical line on the display.
 *
 * @param x Starting x-coordinate.
 * @param y Starting y-coordinate.
 * @param h Height of the line.
 * @param color Color of the line.
 */
void ST77XX_DrawVLine(int16_t x, int16_t y, int16_t h, uint16_t color);

/*
 * @brief Draw a diagonal line on the display.
 *
 * @param x0 Starting x-coordinate.
 * @param y0 Starting y-coordinate.
 * @param length Length of the line.
 * @param angle Angle of the line in radians.
 * @param color Color of the line.
 */
void ST77XX_DrawDLine(int16_t x0, int16_t y0, int16_t length, float angle, uint16_t color);

/*
 * @brief Draw a rectangle on the display.
 *
 * @param x Top-left x-coordinate.
 * @param y Top-left y-coordinate.
 * @param width Width of the rectangle.
 * @param height Height of the rectangle.
 * @param color Color of the rectangle.
 */
void ST77XX_DrawRect(int x, int y, int width, int height, uint16_t color);

/*
 * @brief Fill a rectangle on the display.
 *
 * @param x Top-left x-coordinate.
 * @param y Top-left y-coordinate.
 * @param width Width of the rectangle.
 * @param height Height of the rectangle.
 * @param color Color of the rectangle.
 */
void ST77XX_FillRect(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);

/*
 * @brief Draw a circle on the display.
 *
 * @param x0 Center x-coordinate.
 * @param y0 Center y-coordinate.
 * @param r Radius of the circle.
 * @param color Color of the circle.
 */
void ST77XX_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

/*
 * @brief Fill a circle on the display.
 *
 * @param x0 Center x-coordinate.
 * @param y0 Center y-coordinate.
 * @param r Radius of the circle.
 * @param color Color of the circle.
 */
void ST77XX_FillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

/*
 * @brief Draw a polygon on the display.
 *
 * @param x Array of x-coordinates for each vertex.
 * @param y Array of y-coordinates for each vertex.
 * @param num_sides Number of sides (or vertices) of the polygon.
 * @param color Color of the polygon.
 */
void ST77XX_DrawPolygon(int16_t *x, int16_t *y, uint16_t num_sides, uint16_t color);

/*
 * @brief Fill a polygon on the display.
 *
 * @param x Array of x-coordinates for each vertex.
 * @param y Array of y-coordinates for each vertex.
 * @param num_sides Number of sides (or vertices) of the polygon.
 * @param color Color of the polygon.
 */
void ST77XX_FillPolygon(int16_t *x, int16_t *y, uint16_t num_sides, uint16_t color);

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
void ST77XX_DrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

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
void ST77XX_FillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

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
                               int16_t textColor, char *label);

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
                               int16_t textColor, int16_t backgroundColor, char *label);

#endif  // ST77XX_H
