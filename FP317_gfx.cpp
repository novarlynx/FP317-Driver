/*
 * File: FP317_gfx.cpp
 * Subclass of Adafruit_GFX implementing FP317_driver to allow graphics to be drawn on FP 317 displays.
 * Adafruit GFX https://github.com/adafruit/Adafruit-GFX-Library
 * 
 * Created by Andrew (Novar Lynx) (C) 2022
 * License is LGPL 2.1 https://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html
 * 
 * General Notes:
 * 1. Since the screen is effectively monochrome, any color that is not black (0) will turn ON the dot.
 * 2. Due to the rather low resolution of flip dot screens, nearly all the font files in the Adafruit library are pretty useless.
   For this reason I have created a font for these displays based off an actual font Ferranti-Packard used, called Ferranti7.h.
   Nieto's Luminator fonts work well too: https://github.com/NietoSkunk/MAX3000_Library
   
 
 * IMPORTANT: FP317_driver_pins.h must be provided as it holds configuration for the class instance (Pin assignments and other parameters)
 */

#include "Arduino.h"
#include <Adafruit_GFX.h>
#include <FP317_driver.h>
#include "FP317_gfx.h"

// screen width and height is determined by code that runs in the FP317 driver's constructor, unlike other implementations of Adafruit_GFX.
FP317_gfx::FP317_gfx() : Adafruit_GFX(28,28)
{
  drv = new FP317_driver();  
  _width = drv->getWidth();
  _height = drv->getHeight();
}

void FP317_gfx::drawPixel(int16_t x, int16_t y, uint16_t color)
{
  // Any color other than 0 (black) will be assumed to be turn the dot on.
  bool state = false;
  if (color != 0000) {
    state = true;
  }

  drv->setDot(x, y, state);  
  // Allows for inserting artifical lag for aesthetic reasons. Default is 0.
  delay(lag);
}

// Gives access to the driver's clear function
void FP317_gfx::clearDisplay()
{
  drv->clearDisplay();
}

// Interface for setting the artificial lag, in milliseconds.
void FP317_gfx::setLag(int16_t lag_)
{
  lag = lag_;
}
