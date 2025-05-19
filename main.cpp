#define __GLIBC_USE(X) 0

#include "player/player.h"

#include <pspctrl.h>
#include <pspdisplay.h>
#include <pspkernel.h>
#include <raylib.h>

PSP_MODULE_INFO("rayLib", 0, 1, 0);
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

int main(void) {
  setup_callbacks();

  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PSP Platformówka 2D");

  sceCtrlSetSamplingCycle(0);
  sceCtrlSetSamplingMode(PSP_CTRL_MODE_DIGITAL);

  SceCtrlData pad, prevPad;
  sceCtrlReadBufferPositive(&prevPad, 1);

  Player player;
  player_init(&player);

  while (!WindowShouldClose()) {
    float deltaTime = GetFrameTime();

    sceCtrlReadBufferPositive(&pad, 1);

    bool left = pad.Buttons & PSP_CTRL_LEFT;
    bool right = pad.Buttons & PSP_CTRL_RIGHT;
    bool jumpPressed =
        (pad.Buttons & PSP_CTRL_CROSS) && !(prevPad.Buttons & PSP_CTRL_CROSS);

    if (pad.Buttons & PSP_CTRL_HOME) {
      break;
    }

    player_update(&player, deltaTime, left, right, jumpPressed);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    player_draw(&player);
    EndDrawing();

    prevPad = pad;
  }

  player_unload(&player);
  CloseWindow();
  sceKernelExitGame();
  return 0;
}
