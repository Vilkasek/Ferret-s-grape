#include "player.h"

void player_init(Player *player) {
  *player = (Player){.position = {SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 2.0f},
                     .velocity = {0.0f, 0.0f},
                     .width = 32.0f,
                     .height = 48.0f,
                     .isJumping = false,
                     .texture = {0},
                     .coyoteTime = 0.1f,
                     .coyoteTimer = 0.0f,
                     .jumpBufferTime = 0.1f,
                     .jumpBufferTimer = 0.0f};

  player->texture = LoadTexture("assets/player.png");
}

void player_update(Player *player, float deltaTime, bool left, bool right,
                   bool jumpPressed) {
  if (left)
    player->velocity.x = -PLAYER_SPEED;
  else if (right)
    player->velocity.x = PLAYER_SPEED;
  else
    player->velocity.x = 0.0f;

  if (jumpPressed)
    player->jumpBufferTimer = player->jumpBufferTime;
  else
    player->jumpBufferTimer -= deltaTime;

  player->velocity.y += GRAVITY * deltaTime;

  player->position.x += player->velocity.x * deltaTime;
  player->position.y += player->velocity.y * deltaTime;

  if (player->position.y >= SCREEN_HEIGHT - player->height) {
    player->position.y = SCREEN_HEIGHT - player->height;
    player->velocity.y = 0.0f;
    player->isJumping = false;
    player->coyoteTimer = player->coyoteTime;
  } else {
    player->isJumping = true;
    player->coyoteTimer -= deltaTime;
  }

  if (player->jumpBufferTimer > 0.0f && player->coyoteTimer > 0.0f) {
    player->velocity.y = -JUMP_FORCE;
    player->isJumping = true;
    player->coyoteTimer = 0.0f;
    player->jumpBufferTimer = 0.0f;
  }

  if (player->position.x < 0)
    player->position.x = 0;
  if (player->position.x > SCREEN_WIDTH - player->width)
    player->position.x = SCREEN_WIDTH - player->width;
  if (player->position.y < 0)
    player->position.y = 0;
}

void player_draw(Player *player) {
  DrawTexture(player->texture, (int)player->position.x, (int)player->position.y,
              WHITE);
}

void player_unload(Player *player) { UnloadTexture(player->texture); }
