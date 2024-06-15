#include <SDL2/SDL.h>
#include <stdlib.h>

#include "apple.h"

void APPLE_init(Apple* apple, Grid* grid)
{
  apple->w = grid->cell_size;
  apple->h = grid->cell_size;
  APPLE_set_random_position(apple, grid);
}

void APPLE_set_random_position(Apple* apple, Grid* grid)
{
  apple->x = (rand() % grid->col_count) * grid->cell_size + grid->inner_rect.x;
  apple->y = (rand() % grid->row_count) * grid->cell_size + grid->inner_rect.y;
}
