#include <Arduino.h>
#include "PinDefinitions.h"

void initializePins() {

  Serial.begin(9600);

  //  MCP2515 CAN Controller PINS
  pinMode(PIN_MONITOR_CAN_CS, INPUT);
  pinMode(PIN_BMS_CAN_CS, INPUT);
  pinMode(PIN_DEBUG_CAN_CS, INPUT);

  //  Pedal Inputs PINS
  pinMode(PIN_APPS_5V, INPUT);
  pinMode(PIN_APPS_3V3, INPUT);

  //  Start Button Input PIN
  pinMode(PIN_START_BUTTON, INPUT);

  //  Output PINS
  pinMode(PIN_BRAKE_LIGHT, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_DRIVE_MODE_LED, OUTPUT);
}