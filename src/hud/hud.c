#include <SDL2/SDL_error.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../colors.h"
#include "../logger.h"
#include "hud.h"

#define FONT_PATH  "./assets/terminus.ttf"

#define SCORE_FONT_SIZE  32
#define HSCORE_FONT_SIZE 20

static const SDL_Color color_black = { COLOR_BLACK, SDL_ALPHA_OPAQUE };

HUD* HUD_init(int p_high_score)
{
  HUD* hud = malloc(sizeof(HUD));
  if (hud == NULL)
  {
    LOGGERR("malloc", errno, strerror(errno));
    return NULL;
  }

  hud->score_board.high_score = p_high_score;
  hud->score_board.hs_surface = NULL;
  hud->score_board.hs_texture = NULL;
  hud->score_board.s_surface  = NULL;
  hud->score_board.s_texture  = NULL;

  hud->score_board.hs_font = TTF_OpenFont(FONT_PATH, HSCORE_FONT_SIZE);
  if (hud->score_board.hs_font == NULL)
  {
    LOGGERR("TTF_OpenFont", 0, TTF_GetError());
    HUD_deinit(&hud);
    return NULL;
  }

  hud->score_board.s_font = TTF_OpenFont(FONT_PATH, SCORE_FONT_SIZE);
  if (hud->score_board.s_font == NULL)
  {
    LOGGERR("TTF_OpenFont", 0, TTF_GetError());
    HUD_deinit(&hud);
    return NULL;
  }

  return hud;
}

int HUD_update_score_board_score(HUD* hud, SDL_Renderer* renderer, Grid* grid, int n_score)
{
  char s_text[32] = "";
  sprintf(s_text, "score: %04d", n_score);

  SDL_FreeSurface(hud->score_board.s_surface);
  hud->score_board.s_surface = NULL;
  SDL_DestroyTexture(hud->score_board.s_texture);
  hud->score_board.s_texture = NULL;

  hud->score_board.s_surface = TTF_RenderText_Solid(hud->score_board.s_font, s_text, color_black);
  if (hud->score_board.s_surface == NULL)
  {
    LOGGERR("TTF_RenderText_Solid", 0, TTF_GetError());
    return 1;
  }

  hud->score_board.s_texture = SDL_CreateTextureFromSurface(renderer, hud->score_board.s_surface);
  if (hud->score_board.s_texture == NULL)
  {
    LOGGERR("SDL_CreateTextureFromSurface", 0, SDL_GetError());
    return 1;
  }

  hud->score_board.s_rect.x = grid->outer_rect_bound.x - hud->score_board.s_surface->w;
  hud->score_board.s_rect.y = grid->outer_rect_bound.y + hud->score_board.s_surface->h * 0.5;
  hud->score_board.s_rect.w = hud->score_board.s_surface->w;
  hud->score_board.s_rect.h = hud->score_board.s_surface->h;

  return 0;
}

int HUD_update_score_board_hscore(HUD* hud, SDL_Renderer* renderer, Grid* grid, int n_score)
{
  hud->score_board.high_score = n_score;
  char hs_text[32] = "";
  sprintf(hs_text, "high score: %04d", hud->score_board.high_score);

  SDL_FreeSurface(hud->score_board.hs_surface);
  hud->score_board.hs_surface = NULL;
  SDL_DestroyTexture(hud->score_board.hs_texture);
  hud->score_board.hs_texture = NULL;

  hud->score_board.hs_surface = TTF_RenderText_Solid(hud->score_board.hs_font, hs_text, color_black);
  if (hud->score_board.hs_surface == NULL)
  {
    LOGGERR("TTF_RenderText_Solid", 0, TTF_GetError());
    return 1;
  }

  hud->score_board.hs_texture = SDL_CreateTextureFromSurface(renderer, hud->score_board.hs_surface);
  if (hud->score_board.hs_texture == NULL)
  {
    LOGGERR("SDL_CreateTextureFromSurface", 0, SDL_GetError());
    return 1;
  }

  hud->score_board.hs_rect.x = grid->outer_rect_bound.x - hud->score_board.hs_surface->w;
  hud->score_board.hs_rect.y = hud->score_board.s_rect.y + hud->score_board.s_rect.h + hud->score_board.hs_surface->h * 0.25;
  hud->score_board.hs_rect.w = hud->score_board.hs_surface->w;
  hud->score_board.hs_rect.h = hud->score_board.hs_surface->h;

  return 0;
}

void HUD_counter_offset(HUD* hud, SDL_FPoint* offset)
{
  hud->score_board.hs_rect.x += offset->x;
  hud->score_board.hs_rect.y += offset->y;

  hud->score_board.s_rect.x += offset->x;
  hud->score_board.s_rect.y += offset->y;
}

void HUD_deinit(HUD** hud)
{
  if (hud != NULL && *hud != NULL)
  {
    {
      HUD* p_hud = *hud;

      SDL_FreeSurface(p_hud->score_board.hs_surface);
      p_hud->score_board.hs_surface = NULL;
      SDL_DestroyTexture(p_hud->score_board.hs_texture);
      p_hud->score_board.hs_texture = NULL;

      SDL_FreeSurface(p_hud->score_board.s_surface);
      p_hud->score_board.s_surface = NULL;
      SDL_DestroyTexture(p_hud->score_board.s_texture);
      p_hud->score_board.s_texture = NULL;

      TTF_CloseFont(p_hud->score_board.hs_font);
      p_hud->score_board.hs_font = NULL;
      TTF_CloseFont(p_hud->score_board.s_font);
      p_hud->score_board.s_font = NULL;

      p_hud = NULL;
    }

    free(*hud);
    *hud = NULL;
  }
}
