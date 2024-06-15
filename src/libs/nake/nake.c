#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <stdlib.h>

#include "../logger.h"
#include "nake.h"

#define INIT_NAKE_TAIL_LENGTH   128
#define EXTEND_NAKE_TAIL_LENGTH  64

static float nake_wraparound_right = 0;
static float nake_wraparound_down  = 0;

static SDL_FPoint tail_p_position = {0, 0};
static SDL_FPoint tail_c_position = {0, 0};

int NAKE_init(Nake* nake, Grid* grid)
{
  nake->rect.x = (rand() % grid->col_count) * grid->cell_size + grid->inner_rect.x;
  nake->rect.y = (rand() % grid->row_count) * grid->cell_size + grid->inner_rect.y;
  nake->rect.w = grid->cell_size;
  nake->rect.h = grid->cell_size;

  nake->direction = SDLK_LEFT;

  nake->score           = 0;
  nake->max_tail_length = INIT_NAKE_TAIL_LENGTH;
  nake->tail            = malloc(sizeof(Tail) * INIT_NAKE_TAIL_LENGTH);
  if (nake->tail == NULL)
  {
    LOGG("malloc sizeof Tail returned NULL");
    return 1;
  }

  nake_wraparound_right = grid->inner_rect.x + grid->inner_rect.w - grid->cell_size;
  nake_wraparound_down  = grid->inner_rect.y + grid->inner_rect.h - grid->cell_size;

  return 0;
}

void NAKE_update(Nake* nake, SDL_Keycode key, Grid* grid)
{
  switch (key)
  {
    case SDLK_UP:
    if (nake->direction != SDLK_DOWN) nake->direction = key;
    break;

    case SDLK_DOWN:
    if (nake->direction != SDLK_UP) nake->direction = key;
    break;

    case SDLK_LEFT:
    if (nake->direction != SDLK_RIGHT) nake->direction = key;
    break;

    case SDLK_RIGHT:
    if (nake->direction != SDLK_LEFT) nake->direction = key;
    break;
  }

  nake->p_position.x = nake->rect.x;
  nake->p_position.y = nake->rect.y;

  switch (nake->direction)
  {
    case SDLK_UP:
    nake->rect.y -= grid->cell_size;
    break;

    case SDLK_DOWN:
    nake->rect.y += grid->cell_size;
    break;

    case SDLK_LEFT:
    nake->rect.x -= grid->cell_size;
    break;

    case SDLK_RIGHT:
    nake->rect.x += grid->cell_size;
    break;
  }

  if (nake->rect.x < grid->inner_rect.x)
  {
    nake->rect.x = nake_wraparound_right;
  }
  else if ((nake->rect.x + grid->cell_size) > grid->inner_rect_xtyt.x)
  {
    nake->rect.x = grid->inner_rect.x;
  }

  if (nake->rect.y < grid->inner_rect.y)
  {
    nake->rect.y = nake_wraparound_down;
  }
  else if ((nake->rect.y + grid->cell_size) > grid->inner_rect_xtyt.y)
  {
    nake->rect.y = grid->inner_rect.y;
  }

  tail_p_position.x = nake->p_position.x;
  tail_p_position.y = nake->p_position.y;
  for (int i = 0; i < nake->score; i++)
  {
    tail_c_position.x = nake->tail[i].x;
    tail_c_position.y = nake->tail[i].y;
    nake->tail[i].x = tail_p_position.x;
    nake->tail[i].y = tail_p_position.y;

    if (nake->rect.x == nake->tail[i].x && nake->rect.y == nake->tail[i].y)
    {
      LOGG("touch");
      nake->score = i;
    }

    tail_p_position.x = tail_c_position.x;
    tail_p_position.y = tail_c_position.y;
  }
}

bool NAKE_eat_apple(Nake* nake, Apple* apple)
{
  if (nake->rect.x == apple->x && nake->rect.y == apple->y)
  {
    if (nake->score >= nake->max_tail_length)
    {
      int new_max_tail_length = nake->max_tail_length + EXTEND_NAKE_TAIL_LENGTH;
      Tail* new_tail          = realloc(nake->tail, sizeof(Tail) * new_max_tail_length);
      if (new_tail == NULL)
      {
        LOGG("nake tail extend failed");
        return true;
      }

      LOGG("nake tail extend succesfull");
      nake->max_tail_length = new_max_tail_length;
      nake->tail            = new_tail;
    }

    nake->tail[nake->score].x = nake->p_position.x;
    nake->tail[nake->score].y = nake->p_position.y;
    nake->tail[nake->score].w = nake->rect.w;
    nake->tail[nake->score].h = nake->rect.w;

    nake->score++;
    return true;
  }

  return false;
}

void NAKE_deinit(Nake* nake)
{
  free(nake->tail);
}
