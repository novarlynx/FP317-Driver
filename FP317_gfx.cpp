#include "Arduino.h"
#include <Adafruit_GFX.h>
#include "FP317_driver.h"

#include "FP317_gfx.h"



// screen width and height is determined by code that runs in the FP317 driver's constructor.
// provide FP317_driver_pins.h to set these parameters as well as MCU type.

// unlike other implementations of Adafruit_GFX.
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
}

void FP317_gfx::test()
{
  
}
