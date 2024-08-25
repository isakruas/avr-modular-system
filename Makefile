# Makefile for compiling and programming an AVR microcontroller
# -----------------------------------------------------------

# Executable file name
TARGET = main

# Compiler and flags
CC = avr-g++
CFLAGS = -Os -mmcu=atmega32a -DF_CPU=16000000UL
INC_DIRS = -I./src/modules/module1 -I./src/modules/module2

# Source files
SRCS = src/main.c src/modules/module1/module1.c src/modules/module2/module2.c

# Objects
OBJ_DIR = build/obj
OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

# Programming commands
AVRDUDE = avrdude
AVRDUDE_PROGRAMMER = -c usbasp 
AVRDUDE_PORT = -P usb 
AVRDUDE_MCU = atmega32a
AVRDUDE_FUSES = -U lfuse:w:0xFF:m -U hfuse:w:0xC9:m -U efuse:w:0xFF:m
AVRDUDE_FLAGS = $(AVRDUDE_PROGRAMMER) $(AVRDUDE_PORT) -p $(AVRDUDE_MCU)

# Rules
all: build/$(TARGET).hex

# Compilation of firmware into hexadecimal format
build/$(TARGET).hex: build/$(TARGET).elf
	avr-objcopy -O ihex -R .eeprom $< $@

# Generation of ELF file from compiled objects
build/$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(INC_DIRS) -o $@ $^

# Compilation of source files into objects
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@

# Cleaning generated files
clean:
	rm -rf build

# Programming firmware into microcontroller
flash: build/$(TARGET).hex
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_FUSES) -U flash:w:$<

# Option for code formatting: You can use clang-format for automatic code formatting.
# To install clang-format, use the following command:
# sudo apt-get install clang-format
format:
	find . -name '*.c' -o -name '*.h' | xargs clang-format -i

# Defines rules that do not correspond to real file names as "phony"
.PHONY: all clean flash format

# Defines "all" as the default rule
.DEFAULT_GOAL := all

# Install dependencies
install-dependencies:
	@echo "Please run the following command to install dependencies:"
	@echo "sudo apt-get install gcc-avr avrdude avr-libc"

# MIT License
# -----------
#
# Copyright (c) 2024 Isak Ruas
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
