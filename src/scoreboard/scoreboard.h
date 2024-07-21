#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>

#include "../world/grid/grid.h"

typedef struct
{
  SDL_Texture* texture;
  SDL_FRect       rect;
} SBoard;

int  SBOARD_init(Grid* grid);
void SBOARD_update(SBoard* sboard, int score, SDL_Renderer* renderer, SDL_Rect* window_dim, Grid* grid);
void SBOARD_deinit(SBoard* sboard);
