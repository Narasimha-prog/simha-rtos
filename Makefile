# Project Name
TARGET = nexus_os

# Toolchain Setup (Updated for version 15.2.0)
CC = xtensa-esp-elf-gcc
LD = xtensa-esp-elf-gcc
OBJCOPY = xtensa-esp-elf-objcopy

# Directory Structure
BUILD_DIR = build
SRC_DIRS = kernel shell drivers/bus net services api

# Compiler Flags
# -mlongcalls: Required for ESP32 to handle function calls across large memory addresses
# -nostdlib: We are building a "Mini OS", so we don't want standard C libraries yet
CFLAGS = -mlongcalls -Wall -Wextra -I. -Ikernel/include -O2 -g
LDFLAGS = -nostdlib -T esp32.ld

# Automatically find all .c files in defined source directories
SRCS = main.c $(shell find $(SRC_DIRS) -name '*.c')
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

# Default Rule
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin

# Link the .elf file
$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	@mkdir -p $(@D)
	$(LD) $(OBJS) $(LDFLAGS) -o $@

# Create a flat binary for flashing to real hardware
$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# Compile .c files to .o files
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Build Files
clean:
	rm -rf $(BUILD_DIR)

# Run Simulation (Shortcut for Renode)
sim: all
	renode scripts/run_renode.resc

.PHONY: all clean sim