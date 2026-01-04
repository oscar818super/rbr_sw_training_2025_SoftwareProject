#include <Arduino.h>
#include "PinDefinitions.h"
#include "VCUStates.h"

VCUState currentState = VCUState::INIT;

// Define Constants
const int BRAKE_THRESHOLD = 200;    // Subject to Change
const unsigned long STARTIN_DURATION_MS = 2000;
const unsigned long BUZZIN_DURATION_MS = 2000;

// Define Timers
static unsigned long timerState = 0;

// Public Functions
void initStateMachine() {
    currentState = VCUState::INIT;
    digitalWrite(PIN_DRIVE_MODE_LED, LOW);
    digitalWrite(PIN_BUZZER, LOW);
    digitalWrite(PIN_BRAKE_LIGHT, LOW);
}

void updateStateMachine() {

    // Read inputs
    int startButtonState = digitalRead(PIN_START_BUTTON);
    int brakePedalValue = analogRead(PIN_BRAKES);

    if (brakePedalValue > BRAKE_THRESHOLD) {
        digitalWrite(PIN_BRAKE_LIGHT, HIGH);
    } 
    
    else {
        digitalWrite(PIN_BRAKE_LIGHT, LOW);
    }

    switch (currentState) {

        case VCUState::INIT:
            digitalWrite(PIN_BRAKES, LOW);

            if (startButtonState == HIGH && brakePedalValue > BRAKE_THRESHOLD) {
                currentState = VCUState::STARTIN;
                timerState = millis();
            }

            break;

        case VCUState::STARTIN:
            digitalWrite(PIN_BRAKES, LOW);

            if (brakePedalValue <= BRAKE_THRESHOLD || startButtonState == LOW) {
                currentState = VCUState::INIT;
            }

            else if  (millis() - timerState >= STARTIN_DURATION_MS) {
                currentState = VCUState::BUZZIN;
                timerState = millis();
            }

            break;

        
        case VCUState::BUZZIN:

            if (millis() - timerState >= BUZZIN_DURATION_MS) {
                currentState = VCUState::DRIVE;
                digitalWrite(PIN_BUZZER, LOW);
            }

            else {
                digitalWrite(PIN_BUZZER, HIGH);
            }

            break;

        case VCUState::DRIVE:


    }
}