/*
 * File: FP317_gfx.h
 * Subclass of Adafruit_GFX implementing FP317_driver to allow graphics to be drawn on FP 317 displays.
 * Adafruit GFX https://github.com/adafruit/Adafruit-GFX-Library
 * 
 * Created by Andrew (Novar Lynx) (C) 2022
 * License is LGPL 2.1 https://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html
*/

#ifndef FP317_gfx_h
#define FP317_gfx_h

#include "Arduino.h"
#include "Adafruit_GFX.h"
#include "FP317_driver.h"

class FP317_gfx : public Adafruit_GFX
{
  FP317_driver* drv;
  int16_t lag = 0;
  public:
    FP317_gfx();
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void clearDisplay();
    void setLag(int16_t lag_);


};

#endif
