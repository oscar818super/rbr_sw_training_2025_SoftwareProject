#include <Arduino.h>
#include "PinDefinitions.h"
#include "VCUStates.h"


void setup() {
  // put your setup code here, to run once:
  initializePins();
  initStateMachine();
}

void loop() {
  // put your main code here, to run repeatedly:
  updateStateMachine();
}

