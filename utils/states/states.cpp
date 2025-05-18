#include "states.h"

static States singletonInstance;

States &States::get_instance() { return singletonInstance; }

States::States() { currentState = State::MAIN_MENU; }

State States::get_state() const { return currentState; }

void States::set_state(State newState) { currentState = newState; }
