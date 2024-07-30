#pragma once

#include <stdbool.h>

#include "../window_manager/wm.h"
#include "states.h"

typedef struct
{
  Window*       window;
  STTevents     events;
  STTentities entities;
  bool         running;
} Game;

Game* GAME_create(const char* title, int g_cs, int g_ccx, int g_ccy);
void  GAME_run(Game* game);
void  GAME_destroy(Game** game);
