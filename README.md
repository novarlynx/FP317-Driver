# FP317
Arduino &amp; ESP32 based driver for Ferranti Packard 317 flip dot display boards with FP2800A chips

- FP317_driver is the actual driver that allows for interfacing with the MCU.
- FP317_driver_pins is the configuration file for the driver. Required to operate.
- FP317_gfx is a subclass of Adafruit_GFX (https://github.com/adafruit/Adafruit-GFX-Library) that uses FP317_driver to draw stuff.

This driver was made for the 317 display but could be adapted to any 14 x 28 flip dot display using a pair of FP2800A drivers.
