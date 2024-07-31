#include <SDL2/SDL_keycode.h>
#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../logger.h"
#include "nake.h"

Nake* NAKE_create(Grid* grid)
{
  Nake* nake = malloc(sizeof(Nake));
  if (nake == NULL)
  {
    LOGGERR("malloc", errno, strerror(errno));
    return NULL;
  }

  nake->rect.x = roundf(grid->cell_count.x * 0.5) * grid->cell_size + grid->inner_rect.x;
  nake->rect.y = roundf(grid->cell_count.y * 0.5) * grid->cell_size + grid->inner_rect.y;
  nake->rect.w = grid->cell_size;
  nake->rect.h = grid->cell_size;

  nake->direction = SDLK_LEFT;

  return nake;
}

void NAKE_counter_offset(Nake* nake, Grid* grid)
{
  nake->rect.x += grid->offset.x;
  nake->rect.y += grid->offset.y;
}

void NAKE_update(Nake* nake, Grid* grid, SDL_Keycode key)
{
  switch (key)
  {
    case SDLK_UP:
    if (nake->direction != SDLK_DOWN) nake->direction = SDLK_UP;
    break;

    case SDLK_DOWN:
    if (nake->direction != SDLK_UP) nake->direction = SDLK_DOWN;
    break;

    case SDLK_LEFT:
    if (nake->direction != SDLK_RIGHT) nake->direction = SDLK_LEFT;
    break;

    case SDLK_RIGHT:
    if (nake->direction != SDLK_LEFT) nake->direction = SDLK_RIGHT;
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
    nake->rect.x = grid->inner_rect_bound.x - grid->cell_size;
  else if (nake->rect.x + grid->cell_size > grid->inner_rect_bound.x)
    nake->rect.x = grid->inner_rect.x;

  if (nake->rect.y < grid->inner_rect.y)
    nake->rect.y = grid->inner_rect_bound.y - grid->cell_size;
  else if (nake->rect.y + grid->cell_size > grid->inner_rect_bound.y)
    nake->rect.y = grid->inner_rect.y;
}

void NAKE_free(Nake** nake)
{
  if (nake != NULL && *nake != NULL)
  {
    free(*nake);
    *nake = NULL;
  }
}
