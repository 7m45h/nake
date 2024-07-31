#include <SDL2/SDL_error.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <time.h>

#include "../colors.h"
#include "../logger.h"
#include "hud.h"

#define FONT_PATH  "./assets/terminus.ttf"
#define FONT_RATIO 4

static const SDL_Color color_black = { COLOR_BLACK, SDL_ALPHA_OPAQUE };
static TTF_Font* font = NULL;

int HUD_init(HUD* hud, int cs)
{
  font = TTF_OpenFont(FONT_PATH, cs * FONT_RATIO);
  if (font == NULL)
  {
    LOGGERR("TTF_Open", 0, TTF_GetError());
    return 1;
  }

  hud->score_surface = NULL;
  hud->score_board   = NULL;

  return 0;
}

int HUD_update_score_board(HUD* hud, SDL_Renderer* renderer, Grid* grid, int n_score, int n_hscore)
{
  char score_text[32] = "";
  sprintf(score_text, "high score: %04d | score: %04d", n_hscore, n_score);

  SDL_FreeSurface(hud->score_surface);
  hud->score_surface = NULL;
  SDL_DestroyTexture(hud->score_board);
  hud->score_board = NULL;

  hud->score_surface = TTF_RenderText_Solid(font, score_text, color_black);
  if (hud->score_surface == NULL)
  {
    LOGGERR("TTF_RenderText_Solid", 0, TTF_GetError());
    return 1;
  }

  hud->score_board = SDL_CreateTextureFromSurface(renderer, hud->score_surface);
  if (hud->score_board == NULL)
  {
    LOGGERR("SDL_CreateTextureFromSurface", 0, SDL_GetError());
    return 1;
  }

  hud->score_board_rect.x = grid->outer_rect_bound.x - hud->score_surface->w;
  hud->score_board_rect.y = grid->outer_rect_bound.y + hud->score_surface->h * 0.5f;
  hud->score_board_rect.w = hud->score_surface->w;
  hud->score_board_rect.h = hud->score_surface->h;

  return 0;
}

void HUD_counter_offset(HUD* hud, SDL_FPoint* offset)
{
  hud->score_board_rect.x += offset->x;
  hud->score_board_rect.y += offset->y;
}

void HUD_deinit(HUD* hud)
{
  SDL_FreeSurface(hud->score_surface);
  hud->score_surface = NULL;

  SDL_DestroyTexture(hud->score_board);
  hud->score_board = NULL;

  TTF_CloseFont(font);
  font = NULL;
}
