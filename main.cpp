#define __GLIBC_USE(X) 0

#include <pspctrl.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspkernel.h>

#include <raylib.h>

#include "utils/states/states.h"

PSP_MODULE_INFO("Ferret\'s Grape", 0, 0, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

States &states = States::getInstance();

void update() {
  switch (states.get_state()) {
  case States::State::MAIN_MENU:
    break;
  case States::State::GAME:
    break;
  case States::State::GAME_OVER:
    break;
  }
}
void render() {
  BeginDrawing();

  switch (states.get_state()) {
  case States::State::MAIN_MENU:
    ClearBackground(RAYWHITE);
    DrawText("Hello, World!", 140, 120, 20, BLACK);
    break;
  case States::State::GAME:
    ClearBackground(LIGHTGRAY);
    DrawText("Hello, World!", 140, 120, 20, BLACK);
    break;
  case States::State::GAME_OVER:
    ClearBackground(DARKGREEN);
    DrawText("Hello, World!", 140, 120, 20, BLACK);
    break;
  }

  EndDrawing();
}

int main() {
  InitWindow(480, 272, "Ferret\'s Grape");

  while (!WindowShouldClose()) {
    update();
    render();
  }

  CloseWindow();
  return 0;
}
