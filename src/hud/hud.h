#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

#include "../grid/grid.h"

typedef struct
{
  SDL_Surface* score_surface;
  SDL_Texture*   score_board;
  SDL_FRect score_board_rect;
} HUD;

int  HUD_init(HUD* hud, int cs);
int  HUD_update_score_board(HUD* hud, SDL_Renderer* renderer, Grid* grid, int n_score, int n_hscore);
void HUD_counter_offset(HUD* hud, SDL_FPoint* offset);
void HUD_deinit(HUD* hud);
