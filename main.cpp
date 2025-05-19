#define __GLIBC_USE(X) 0

#include "raylib.h"
#include <pspctrl.h>
#include <pspdisplay.h>
#include <pspkernel.h>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272
#define GRAVITY 600.0f
#define JUMP_FORCE 350.0f
#define PLAYER_SPEED 200.0f

PSP_MODULE_INFO("rayLib", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

typedef struct {
  Vector2 position;
  Vector2 velocity;
  float width;
  float height;
  bool isJumping;
  Texture2D texture;
} Player;

int main(void) {
  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PSP Platformówka 2D");

  sceCtrlSetSamplingCycle(0);
  sceCtrlSetSamplingMode(PSP_CTRL_MODE_DIGITAL);

  SceCtrlData pad;
  SceCtrlData prevPad;
  sceCtrlReadBufferPositive(&prevPad, 1);

  Player player = {.position = {SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 2.0f},
                   .velocity = {0.0f, 0.0f},
                   .width = 32.0f,
                   .height = 48.0f,
                   .isJumping = false,
                   .texture = {0}};

  player.texture = LoadTexture("assets/player.png");

  while (!WindowShouldClose()) {
    float deltaTime = GetFrameTime();

    sceCtrlReadBufferPositive(&pad, 1);
    bool crossPressed =
        (pad.Buttons & PSP_CTRL_CROSS) && !(prevPad.Buttons & PSP_CTRL_CROSS);

    if (pad.Buttons & PSP_CTRL_LEFT)
      player.velocity.x = -PLAYER_SPEED;
    else if (pad.Buttons & PSP_CTRL_RIGHT)
      player.velocity.x = PLAYER_SPEED;
    else
      player.velocity.x = 0.0f;

    if (crossPressed && !player.isJumping) {
      player.velocity.y = -JUMP_FORCE;
      player.isJumping = true;
    }

    player.velocity.y += GRAVITY * deltaTime;

    player.position.x += player.velocity.x * deltaTime;
    player.position.y += player.velocity.y * deltaTime;

    if (player.position.x < 0) {
      player.position.x = 0;
    }
    if (player.position.x > SCREEN_WIDTH - player.width) {
      player.position.x = SCREEN_WIDTH - player.width;
    }

    if (player.position.y > SCREEN_HEIGHT - player.height) {
      player.position.y = SCREEN_HEIGHT - player.height;
      player.velocity.y = 0;
      player.isJumping = false;
    }
    if (player.position.y < 0) {
      player.position.y = 0;
      player.velocity.y = 0;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawTexture(player.texture, (int)player.position.x, (int)player.position.y,
                WHITE);

    EndDrawing();

    prevPad = pad;
  }

  UnloadTexture(player.texture);
  CloseWindow();

  return 0;
}
