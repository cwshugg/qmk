# This defines compile-time rules for the QMK firmware.

# Include extra source files in compilation
SRC += layers.c screen.c activity.c

# Use DFU Bootlader for Elite-C
BOOTLOADER =            atmel-dfu

# Enable Link-Time Optimization
LTO_ENABLE =            yes

# Enable OLED screen
OLED_ENABLE	=           yes
OLED_DRIVER =           ssd1306
OLED_DRIVER_ENABLE =    yes

# Enable use of system and audio control keycodes
EXTRAKEY_ENABLE =       yes

