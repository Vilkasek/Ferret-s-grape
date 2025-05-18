#define __GLIBC_USE(X) 0

#include <pspctrl.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspkernel.h>

#include <raylib.h>

#include "utils/states/states.h"

PSP_MODULE_INFO("Ferret\'s Grape", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int exit_callback(int arg1, int arg2, void *common) {
  sceKernelExitGame();
  return 0;
}

int callback_thread(SceSize args, void *argp) {
  int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
  sceKernelRegisterExitCallback(cbid);
  sceKernelSleepThreadCB();
  return 0;
}

int setup_callbacks(void) {
  int thid = sceKernelCreateThread("update_thread", callback_thread, 0x11,
                                   0xFA0, 0, 0);
  if (thid >= 0) {
    sceKernelStartThread(thid, 0, 0);
  }
  return thid;
}

States statesInstance;

void update() {
  SceCtrlData pad;

  sceCtrlReadBufferPositive(&pad, 1);

  if (pad.Buttons & PSP_CTRL_HOME) {
    sceKernelExitGame();
  }

  switch (statesInstance.get_state()) {
  case State::MAIN_MENU:
    break;
  case State::GAME:
    break;
  case State::GAME_OVER:
    break;
  }
}

void render() {
  BeginDrawing();

  switch (statesInstance.get_state()) {
  case State::MAIN_MENU:
    ClearBackground(RAYWHITE);
    DrawText("Hello, World!", 140, 120, 20, BLACK);
    break;
  case State::GAME:
    ClearBackground(LIGHTGRAY);
    DrawText("Hello, World!", 140, 120, 20, BLACK);
    break;
  case State::GAME_OVER:
    ClearBackground(DARKGREEN);
    DrawText("Hello, World!", 140, 120, 20, BLACK);
    break;
  }

  EndDrawing();
}

int main() {
  setup_callbacks();

  InitWindow(480, 272, "Ferret\'s Grape");
  SetTargetFPS(60);

  statesInstance.set_state(State::GAME);

  while (!WindowShouldClose()) {
    update();
    render();
  }

  CloseWindow();
  return 0;
}
