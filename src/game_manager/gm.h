#pragma once

#include <SDL2/SDL_keycode.h>
#include <stdbool.h>

#include "../window_manager/wm.h"
#include "states.h"

#define GAME_SAVE_FILE_PATH "./nake.hex"

typedef struct
{
  Window*            window;
  SDL_Keycode   current_key;
  STTentities      entities;
  bool              running;
  bool            interrupt;
  float event_poll_interval;
  float     update_interval;
} Game;

int   GAME_load(STTiconf* conf);
Game* GAME_create(const char* title, STTiconf* conf);
void  GAME_run(Game* game);
void  GAME_destroy(Game** game);
