#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <stdbool.h>

#include "../world/grid/grid.h"
#include "../apple/apple.h"

typedef SDL_FRect Tail;

typedef struct
{
  SDL_FRect        rect;
  SDL_FPoint p_position;
  SDL_Keycode direction;
  int             score;
  int   max_tail_length;
  Tail*            tail;
} Nake;

int  NAKE_init(Nake* nake, Grid* grid);
void NAKE_handle_grid_resize(Nake* nake, Grid* grid);
void NAKE_update(Nake* nake, SDL_Keycode key, Grid* grid);
bool NAKE_eat_apple(Nake* nake, Apple* apple);
void NAKE_deinit(Nake* nake);
