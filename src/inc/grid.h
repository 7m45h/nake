#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

typedef struct
{
  int         cell_size;
  int margin_cell_count;
  SDL_FRect  outer_rect;
  SDL_FRect  inner_rect;
} Grid;

void GRID_form(Grid* grid, int ww, int wh, int cell_size, int margin_cc);
void GRID_handle_world_resize(Grid* grid, int ww, int wh);
void GRID_render(Grid* grid, SDL_Renderer* renderer);
