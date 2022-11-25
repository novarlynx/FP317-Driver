/*
 * File: FP317_driver.cpp
 * Class for driving a group of Ferranti-Packard 317 flip dot displays using FP2800A drivers
 * Capable of controlling up to eight displays using IO pins or shift registers depending on chip.
 * Pin and display settings are configured using FP317_driver_pins.h
 * 
 * Created by Andrew (Novar Lynx) (C) 2022
 * License is LGPL 2.1 https://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html
 */

// IMPORTANT: FP317_driver_pins.h must be provided as it holds configuration for the class instance (Pin assignments and other parameters)
// You can download it from my github: https://github.com/novarlynx/FP317-Driver/blob/main/FP317_driver_pins.h

// When initialized the driver will automatically determine the display's width and height based on which boards are enabled in FP317_driver_pins.h
// Please see the comments in that file for more details on this function.

#include "Arduino.h"
#include "FP317_driver.h"
#include "FP317_driver_pins.h"

FP317_driver::FP317_driver()
{
  // configure pins
  pinMode(PIN_U1_A0, OUTPUT);
  pinMode(PIN_U1_A1, OUTPUT);
  pinMode(PIN_U1_A2, OUTPUT); 
  pinMode(PIN_U1_B0, OUTPUT);
  pinMode(PIN_U1_B1, OUTPUT);
  pinMode(PIN_U1_DATA, OUTPUT);
  pinMode(PIN_U2_A0, OUTPUT);
  pinMode(PIN_U2_A1, OUTPUT);
  pinMode(PIN_U2_A2, OUTPUT);
  pinMode(PIN_U2_B0, OUTPUT); // also U2_DATA
  pinMode(PIN_U2_B1, OUTPUT);

  // Calculate the width and height of the entire array of displays
  byte gridXcount = 0;
  byte gridYcount = 0;

  for (int i = 0; i < getDispCnt(); i++)
  {
    // Count display columns (GridX) only looking at the 1st row (GridY = 1)
    if (displays[i].gridY == 1) {
      if (displays[i].enabled == true) {
        gridXcount += 1;
      }
    }
    // Count display rows (GridY) only looking at the 1st column (GridX = 1)
    if (displays[i].gridX == 1) {
      if (displays[i].enabled == true) {
        gridYcount += 1;
      }
    }
    // Configure the ENABLE pins while we're at it
    pinMode(displays[i].PIN_ENABLE, OUTPUT);
    digitalWrite(displays[i].PIN_ENABLE, LOW);
  }
  // Using the counts, figure out the width and height
  width = 28 * gridXcount - 1;
  height = 14 * gridYcount - 1;

  // Clear the display
  clearDisplay(); 
}

void FP317_driver::setDot(int16_t x, int16_t y, bool state)
{
  FP317_module disp;

  // Escape if the dot is out of bounds
  if (!((x >= 0) && (x < width + 1) && (y >= 0) && (y < height + 1))) {
    return;   
  }

  // Step 1, get the display module the coordinates are in.

  // For X, the range of a single module is 1 to 28. Therefore here's the ranges for four displays across GridX:
  // 1 = 1 to 28; 2 = 29 to 56; 3 = 57 to 84; 4 = 85 to 112.
  // For simplicity for code we'll start at 0 instead:
  // 1 = 0 to 27; 2 = 28 to 55; 3 = 56 to 83; 4 = 84 to 111.

  // Find the display in the array.
  byte gridX = (x / 28) + 1;
  byte gridY = (y / 14) + 1;
  bool found = false;

  for (int d = 0; d < getDispCnt(); d++)
  {
    if (displays[d].enabled == true &&
        displays[d].gridX == gridX &&
        displays[d].gridY == gridY)
    {
      disp = displays[d];
      found = true;
      break;
    }
  }
  if (found == false) {
    // This is indicative of a configuration error. Todo, add a way to tell the user about this
    return;
  }
  
  // Determine if the display's gridRow is odd or even.. Odd means FP2800 chips are on top, even means FP2800 chips are on bottom
  bool even = false;
  if (disp.gridY % 2 == 0) { even = true; }

  // Step 2, set the drivers' X coordinate
  // first correct an X coordinate that exceeds the display's range
  x = x - ((x / 28) * 28);
  // then make the calculations
  int xGroup = (x - (x % 7)) / 7;
  int xPixel = (x % 7) + 1;
  // Invert for an odd row
  if (!even) {
    xGroup = invertNum(xGroup, 3);
    xPixel = invertNum(xPixel, 8); 
  }
 
  // Step 3, set the drivers' Y coordinate
  // first correct a Y coordinate that exceeds the display's range
  y = y - ((y / 14) * 14);
  // then make the calculations
  int yGroup = (y - (y % 7)) / 7;
  int yPixel = (y % 7) + 1;
  // Invert group for an odd row & invert pixel of ran even row
  if (even) { yGroup = invertNum(yGroup, 1); }
  if (!even) { yPixel = invertNum(yPixel, 8); }

  /*
  // Shit used for debug, uncomment if needed lol
  Serial.print("Module found ");
  Serial.print(disp.gridX);
  Serial.print(",");
  Serial.print(disp.gridY);
  Serial.print("; Xg: ");
  Serial.print(xGroup);
  Serial.print("; Xp: ");
  Serial.print(xPixel);
  Serial.print(" Yg: ");
  Serial.print(yGroup);
  Serial.print("; Yp: ");
  Serial.print(yPixel);
  Serial.print("; state ");
  Serial.println(state);*/

  // Step 4, set the FP2800 chips
  digitalWrite(PIN_U1_A0, xPixel & 0x01);
  digitalWrite(PIN_U1_A1, xPixel & 0x02);
  digitalWrite(PIN_U1_A2, xPixel & 0x04);
  digitalWrite(PIN_U1_B0, xGroup & 0x01);
  digitalWrite(PIN_U1_B1, xGroup & 0x02);   
  digitalWrite(PIN_U2_A0, yPixel & 0x01);
  digitalWrite(PIN_U2_A1, yPixel & 0x02);
  digitalWrite(PIN_U2_A2, yPixel & 0x04);
  digitalWrite(PIN_U2_B1, yGroup & 0x01);

  // Step 5, set the state. 
  // If this is an even module, the dot colors are reversed
  if (even) { state = !state; }
  if (state == true)
  {
    digitalWrite(PIN_U2_B0, LOW);
    digitalWrite(PIN_U1_DATA, HIGH);
  } else {
    digitalWrite(PIN_U2_B0, HIGH);
    digitalWrite(PIN_U1_DATA, LOW);
  }

  // Step 6, enable pulse!!
  digitalWrite(disp.PIN_ENABLE, HIGH);
  delayMicroseconds(250);
  digitalWrite(disp.PIN_ENABLE, LOW);
}

void FP317_driver::clearDisplay()
{
  for (int x = 0; x <=width; x++)
  {
    for (int y = 0; y <=height; y++)
    {
      setDot(x, y, false);
    }
  }    
}

int FP317_driver::invertNum(int num, int range)
{
  return range - num;
}

int FP317_driver::getDispCnt()
{
  return sizeof(displays) / sizeof(displays[0]);
}

int16_t FP317_driver::getWidth()
{
  return width;
}
int16_t FP317_driver::getHeight()
{
  return height;
}
