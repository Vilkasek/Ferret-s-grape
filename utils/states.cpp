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

  States(const States &) = delete;
  States &operator=(const States &) = delete;

private:
  States() {}
};
