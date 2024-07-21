#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>

#include "../logger.h"
#include "../world/world.h"
#include "scoreboard.h"

#define TERMINUS_FONT_PATH "./assets/terminus.ttf"
#define SCORE_FONT_RATIO   4.0f

static const SDL_Colour color_fg = { COLOR_FG, SDL_ALPHA_OPAQUE };

static TTF_Font* terminus_font    = NULL;
static SDL_Surface* score_surface = NULL;

int SBOARD_init(Grid* grid)
{
  terminus_font = TTF_OpenFont(TERMINUS_FONT_PATH, grid->cell_size * SCORE_FONT_RATIO);
  if (terminus_font == NULL)
  {
    LOGG(TTF_GetError());
    LOGG("TTF_OpenFont failed");
    return 1;
  }

  return 0;
}

void SBOARD_update(SBoard* sboard, int score, SDL_Renderer* renderer, SDL_Rect* window_dim, Grid* grid)
{
  char score_text[16] = "";
  sprintf(score_text, "score: %04d", score);

  SDL_DestroyTexture(sboard->texture);
  SDL_FreeSurface(score_surface);
  score_surface   = NULL;
  sboard->texture = NULL;

  score_surface = TTF_RenderText_Solid(terminus_font, score_text, color_fg);
  if (score_surface == NULL)
  {
    LOGG(TTF_GetError());
    LOGG("create surface from string failed");
    return;
  }

  sboard->texture = SDL_CreateTextureFromSurface(renderer, score_surface);
  if (sboard->texture == NULL)
  {
    LOGG(SDL_GetError());
    LOGG("create texture from score_surface failed");
    return;
  }

  sboard->rect.x = window_dim->w - score_surface->w - grid->outer_rect.x;
  sboard->rect.y = window_dim->h - grid->outer_rect.y + (score_surface->h * 0.5);
  sboard->rect.w = score_surface->w;
  sboard->rect.h = score_surface->h;
}

void SBOARD_deinit(SBoard* sboard)
{
  SDL_DestroyTexture(sboard->texture);
  SDL_FreeSurface(score_surface);
  TTF_CloseFont(terminus_font);
}
