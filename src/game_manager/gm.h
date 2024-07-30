#pragma once

#include <stdbool.h>

#include "../window_manager/wm.h"

typedef struct
{
  Window* window;
  bool   running;
} Game;

Game* GAME_create(const char* title);
void  GAME_destroy(Game** game);
