#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>

typedef struct
{
  int               cell_size;
  SDL_Point        cell_count;
  SDL_FRect        outer_rect;
  SDL_FRect        inner_rect;
  SDL_FPoint           offset;
  SDL_FPoint outer_rect_bound;
  SDL_FPoint inner_rect_bound;
} Grid;

Grid* GRID_create(SDL_Point* window_dim, int cs, int ccx, int ccy);
void  GRID_align_center(Grid* grid, SDL_Point* window_dim);
void  GRID_destroy(Grid** grid);
