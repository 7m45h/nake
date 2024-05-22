#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>

#include "inc/grid.h"

static void grid_set_dimensions(Grid* grid, int ww, int wh)
{
  int margin_size        = grid->margin_cell_count * grid->cell_size;
  int margin_size_double = margin_size * 2;

  ww -= margin_size_double;
  wh -= margin_size_double;

  int grid_col_count = ww / grid->cell_size;
  int grid_row_count = wh / grid->cell_size;

  grid->outer_rect.w = grid->cell_size * grid_col_count;
  grid->outer_rect.h = grid->cell_size * grid_row_count;
  grid->outer_rect.x = margin_size + (ww - grid->outer_rect.w) * 0.5;
  grid->outer_rect.y = margin_size + (wh - grid->outer_rect.h) * 0.5;

  grid->inner_rect.x = grid->outer_rect.x + grid->cell_size;
  grid->inner_rect.y = grid->outer_rect.y + grid->cell_size;
  grid->inner_rect.w = grid->outer_rect.w - (grid->cell_size * 2);
  grid->inner_rect.h = grid->outer_rect.h - (grid->cell_size * 2);
}

void GRID_form(Grid* grid, int ww, int wh, int cell_size, int margin_cc)
{
  grid->cell_size         = cell_size;
  grid->margin_cell_count = margin_cc;
  grid_set_dimensions(grid, ww, wh);
}

void GRID_handle_world_resize(Grid* grid, int ww, int wh)
{
  grid_set_dimensions(grid, ww, wh);
}

void GRID_render(Grid* grid, SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRectF(renderer, &grid->outer_rect);
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRectF(renderer, &grid->inner_rect);
}
