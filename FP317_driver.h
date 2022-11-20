/*
 * File: FP317_driver.h
 * Class for driving a group of Ferranti-Packard 317 flip dot displays using FP2800A drivers
 * Capable of controlling up to eight displays using IO pins or shift registers depending on chip.
 * Pin and display settings are configured using FP317_driver_pins.h
 * 
 * Created by Andrew (Novar Lynx) (C) 2022
 * License is LGPL 2.1 https://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html
 */

// IMPORTANT: FP317_driver_pins.h must be provided as it holds configuration for the class instance (Pin assignments and other parameters)

#ifndef FP317_driver_h
#define FP317_driver_h

#include "Arduino.h"

class FP317_driver
{
  int width = 0;
  int height = 0;
  
  public:
    FP317_driver();
    void setDot(int16_t x, int16_t y, bool state);
    void clearDisplay();
    int16_t getWidth();
    int16_t getHeight();
    
  private:
    int invertNum(int num, int range);
    int getDispCnt();
};

#endif
