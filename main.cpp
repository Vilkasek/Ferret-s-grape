#define __GLIBC_USE(X) 0

#include "player/player.h"

#include <pspctrl.h>
#include <pspdisplay.h>
#include <pspkernel.h>
#include <raylib.h>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272
#define GRAVITY 600.0f
#define JUMP_FORCE 350.0f
#define PLAYER_SPEED 200.0f

PSP_MODULE_INFO("rayLib", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int main(void) {
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
    bool jumpPressed =
        (pad.Buttons & PSP_CTRL_CROSS) && !(prevPad.Buttons & PSP_CTRL_CROSS);

    bool moveLeft = pad.Buttons & PSP_CTRL_LEFT;
    bool moveRight = pad.Buttons & PSP_CTRL_RIGHT;

    player_update(&player, deltaTime, moveLeft, moveRight, jumpPressed);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    player_draw(&player);
    EndDrawing();

    prevPad = pad;
  }

  player_unload(&player);
  CloseWindow();

  return 0;
}
