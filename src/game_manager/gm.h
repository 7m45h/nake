#pragma once

#include <stdbool.h>

#include "../window_manager/wm.h"
#include "states.h"

#define GAME_SAVE_FILE_PATH "./nake-save.txt"

typedef struct
{
  Window*            window;
  STTevents          events;
  STTentities      entities;
  bool              running;
  bool            interrupt;
  float event_poll_interval;
  float     update_interval;
} Game;

Game* GAME_create(const char* title, STTiconf* conf);
void  GAME_run(Game* game);
void  GAME_destroy(Game** game);
