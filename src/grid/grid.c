#include <SDL2/SDL_rect.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../logger.h"
#include "grid.h"

Grid* GRID_create(SDL_Point* window_dim, int cs, int ccx, int ccy)
{
  Grid* grid = malloc(sizeof(Grid));
  if (grid == NULL)
  {
    LOGGERR("malloc", errno, strerror(errno));
    return NULL;
  }

  grid->cell_size    = cs;
  grid->cell_count.x = ccx;
  grid->cell_count.y = ccy;

  grid->outer_rect.w = (grid->cell_count.x + 2) * grid->cell_size;
  grid->outer_rect.h = (grid->cell_count.y + 2) * grid->cell_size;
  grid->outer_rect.x = (window_dim->x - grid->outer_rect.w) * 0.5;
  grid->outer_rect.y = (window_dim->y - grid->outer_rect.h) * 0.5;

  grid->inner_rect.x = grid->outer_rect.x + grid->cell_size;
  grid->inner_rect.y = grid->outer_rect.y + grid->cell_size;

  int cell_size_double = grid->cell_size * 2;
  grid->inner_rect.w = grid->outer_rect.w - cell_size_double;
  grid->inner_rect.h = grid->outer_rect.h - cell_size_double;

  grid->outer_rect_bound.x = grid->outer_rect.x + grid->outer_rect.w;
  grid->outer_rect_bound.y = grid->outer_rect.y + grid->outer_rect.h;
  grid->inner_rect_bound.x = grid->inner_rect.x + grid->inner_rect.w;
  grid->inner_rect_bound.y = grid->inner_rect.y + grid->inner_rect.h;

  return grid;
}

void  GRID_align_center(Grid* grid, SDL_Point* window_dim)
{
  float outer_rect_xp = grid->outer_rect.x;
  float outer_rect_yp = grid->outer_rect.y;

  grid->outer_rect.x = (window_dim->x - grid->outer_rect.w) * 0.5;
  grid->outer_rect.y = (window_dim->y - grid->outer_rect.h) * 0.5;

  grid->offset.x = grid->outer_rect.x - outer_rect_xp;
  grid->offset.y = grid->outer_rect.y - outer_rect_yp;

  grid->inner_rect.x += grid->offset.x;
  grid->inner_rect.y += grid->offset.y;

  grid->outer_rect_bound.x += grid->offset.x;
  grid->outer_rect_bound.y += grid->offset.y;
  grid->inner_rect_bound.x += grid->offset.x;
  grid->inner_rect_bound.y += grid->offset.y;
}

void  GRID_destroy(Grid** grid)
{
  if (grid != NULL && *grid != NULL)
  {
    free(*grid);
    *grid = NULL;
  }
}
