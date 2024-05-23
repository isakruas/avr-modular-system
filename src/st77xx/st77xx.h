/*
 * Header guard to prevent multiple inclusions of the "st77xx.h" header file.
 */
#ifndef ST77XX_H
#define ST77XX_H

#include <avr/io.h>
#include <avr/pgmspace.h>
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

#endif  // ST77XX_H
