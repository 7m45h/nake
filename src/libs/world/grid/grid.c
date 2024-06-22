#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>

#include "../../../logger.h"
#include "grid.h"

void GRID_populate(Grid* grid, SDL_Rect* window_dim, int cs, int ccc, int rcc)
{
  grid->cell_size    = cs;
  grid->cell_count.x = ccc - 2;
  grid->cell_count.y = rcc - 2;

  grid->offset.x = 0;
  grid->offset.y = 0;

  grid->outer_rect.w = grid->cell_size * ccc;
  grid->outer_rect.h = grid->cell_size * rcc;
  grid->outer_rect.x = (window_dim->w - grid->outer_rect.w) * 0.5f;
  grid->outer_rect.y = (window_dim->h - grid->outer_rect.h) * 0.5f;

  grid->inner_rect.x = grid->outer_rect.x + grid->cell_size;
  grid->inner_rect.y = grid->outer_rect.y + grid->cell_size;
  cs *= 2;
  grid->inner_rect.w = grid->outer_rect.w - cs;
  grid->inner_rect.h = grid->outer_rect.h - cs;

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
}
