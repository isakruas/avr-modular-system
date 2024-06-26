# Makefile for compiling C code with GTK and libxml2
# -----------------------------------------------------------

# Executable file name
TARGET = main

# Compiler and flags
CC = gcc
CFLAGS = $(shell pkg-config --cflags gtk+-3.0 libxml-2.0)
LDFLAGS = $(shell pkg-config --libs gtk+-3.0 libxml-2.0)

# Include directories
INC_DIRS = 

# Source files
SRCS = src/main.c

# Objects
OBJ_DIR = build/obj
OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

all: $(TARGET)

# Compilation of source files into objects
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@

# Linking objects into the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INC_DIRS) -o $@ $^ $(LDFLAGS)

# Cleaning generated files
clean:
	rm -rf build

# Option for code formatting
format:
	find . -name '*.c' -o -name '*.h' | xargs clang-format -i

# Defines rules that do not correspond to real file names as "phony"
.PHONY: all clean format

# Install dependencies
install-dependencies:
	@echo "Please run the following command to install dependencies:"
	@echo "sudo apt-get install libgtk-3-dev libxml2-dev"

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
