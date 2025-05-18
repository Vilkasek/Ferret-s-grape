class States {
public:
  static States &getInstance() {
    static States instance;
    return instance;
  }

  enum class State {
    MAIN_MENU,
    GAME,
    GAME_OVER,
  };

  State get_state() { return currentState; }

  void set_state(State newState) { currentState = newState; }

  States(const States &) = delete;
  States &operator=(const States &) = delete;

private:
  States() {}
  State currentState = State::GAME;
};
