#include "states.h"

States::States() {}

States& States::get_instance() {
    static States instance;
    return instance;
}

States::State States::get_state() const {
    return currentState;
}

void States::set_state(State newState) {
    currentState = newState;
}
