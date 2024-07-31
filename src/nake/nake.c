#include <SDL2/SDL_keycode.h>
#include <errno.h>
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

  nake->rect.x = (grid->cell_count.x * 0.5) * grid->cell_size + grid->inner_rect.x;
  nake->rect.y = (grid->cell_count.y * 0.5) * grid->cell_size + grid->inner_rect.y;
  nake->rect.w = grid->cell_size;
  nake->rect.h = grid->cell_size;

  nake->direction = SDLK_UNKNOWN;

  return nake;
}

void  NAKE_counter_offset(Nake* nake, Grid* grid)
{
  nake->rect.x += grid->offset.x;
  nake->rect.y += grid->offset.y;
}

void NAKE_free(Nake** nake)
{
  if (nake != NULL && *nake != NULL)
  {
    free(*nake);
    *nake = NULL;
  }
}
