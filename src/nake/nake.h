#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <stddef.h>

#include "../apple/apple.h"
#include "../grid/grid.h"

typedef enum
{
  ATE,
  NOT_ATE,
  ERROR
} FEAST;

typedef SDL_FRect Tail;

typedef struct
{
  SDL_FRect        rect;
  SDL_FPoint p_position;
  SDL_Keycode direction;
  size_t   tail_max_len;
  size_t       tail_len;
  Tail*            tail;
} Nake;

Nake* NAKE_create(Grid* grid);
void  NAKE_counter_offset(Nake* nake, Grid* grid);
void  NAKE_update(Nake* nake, Grid* grid, SDL_Keycode key);
FEAST NAKE_eat_apple(Nake* nake, Apple* apple);
void  NAKE_free(Nake** nake);
