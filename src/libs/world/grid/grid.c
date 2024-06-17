#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>

#include "../../../logger.h"
#include "grid.h"

void GRID_populate(Grid* grid, int ww, int wh, int cell_size, int mx, int my)
{
  grid->cell_size = cell_size;
  grid->margin.x  = mx * cell_size;
  grid->margin.y  = my * cell_size;

  ww -= grid->margin.x * 2;
  wh -= grid->margin.y * 2;

  grid->cell_count.y = ww / cell_size;
  grid->cell_count.x = wh / cell_size;

  grid->outer_rect.w = cell_size * grid->cell_count.y;
  grid->outer_rect.h = cell_size * grid->cell_count.x;
  grid->outer_rect.x = grid->margin.x + (ww - grid->outer_rect.w) * 0.5;
  grid->outer_rect.y = grid->margin.y + (wh - grid->outer_rect.h) * 0.5;

  grid->inner_rect.x = grid->outer_rect.x + cell_size;
  grid->inner_rect.y = grid->outer_rect.y + cell_size;

  cell_size *= 2;
  grid->inner_rect.w = grid->outer_rect.w - cell_size;
  grid->inner_rect.h = grid->outer_rect.h - cell_size;

  grid->cell_count.y -= 2;
  grid->cell_count.x -= 2;

  grid->inner_rect_xtyt.x = grid->inner_rect.x + grid->inner_rect.w;
  grid->inner_rect_xtyt.y = grid->inner_rect.y + grid->inner_rect.h;

  LOGG("grid populated!");
}

void GRID_handle_window_resize(Grid* grid, SDL_Rect* window_dim)
{
  SDL_FPoint new_grid_position;

  new_grid_position.x = (window_dim->w - grid->outer_rect.w) * 0.5;
  new_grid_position.y = (window_dim->h - grid->outer_rect.h) * 0.5;

  grid->offset.x = new_grid_position.x - grid->outer_rect.x;
  grid->offset.y = new_grid_position.y - grid->outer_rect.y;

  grid->outer_rect.x = new_grid_position.x;
  grid->outer_rect.y = new_grid_position.y;

  grid->inner_rect.x      = grid->outer_rect.x + grid->cell_size;
  grid->inner_rect.y      = grid->outer_rect.y + grid->cell_size;
  grid->inner_rect_xtyt.x = grid->inner_rect.x + grid->inner_rect.w;
  grid->inner_rect_xtyt.y = grid->inner_rect.y + grid->inner_rect.h;

  grid->margin.x = grid->outer_rect.x;
  grid->margin.y = grid->outer_rect.y;
}
