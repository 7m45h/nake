#include <SDL2/SDL.h>

#include "../../../logger.h"
#include "grid.h"

void GRID_populate(Grid* grid, int ww, int wh, int cell_size, int mx, int my)
{
  grid->cell_size = cell_size;
  grid->margin_x  = mx;
  grid->margin_y  = my;

  int margin_x_size = cell_size * mx;
  int margin_y_size = cell_size * my;

  ww -= margin_x_size * 2;
  wh -= margin_y_size * 2;

  grid->col_count = ww / cell_size;
  grid->row_count = wh / cell_size;

  grid->outer_rect.w = cell_size * grid->col_count;
  grid->outer_rect.h = cell_size * grid->row_count;
  grid->outer_rect.x = margin_x_size + (ww - grid->outer_rect.w) * 0.5;
  grid->outer_rect.y = margin_y_size + (wh - grid->outer_rect.h) * 0.5;

  grid->inner_rect.x = grid->outer_rect.x + cell_size;
  grid->inner_rect.y = grid->outer_rect.y + cell_size;

  cell_size *= 2;
  grid->inner_rect.w = grid->outer_rect.w - cell_size;
  grid->inner_rect.h = grid->outer_rect.h - cell_size;

  grid->col_count -= 2;
  grid->row_count -= 2;

  grid->inner_rect_xtyt.x = grid->inner_rect.x + grid->inner_rect.w;
  grid->inner_rect_xtyt.y = grid->inner_rect.y + grid->inner_rect.h;

  LOGG("grid populated!");
}
