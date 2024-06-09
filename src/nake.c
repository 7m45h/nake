#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdlib.h>

#include "inc/nake.h"
#include "inc/logger.h"
#include "inc/world.h"

#define INIT_NAKE_TAIL_ALLOC   128
#define NAKE_TAIL_REALLOC_SIZE  64

typedef struct
{
  SDL_FRect        rect;
  SDL_FPoint p_position;
  SDL_Keycode direction;
  int             score;
  int      max_tail_len;
  SDL_FRect*       tail;
} Nake;

static Nake nake;

static SDL_FPoint c_position = {0, 0};
static SDL_FPoint p_position = {0, 0};

int NAKE_init(void)
{
  nake.rect.x = ((rand() % world.grid.col_count) * world.grid.cell_size) + world.grid.inner_rect.x;
  nake.rect.y = ((rand() % world.grid.row_count) * world.grid.cell_size) + world.grid.inner_rect.y;
  nake.rect.w = world.grid.cell_size;
  nake.rect.h = world.grid.cell_size;

  nake.direction = SDLK_LEFT;

  nake.score        =  0;
  nake.max_tail_len = INIT_NAKE_TAIL_ALLOC;
  nake.tail         = malloc(sizeof(SDL_FRect) * nake.max_tail_len);
  if (nake.tail == NULL)
  {
    LOGG("malloc sizeof Tail returned NULL");
    return 1;
  }

  return 0;
}

void NAKE_update(void)
{
  switch (world.crnt_key)
  {
    case SDLK_UP:
    if (nake.direction != SDLK_DOWN) nake.direction = world.crnt_key;
    break;

    case SDLK_DOWN:
    if (nake.direction != SDLK_UP) nake.direction = world.crnt_key;
    break;

    case SDLK_LEFT:
    if (nake.direction != SDLK_RIGHT) nake.direction = world.crnt_key;
    break;

    case SDLK_RIGHT:
    if (nake.direction != SDLK_LEFT) nake.direction = world.crnt_key;
    break;
  }

  nake.p_position.x = nake.rect.x;
  nake.p_position.y = nake.rect.y;

  switch (nake.direction)
  {
    case SDLK_UP:
    nake.rect.y -= nake.rect.w;
    break;

    case SDLK_DOWN:
    nake.rect.y += nake.rect.w;
    break;

    case SDLK_LEFT:
    nake.rect.x -= nake.rect.w;
    break;

    case SDLK_RIGHT:
    nake.rect.x += nake.rect.w;
    break;
  }

  if (nake.rect.x < world.grid.inner_rect.x)
  {
    nake.rect.x = world.grid.inner_rect.x + world.grid.inner_rect.w - world.grid.cell_size;
  }
  else if ((nake.rect.x + world.grid.cell_size) > (world.grid.inner_rect.x + world.grid.inner_rect.w))
  {
    nake.rect.x = world.grid.inner_rect.x;
  }

  if (nake.rect.y < world.grid.inner_rect.y)
  {
    nake.rect.y = world.grid.inner_rect.y + world.grid.inner_rect.h - world.grid.cell_size;
  }
  else if ((nake.rect.y + world.grid.cell_size) > (world.grid.inner_rect.y + world.grid.inner_rect.h))
  {
    nake.rect.y = world.grid.inner_rect.y;
  }

  p_position.x = nake.p_position.x;
  p_position.y = nake.p_position.y;
  for (int i = 0; i < nake.score; i++)
  {
    c_position.x    = nake.tail[i].x;
    c_position.y    = nake.tail[i].y;
    nake.tail[i].x = p_position.x;
    nake.tail[i].y = p_position.y;

    if (nake.rect.x == nake.tail[i].x && nake.rect.y == nake.tail[i].y)
    {
      LOGG("touch");
      nake.score = i;
    }

    p_position.x    = c_position.x;
    p_position.y    = c_position.y;
  }
}

bool NAKE_eat_apple(SDL_FRect* apple_position)
{
  if (nake.rect.x == apple_position->x && nake.rect.y == apple_position->y)
  {
    if (nake.score >= nake.max_tail_len)
    {
      int new_tail_max_len = nake.max_tail_len + NAKE_TAIL_REALLOC_SIZE;
      SDL_FRect* new_tail  = realloc(nake.tail, sizeof(SDL_FRect) * new_tail_max_len);
      if (new_tail == NULL)
      {
        LOGG("realloc nake tailed returned NULL");
        return true;
      }

      LOGG("nake tail realloced succesfully");
      nake.max_tail_len = new_tail_max_len;
      nake.tail         = new_tail;
    }

    nake.tail[nake.score].x = nake.p_position.x;
    nake.tail[nake.score].y = nake.p_position.y;
    nake.tail[nake.score].w = nake.rect.w;
    nake.tail[nake.score].h = nake.rect.h;

    nake.score++;
    return true;
  }

  return false;
}

int NAKE_get_score(void)
{
  return nake.score;
}

void NAKE_render(void)
{
  SDL_SetRenderDrawColor(world.renderer, COLOR_FG, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRectF(world.renderer, &nake.rect);
  SDL_RenderFillRectsF(world.renderer, nake.tail, nake.score);
}

void NAKE_deinit(void)
{
  free(nake.tail);
}
