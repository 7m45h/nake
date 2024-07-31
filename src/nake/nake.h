#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>

#include "../grid/grid.h"

typedef struct
{
  SDL_FRect        rect;
  SDL_Keycode direction;
} Nake;

Nake* NAKE_create(Grid* grid);
void  NAKE_counter_offset(Nake* nake, Grid* grid);
void  NAKE_update(Nake* nake, Grid* grid, SDL_Keycode key);
void  NAKE_free(Nake** nake);
