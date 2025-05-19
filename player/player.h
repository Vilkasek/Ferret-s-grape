#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272
#define GRAVITY 600.0f
#define JUMP_FORCE 350.0f
#define PLAYER_SPEED 200.0f

typedef struct {
  Vector2 position;
  Vector2 velocity;
  float width;
  float height;
  bool isJumping;
  Texture2D texture;
} Player;

void player_init(Player *player);
void player_update(Player *player, float deltaTime, bool moveLeft,
                   bool moveRight, bool jumpPressed);
void player_draw(Player *player);
void player_unload(Player *player);

#endif
