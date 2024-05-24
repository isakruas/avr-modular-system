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
    {ST77XX_INVOFF, 0, {0}, 120},
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
    {ST77XX_COLMOD, 1, {0x05}, 10},
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

    SPI_MasterInit();  // Initialize SPI

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
