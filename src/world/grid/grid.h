#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>

typedef struct
{
  int              cell_size;
  SDL_Point       cell_count;
  SDL_FPoint          offset;
  SDL_FRect       outer_rect;
  SDL_FRect       inner_rect;
  SDL_FPoint inner_rect_xtyt;
} Grid;

void GRID_populate(Grid* grid, SDL_Rect* window_dim, int cs, int ccc, int rcc);
void GRID_handle_window_resize(Grid* grid, SDL_Rect* window_dim);
