#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>

#include "inc/nake.h"
#include "inc/world.h"

void NAKE_init(Nake* nake, Grid* grid)
{
  nake->rect.x = ((rand() % grid->col_count) * grid->cell_size) + grid->inner_rect.x;
  nake->rect.y = ((rand() % grid->row_count) * grid->cell_size) + grid->inner_rect.y;
  nake->rect.w = grid->cell_size;
  nake->rect.h = grid->cell_size;

  nake->direction = SDLK_LEFT;

  nake->score = 0;
}

void NAKE_update(Nake* nake, Grid* grid, SDL_Keycode crnt_key)
{
  switch (crnt_key)
  {
    case SDLK_UP:
    if (nake->direction != SDLK_DOWN) nake->direction = crnt_key;
    break;

    case SDLK_DOWN:
    if (nake->direction != SDLK_UP) nake->direction = crnt_key;
    break;

    case SDLK_LEFT:
    if (nake->direction != SDLK_RIGHT) nake->direction = crnt_key;
    break;

    case SDLK_RIGHT:
    if (nake->direction != SDLK_LEFT) nake->direction = crnt_key;
    break;
  }

  switch (nake->direction)
  {
    case SDLK_UP:
    nake->rect.y -= nake->rect.w;
    break;

    case SDLK_DOWN:
    nake->rect.y += nake->rect.w;
    break;

    case SDLK_LEFT:
    nake->rect.x -= nake->rect.w;
    break;

    case SDLK_RIGHT:
    nake->rect.x += nake->rect.w;
    break;
  }

  if (nake->rect.x < grid->inner_rect.x)
  {
    nake->rect.x = grid->inner_rect.w - grid->cell_size;
  }
  else if ((nake->rect.x + grid->cell_size) > (grid->inner_rect.x + grid->inner_rect.w))
  {
    nake->rect.x = grid->inner_rect.x;
  }

  if (nake->rect.y < grid->inner_rect.y)
  {
    nake->rect.y = grid->inner_rect.h - grid->cell_size;
  }
  else if ((nake->rect.y + grid->cell_size) > (grid->inner_rect.y + grid->inner_rect.h))
  {
    nake->rect.y = grid->inner_rect.y;
  }
}

void NAKE_render(Nake* nake, SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, COLOR_FG, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRectF(renderer, &nake->rect);
}
