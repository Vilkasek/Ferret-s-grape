#include "player.h"

void player_init(Player *player) {
  *player = (Player){.position = {SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 2.0f},
                     .velocity = {0.0f, 0.0f},
                     .width = 32.0f,
                     .height = 48.0f,
                     .isJumping = false,
                     .texture = LoadTexture("assets/player.png")};
}

void player_update(Player *player, float deltaTime, bool moveLeft,
                   bool moveRight, bool jumpPressed) {
  if (moveLeft)
    player->velocity.x = -PLAYER_SPEED;
  else if (moveRight)
    player->velocity.x = PLAYER_SPEED;
  else
    player->velocity.x = 0.0f;

  if (jumpPressed && !player->isJumping) {
    player->velocity.y = -JUMP_FORCE;
    player->isJumping = true;
  }

  player->velocity.y += GRAVITY * deltaTime;

  player->position.x += player->velocity.x * deltaTime;
  player->position.y += player->velocity.y * deltaTime;

  if (player->position.x < 0)
    player->position.x = 0;
  if (player->position.x > SCREEN_WIDTH - player->width)
    player->position.x = SCREEN_WIDTH - player->width;

  if (player->position.y > SCREEN_HEIGHT - player->height) {
    player->position.y = SCREEN_HEIGHT - player->height;
    player->velocity.y = 0;
    player->isJumping = false;
  }

  if (player->position.y < 0) {
    player->position.y = 0;
    player->velocity.y = 0;
  }
}

void player_draw(Player *player) {
  DrawTexture(player->texture, (int)player->position.x, (int)player->position.y,
              WHITE);
}

void player_unload(Player *player) { UnloadTexture(player->texture); }
