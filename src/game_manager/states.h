#pragma once

#include <SDL2/SDL_keycode.h>
#include <stdbool.h>

#include "../hud/hud.h"
#include "../apple/apple.h"
#include "../grid/grid.h"
#include "../nake/nake.h"

typedef struct
{
  int    grid_cell_size;
  int grid_cell_count_x;
  int grid_cell_count_y;
  int   update_interval;
  int      p_high_score;
} STTiconf;

typedef struct
{
  Grid*  grid;
  Nake*  nake;
  Apple apple;
  HUD*    hud;
} STTentities;
