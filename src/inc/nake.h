#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include "grid.h"

typedef struct
{
  SDL_FRect        rect;
  SDL_Keycode direction;
  int             score;
} Nake;

void NAKE_init(Nake* nake, Grid* grid);
void NAKE_update(Nake* nake, Grid* grid, SDL_Keycode crnt_key);
void NAKE_render(Nake* nake, SDL_Renderer* renderer);
