#pragma once

#include <SDL2/SDL_keycode.h>
#include <stdbool.h>

#include "../grid/grid.h"
#include "../nake/nake.h"

typedef struct
{
  bool          quit;
  bool window_resize;
  SDL_Keycode    key;
} STTevents;

typedef struct
{
  Grid* grid;
  Nake* nake;
} STTentities;
