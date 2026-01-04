#ifndef PIN_DEFINITIONS_H
#define PIN_DEFINITIONS_H

#include <Arduino.h>

//  Pin definitions

//  MCP2515 CAN Crystal Frequency
#define CAN_CRYSTAL_FREQ    MCP_20MHZ

//  MCP2515 CAN Controller PINS
#define PIN_MONITOR_CAN_CS    10    // Pin PB2
#define PIN_BMS_CAN_CS    9   // Pin PB1
#define PIN_DEBUG_CAN_CS    8   // Pin PB0

//  Pedal Inputs PINS
#define PIN_APPS_5V    A0  // Pin PC0
#define PIN_APPS_3V3   A1  // Pin PC1
#define PIN_BRAKES     A3  // Pin PC3

//  Start Button Input PIN
#define PIN_START_BUTTON   A4   // Pin PC4

//  Output PINS
#define PIN_BRAKE_LIGHT    2   // Pin PD2
#define PIN_BUZZER  4   // Pin PD4
#define PIN_DRIVE_MODE_LED  3   // Pin PD3

//Function Declarations
void initializePins();

#endif