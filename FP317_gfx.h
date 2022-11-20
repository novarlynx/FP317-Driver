#ifndef FP317_gfx_h
#define FP317_gfx_h

#include "Arduino.h"
#include "Adafruit_GFX.h"
#include "FP317_driver.h"

class FP317_gfx : public Adafruit_GFX
{
  FP317_driver* drv;
  public:
    FP317_gfx();
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void test();


};

#endif
