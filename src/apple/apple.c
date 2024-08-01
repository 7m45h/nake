#include <stdlib.h>

#include "apple.h"

void APPLE_init(Apple* apple, Grid* grid)
{
  apple->w = grid->cell_size;
  apple->h = grid->cell_size;
  APPLE_set_rand_position(apple, grid);
}

void APPLE_counter_offset(Apple* apple, SDL_FPoint* offset)
{
  apple->x += offset->x;
  apple->y += offset->y;
}

void APPLE_set_rand_position(Apple* apple, Grid* grid)
{
  apple->x = rand() % grid->cell_count.x * grid->cell_size + grid->inner_rect.x;
  apple->y = rand() % grid->cell_count.y * grid->cell_size + grid->inner_rect.y;
}
