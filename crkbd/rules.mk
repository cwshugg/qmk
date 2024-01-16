# This defines compile-time rules for the QMK firmware.

# Include extra source files in compilation
SRC += layers.c screen.c activity.c sync.c

# Use DFU Bootlader for Elite-C
BOOTLOADER =            atmel-dfu

# Enable Link-Time Optimization
LTO_ENABLE =            yes

# Enable split keyboard features
SPLIT_KEYBOARD =        yes

# Enable OLED screen
OLED_ENABLE	=           yes
OLED_DRIVER =           ssd1306
OLED_DRIVER_ENABLE =    yes

# Enable use of system and audio control keycodes
EXTRAKEY_ENABLE =       yes

# Enable use of tap dancing
TAP_DANCE_ENABLE =      yes

