#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>

typedef struct
{
  int              cell_size;
  SDL_FPoint          margin;
  SDL_FPoint          offset;
  SDL_Point       cell_count;
  SDL_FRect       outer_rect;
  SDL_FRect       inner_rect;
  SDL_FPoint inner_rect_xtyt;
} Grid;

void GRID_populate(Grid* grid, int ww, int wh, int cell_size, int mx, int my);
void GRID_handle_window_resize(Grid* grid, SDL_Rect* window_dim);
