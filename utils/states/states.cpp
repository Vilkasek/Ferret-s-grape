#include "states.h"

static States singletonInstance;

States& States::get_instance() {
    return singletonInstance;
}

States::States() {
    currentState = GameState::MAIN_MENU;
}

GameState States::get_state() const {
    return currentState;
}

void States::set_state(GameState newState) {
    currentState = newState;
}

