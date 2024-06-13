#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>

typedef struct
{
  int        cell_size;
  int         margin_x;
  int         margin_y;
  int        col_count;
  int        row_count;
  SDL_FRect outer_rect;
  SDL_FRect inner_rect;
} Grid;

void GRID_populate(Grid* grid, int ww, int wh, int cell_size, int mx, int my);
