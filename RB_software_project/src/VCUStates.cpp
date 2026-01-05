#include <Arduino.h>
#include "PinDefinitions.h"
#include "VCUStates.h"

VCUState currentState = VCUState::INIT;

// Define Constants
const int BRAKE_THRESHOLD = 200;    // Subject to Change
const unsigned long STARTIN_DURATION_MS = 2000;
const unsigned long BUZZIN_DURATION_MS = 2000;
const unsigned int APPS_FAULTY_DURATION_MS = 100;
const bool isFrontDirection = true;

// Define Timers
static unsigned long timerState = 0;
static unsigned long timerAPPSFault = 0;
static bool isAppsFaultActive = false;

//  Private Functions
int16_t calculateTorque(int throttleVal) {
    
    throttleVal = constrain(throttleVal, 0, 1023);
    long mappedVal = 0;
    if (isFrontDirection) {
        mappedVal = map(throttleVal, 0, 1023, 0, 32767);
    } else {

        mappedVal = map(throttleVal, 0, 1023, 0, -32768); 
    }
    
    return (int16_t)mappedVal;
}

//  Public Functions
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
    int apps5VValue = analogRead(PIN_APPS_5V);
    int apps3V3Value = analogRead(PIN_APPS_3V3);

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

            int apps3v3ValueScaled = apps3V3Value * 5 / 3.3;

            if (abs(apps5VValue - apps3v3ValueScaled) / apps5VValue > 0.1) {
                if (isAppsFaultActive && (millis() - timerAPPSFault >= APPS_FAULTY_DURATION_MS)) {
                    currentState = VCUState::INIT;
                    isAppsFaultActive = false;
                    break;
                } 
                
                else if (!isAppsFaultActive) {
                    isAppsFaultActive = true;
                    timerAPPSFault = millis();
                }
            }

            else {
                isAppsFaultActive = false;
            }

            int16_t torqueCommand = calculateTorque(apps5VValue);

            break;
            


    }

}