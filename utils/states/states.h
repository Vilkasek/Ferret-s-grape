#pragma once

enum class GameState { MAIN_MENU, GAME, GAME_OVER };

class States {
public:
  static States &get_instance();

  GameState get_state() const;
  void set_state(GameState newState);

  States();

private:
  GameState currentState;
};
