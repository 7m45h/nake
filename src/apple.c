#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <stdlib.h>

#include "inc/apple.h"

void APPLE_init(Apple* apple, Grid* grid)
{
  apple->w = grid->cell_size;
  apple->h = grid->cell_size;
  APPLE_set_random_position(apple, grid);
}

void APPLE_set_random_position(Apple* apple, Grid* grid)
{
  apple->x = ((rand() % grid->col_count) * grid->cell_size) + grid->inner_rect.x;
  apple->y = ((rand() % grid->row_count) * grid->cell_size) + grid->inner_rect.y;
}

void APPLE_render(Apple* apple, SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRectF(renderer, apple);
}
