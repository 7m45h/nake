#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>

#include "../grid/grid.h"

typedef struct
{
  struct
  {
    int          high_score;
    TTF_Font*       hs_font;
    SDL_Surface* hs_surface;
    SDL_Texture* hs_texture;
    SDL_FRect       hs_rect;
    TTF_Font*        s_font;
    SDL_Surface*  s_surface;
    SDL_Texture*  s_texture;
    SDL_FRect        s_rect;
  } score_board;
} HUD;

HUD* HUD_init(int p_high_score);
int  HUD_update_score_board_score(HUD* hud, SDL_Renderer* renderer, Grid* grid, int n_score);
int  HUD_update_score_board_hscore(HUD* hud, SDL_Renderer* renderer, Grid* grid, int n_score);
void HUD_counter_offset(HUD* hud, SDL_FPoint* offset);
void HUD_deinit(HUD** hud);
