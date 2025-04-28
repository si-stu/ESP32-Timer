// modeController.cpp

#include "modeController.h"

ModeController::ModeController() {
    // Constructor implementation
    mode = Mode::INIT; // Initialize the mode to INIT
}

ModeController::~ModeController() {
    // Destructor implementation
}

Mode ModeController::getMode() const {
    return mode;
}

bool ModeController::setMode(Mode newMode) {
    
    bool allowTransition = false;
    // Start method implementation
    switch(mode) {
        case Mode::INIT:
            // Initialization logic
            if(newMode == Mode::STANDBY) {
                allowTransition = true;
            }
            break;
        case Mode::STANDBY:
            // Standby logic
            if(newMode == Mode::TIMER) {
                allowTransition = true;
            }
            break;
        case Mode::TIMER:
            // Timer logic
            if(newMode == Mode::STANDBY) {
                allowTransition = true;
            }
            break;
        default:
            return false; // Invalid mode
    }
    if(allowTransition) {
        mode = newMode; // Update the mode if transition is allowed
    }

    return allowTransition;
}

