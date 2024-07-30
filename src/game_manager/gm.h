#pragma once

#include <stdbool.h>

#include "../window_manager/wm.h"
#include "states.h"

typedef struct
{
  Window*  window;
  STTevents event;
  bool    running;
} Game;

Game* GAME_create(const char* title);
void  GAME_run(Game* game);
void  GAME_destroy(Game** game);
