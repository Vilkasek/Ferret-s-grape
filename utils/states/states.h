#pragma once

enum class State { MAIN_MENU, GAME, GAME_OVER };

class States {
public:
  static States &get_instance();

  State get_state() const;
  void set_state(State newState);

  States();

private:
  State currentState = State::MAIN_MENU;
};
