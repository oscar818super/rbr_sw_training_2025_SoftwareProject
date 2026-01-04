#ifndef VCU_STATES_H
#define VCU_STATES_H

#include <Arduino.h>

enum class VCUState {
    INIT = 0,
    STARTIN = 1,
    BUZZIN = 2,
    DRIVE = 3
};

// Expose the current state so main.cpp (and later CAN) can see it
extern VCUState currentState;

// Function declarations
void initStateMachine();
void updateStateMachine();

#endif