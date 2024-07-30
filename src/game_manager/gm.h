#pragma once

#include <stdbool.h>

#include "../window_manager/wm.h"
#include "states.h"

typedef struct
{
  Window*            window;
  STTevents          events;
  STTentities      entities;
  bool              running;
  float event_poll_interval;
  float     update_interval;
} Game;

Game* GAME_create(const char* title, int g_cs, int g_ccx, int g_ccy, int update_interval);
void  GAME_run(Game* game);
void  GAME_destroy(Game** game);
