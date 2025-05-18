#pragma once

class States {
public:
  enum class State { MAIN_MENU, GAME, GAME_OVER };

  static States &get_instance();

  State get_state() const;
  void set_state(State newState);

  States(const States &) = delete;
  States &operator=(const States &) = delete;

private:
  States();
  State currentState = State::MAIN_MENU;
};
