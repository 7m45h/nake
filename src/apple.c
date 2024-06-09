#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include "inc/apple.h"
#include "inc/world.h"

static SDL_FRect apple;

void APPLE_init(void)
{
  apple.w = world.grid.cell_size;
  apple.h = world.grid.cell_size;
  APPLE_set_random_position();
}

void APPLE_set_random_position(void)
{
  apple.x = ((rand() % world.grid.col_count) * world.grid.cell_size) + world.grid.inner_rect.x;
  apple.y = ((rand() % world.grid.row_count) * world.grid.cell_size) + world.grid.inner_rect.y;
}

SDL_FRect* APPLE_get_position(void)
{
  return &apple;
}

void APPLE_render(void)
{
  SDL_SetRenderDrawColor(world.renderer, COLOR_FG, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRectF(world.renderer, &apple);
}
