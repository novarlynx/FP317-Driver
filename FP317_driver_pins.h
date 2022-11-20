/*
 * File: FP317_driver_pins.h
 * Configuration settings for the FP317_driver class
 * Contains pin assignments and display configuration 
 * 
 * Created by Andrew (Novar Lynx) (C) 2022
 * License is LGPL 2.1 https://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html
 */

//===============================================================
// UNCOMMENT THE LINE FOR THE MCU YOU'RE USING BELOW!
#define MCU_TYPE_ESP32_Mini_1
//#define MCU_TYPE_ARDUINO_UNO // not implemented yet
//===============================================================

/*
Each section below contains pin assignments for each module.
IMPORTANT: it also contains a configuration table which is used to set module parameters.
IMPORTANT: Enabled displays MUST form a complete rectangle or you WILL see errors!

Table row elements:
{ enabled(true/false), GridX, GridY, PIN_U1_ENABLE, PIN_U2_ENABLE }
If enabled is set to false, the module will be skipped by the FP317 driver class's auto configuration.
ENABLE pins refer to the driver's two enable pins which are unique for each module.

Module GridX and GridY diagram:
-------------------------------------
| driver board space                |
------------------------------------- (row 1)
| X=1    | X=2    | X=3    | X=4    |
| Y=1    | Y=1    | Y=1    | Y=1    |
------------------------------------- (row 15)
| X=1    | X=2    | X=3    | X=4    |
| Y=2    | Y=2    | Y=2    | Y=2    |
------------------------------------- (row 28)
| driver board space                |
------------------------------------- (row 29)
| X=1    | X=2    | X=3    | X=4    |
| Y=3    | Y=3    | Y=3    | Y=3    |
------------------------------------- (row 43)
| X=1    | X=2    | X=3    | X=4    |
| Y=4    | Y=4    | Y=4    | Y=4    |
------------------------------------- (row 56)
| driver board space                |
-------------------------------------
                                        .... etc
 */   
// Struct to hold data on FP317 modules, for the program
// DO NOT MESS WITH THIS
typedef struct {
  bool enabled;
  byte gridX; // 1 to 4, X location in the display grid
  byte gridY; // 1 to 2, Y location in the display grid
  byte PIN_U1_ENABLE; // IO pin of U1 enable
  byte PIN_U2_ENABLE; // IO pin of U2 enable
} FP317_module;

//===============================================================
// MCU: Espressif ESP32 Mini 1 DevBoard (Max 4 modules, 56 x 28)
//===============================================================
 #ifdef MCU_TYPE_ESP32_Mini_1
  // FP2800A driver pin assignments
  const int8_t PIN_U1_A0 = 14;
  const int8_t PIN_U1_A1 = 32;
  const int8_t PIN_U1_A2 = 18; 
  const int8_t PIN_U1_B0 = 27;
  const int8_t PIN_U1_B1 = 26;
  const int8_t PIN_U1_DATA = 33;
  const int8_t PIN_U2_A0 = 10;
  const int8_t PIN_U2_A1 = 5;
  const int8_t PIN_U2_A2 = 9;
  const int8_t PIN_U2_B0 = 25;
  const int8_t PIN_U2_B1 = 4;
  
  // Display module configuration table
  FP317_module displays[8] = {
  {  true, 1, 1, 21, 19}, // Upper left module
  { false, 2, 1, 00, 00},
  {  true, 1, 2, 22, 23}, // Lower left module
  { false, 2, 2, 00, 00},
  };
 #endif



/* More on pin assignments, lots of technobabble here

Each display module has two FP2800A driver chips, labeled U1 and U2. 
U1 selects the vertical column on the module's matrix of dots.
U2 selects the horizontal row on the module's matrix of dots.
The display module is arranged in a 2x4 grid of eight quadrants, with each quadrant having a dimension of 7x7 dots.
This can further be broken down into row and column groups, so imagine 7 rows or columms within each module forming a matrix.

 Each FP2800A driver chip has the following i/o pins that must be set for a display change operation:
A0, A1, and A2 select the individual row or column within a quadrant.
B0, B1 selects the row or quadrant group.

To set a dot, the A and B pins on both U1 and U2 have to be set accordingly.
U1 A0, A1, A2 select one of 7 columns within a column group.
U1 B0, B1 select one of four column groups.
U2 A0, A1, A2 select one of 7 rows within a row group.
U2 B0, B1 select one of two row groups.

U1 and U2 also have the DATA pin, which is used to set which way the dot is flipped. On some modules, 1 = on, 0 = off, but on
other modules this is reversed as the dots were installed backwards so the module can be installed upside down against another module.

Finally, U1 and U2 have ENABLE pins, which tell the chips to actually flip the dot.

With the way the 317 module is designed, ALL FP2800A chips in the entire grid of modules share the SAME selector and data pins, but
each module has its own ENABLE pins, two per module. This means a grid of 8 requires 16 enable pins. 
 */
