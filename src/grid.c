#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>

#include "inc/grid.h"
#include "inc/world.h"

static void grid_set_dimensions(Grid* grid, int ww, int wh)
{
  int margin_x_size        = grid->margin_x * grid->cell_size;
  int margin_y_size        = grid->margin_y * grid->cell_size;
  int margin_x_size_double = margin_x_size * 2;
  int margin_y_size_double = margin_y_size * 2;

  ww -= margin_x_size_double;
  wh -= margin_y_size_double;

  grid->col_count = ww / grid->cell_size;
  grid->row_count = wh / grid->cell_size;

  grid->outer_rect.w = grid->cell_size * grid->col_count;
  grid->outer_rect.h = grid->cell_size * grid->row_count;
  grid->outer_rect.x = margin_x_size + (ww - grid->outer_rect.w) * 0.5;
  grid->outer_rect.y = margin_y_size + (wh - grid->outer_rect.h) * 0.5;

  grid->inner_rect.x = grid->outer_rect.x + grid->cell_size;
  grid->inner_rect.y = grid->outer_rect.y + grid->cell_size;
  grid->inner_rect.w = grid->outer_rect.w - (grid->cell_size * 2);
  grid->inner_rect.h = grid->outer_rect.h - (grid->cell_size * 2);

  grid->col_count -= 2; // remove border cells
  grid->row_count -= 2; // remove border cells
}

void GRID_form(Grid* grid, int ww, int wh, int cell_size, int mx, int my)
{
  grid->cell_size = cell_size;
  grid->margin_x  = mx;
  grid->margin_y  = my;
  grid_set_dimensions(grid, ww, wh);
}

void GRID_handle_world_resize(Grid* grid, int ww, int wh)
{
  grid_set_dimensions(grid, ww, wh);
}

void GRID_render(Grid* grid, SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, COLOR_FG, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRectF(renderer, &grid->outer_rect);
  SDL_SetRenderDrawColor(renderer, COLOR_BG, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRectF(renderer, &grid->inner_rect);

  // draw grid lines
  // SDL_SetRenderDrawColor(renderer, COLOR_FG, SDL_ALPHA_OPAQUE);
  // float border_x = grid->inner_rect.x + grid->inner_rect.w;
  // float border_y = grid->inner_rect.y + grid->inner_rect.h;
  // float start_x  = 0;
  // float start_y  = 0;
  // for (int x = 0; x < grid->inner_rect.w; x += grid->cell_size)
  // {
  //   start_x = grid->inner_rect.x +x;
  //   SDL_RenderDrawLineF(renderer, start_x, grid->inner_rect.y, start_x, border_y);
  // }
  // for (int y = 0; y < grid->inner_rect.h; y += grid->cell_size)
  // {
  //   start_y = grid->inner_rect.y + y;
  //   SDL_RenderDrawLineF(renderer, grid->inner_rect.x, start_y, border_x, start_y);
  // }
}
