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

  return grid;
}

void  GRID_align_center(Grid* grid, SDL_Point* window_dim)
{
  grid->outer_rect.x = (window_dim->x - grid->outer_rect.w) * 0.5;
  grid->outer_rect.y = (window_dim->y - grid->outer_rect.h) * 0.5;
  grid->inner_rect.x = (window_dim->x - grid->inner_rect.w) * 0.5;
  grid->inner_rect.y = (window_dim->y - grid->inner_rect.h) * 0.5;
}

void  GRID_destroy(Grid** grid)
{
  if (grid != NULL && *grid != NULL)
  {
    free(*grid);
    *grid = NULL;
  }
}
