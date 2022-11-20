/*
 * File: FP317_driver_pins.h
 * Configuration settings for the FP317_driver class
 * Contains pin assignments and display configuration 
 * 
 * Created by Andrew (Novar Lynx) (C) 2022
 */

// Set this define for the MCU you're using to set pin assignments and display range limits.
#define MCU_TYPE_ESP32_Mini_1

// Each ifdef below contains an array to configure the modules, enable and disable as necessary
// for the displays you have connected to your MCU.

// Struct to hold data on FP317 modules, for the program
typedef struct {
  bool enabled;
  byte gridX; // 1 to 4, X location in the display grid
  byte gridY; // 1 to 2, Y location in the display grid
  byte PIN_U1_ENABLE; // IO pin of U1 enable
  byte PIN_U2_ENABLE; // IO pin of U2 enable
} FP317_module;

// ESP32-DevKit-Mini-1 can only support four modules, for a maximum size of 56x28
 #ifdef MCU_TYPE_ESP32_Mini_1
  const int8_t PIN_U1_A0 = 14;
  const int8_t PIN_U1_A1 = 32;
  const int8_t PIN_U1_A2 = 18; 
  const int8_t PIN_U1_B0 = 27;
  const int8_t PIN_U1_B1 = 26;
  const int8_t PIN_U1_DATA = 33;
  const int8_t PIN_U2_A0 = 10;
  const int8_t PIN_U2_A1 = 5;
  const int8_t PIN_U2_A2 = 9;
  const int8_t PIN_U2_B0 = 25; // also U2_DATA
  const int8_t PIN_U2_B1 = 4;
  FP317_module displays[8] = {
// X and Y below is gridX and gridY
// Maximum of four modules with this MCU, 56x28
// enable? X  Y  pin #s
  {  true, 1, 1, 21, 19}, // Upper left module
  { false, 2, 1, 00, 00},
  {  true, 1, 2, 22, 23}, // Lower left module
  { false, 2, 2, 00, 00},
  };
 #endif
