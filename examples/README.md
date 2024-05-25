# Examples Directory

The `examples` directory showcases various example projects utilizing different external modules and protocols.
 
### Examples Description:
- **at24c256**: Example project interfacing with AT24C256 EEPROM using I2C protocol.
- **cp2102**: Example project targeting CP2102 USB to UART bridge.
- **pcf8574**: Example interacting with PCF8574 I/O expander using I2C protocol.
- **st7735s**: Example controlling ST7735S TFT display using SPI protocol.
- **st7789**: Example controlling ST7789 TFT display using SPI protocol.


**Note:** For using st77xx, you should adjust ST77XX_INVOFF and ST77XX_COLMOD as indicated in the datasheet for each model.

## Compilation Instructions

1. Navigate to the example directory you want to compile.
2. Run:
   ```sh
   make
   ```
3. Follow any additional instructions specific to the example in its own `README.md` or comments within source files.

## License
This project is distributed under the [MIT License](https://opensource.org/licenses/MIT).
