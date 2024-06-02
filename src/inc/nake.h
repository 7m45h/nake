#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include "grid.h"

typedef SDL_FRect Tail;

typedef struct
{
  SDL_FRect        rect;
  SDL_FPoint p_position;
  SDL_Keycode direction;
  int           p_score;
  int             score;
  int      max_tail_len;
  Tail*            tail;
} Nake;

int  NAKE_init(Nake* nake, Grid* grid);
void NAKE_update(Nake* nake, Grid* grid, SDL_Keycode crnt_key);
void NAKE_ate_apple(Nake* nake);
void NAKE_render(Nake* nake, SDL_Renderer* renderer);
void NAKE_deinit(Nake* nake);
