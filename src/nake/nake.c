#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#include "../logger.h"
#include "nake.h"

#define TAIL_INIT_MAX_LEN 128

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

  nake->p_position.x = 0;
  nake->p_position.y = 0;
  nake->direction    = SDLK_LEFT;

  nake->tail = malloc(sizeof(Tail) * TAIL_INIT_MAX_LEN);
  if (nake->tail == NULL)
  {
    LOGGERR("malloc", errno, strerror(errno));
    NAKE_free(&nake);
    return NULL;
  }

  nake->tail_max_len = TAIL_INIT_MAX_LEN;
  nake->tail_len     = 0;

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

  nake->p_position.x = nake->rect.x;
  nake->p_position.y = nake->rect.y;

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

  SDL_FPoint c_position;
  for (size_t i = 0; i < nake->tail_len; i++)
  {
    c_position.x = nake->tail[i].x;
    c_position.y = nake->tail[i].y;

    nake->tail[i].x = nake->p_position.x;
    nake->tail[i].y = nake->p_position.y;

    nake->p_position.x = c_position.x;
    nake->p_position.y = c_position.y;
  }
}

FEAST NAKE_eat_apple(Nake* nake, Apple* apple)
{
  if (nake->rect.x == apple->x && nake->rect.y == apple->y)
  {
    if (nake->tail_len >= nake->tail_max_len)
    {
      size_t new_max_tail_len = nake->tail_max_len + TAIL_INIT_MAX_LEN;
      Tail* new_tail          = realloc(nake->tail, new_max_tail_len);

      if (new_tail == NULL)
      {
        LOGGERR("realloc", errno, strerror(errno));
        return ERROR;
      }

      nake->tail_max_len = new_max_tail_len;
      nake->tail         = new_tail;
    }

    nake->tail[nake->tail_len].x = nake->p_position.x;
    nake->tail[nake->tail_len].y = nake->p_position.y;
    nake->tail[nake->tail_len].w = nake->rect.w;
    nake->tail[nake->tail_len].h = nake->rect.h;

    nake->tail_len++;

    return ATE;
  }

  return NOT_ATE;
}

void NAKE_free(Nake** nake)
{
  if (nake != NULL && *nake != NULL)
  {
    free((*nake)->tail);
    (*nake)->tail_max_len = 0;
    (*nake)->tail_len     = 0;
    (*nake)->tail         = NULL;

    free(*nake);
    *nake = NULL;
  }
}
