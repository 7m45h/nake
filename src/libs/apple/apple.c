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
  apple->x = (rand() % grid->cell_count.y) * grid->cell_size + grid->inner_rect.x;
  apple->y = (rand() % grid->cell_count.x) * grid->cell_size + grid->inner_rect.y;
}

void APPLE_handle_grid_resize(Apple* apple, Grid* grid)
{
  apple->x += grid->offset.x;
  apple->y += grid->offset.y;
}
