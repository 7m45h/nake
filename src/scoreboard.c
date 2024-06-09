#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>

#include "inc/scoreboard.h"
#include "inc/logger.h"
#include "inc/world.h"

#define TERMINUS_FONT_PATH "./assets/terminus.ttf"
#define SCORE_FONT_RATIO   4

static const SDL_Color color_fg  = { COLOR_FG, SDL_ALPHA_OPAQUE};

static TTF_Font* terminus_font    = NULL;
static SDL_Surface* score_surface = NULL;
static SDL_Texture* score_texture = NULL;
static SDL_FRect score_rect       = { 0, 0, 0, 0 };

int SCOREB_init(void)
{
  terminus_font = TTF_OpenFont(TERMINUS_FONT_PATH, world.grid.cell_size * SCORE_FONT_RATIO);
  if (terminus_font == NULL)
  {
    LOGG(TTF_GetError());
    LOGG("TTF_OpenFont failed");
    return 1;
  }

  SCOREB_update(0);

  return 0;
}

void SCOREB_update(int score)
{
  char score_text[16]        = "";
  sprintf(score_text, "score: %04d", score);

  SDL_DestroyTexture(score_texture);
  SDL_FreeSurface(score_surface);
  score_surface = NULL;
  score_texture = NULL;

  score_surface = TTF_RenderText_Solid(terminus_font, score_text, color_fg);
  if (score_surface == NULL)
  {
    LOGG(TTF_GetError());
    LOGG("create surface from string failed");
    return;
  }

  score_texture = SDL_CreateTextureFromSurface(world.renderer, score_surface);
  if (score_texture == NULL)
  {
    LOGG(SDL_GetError());
    LOGG("create texture from score_surface failed");
    return;
  }

  score_rect.x = world.window_dimensions.w  - score_surface->w - world.grid.margin_x * world.grid.cell_size;
  score_rect.y = world.window_dimensions.h - score_surface->h - ((float) world.grid.margin_y / SCORE_FONT_RATIO) * world.grid.cell_size;
  score_rect.w = score_surface->w;
  score_rect.h = score_surface->h;
}

void SCOREB_render(void)
{
  SDL_RenderCopyF(world.renderer, score_texture, NULL, &score_rect);
}

void SCOREB_deinit(void)
{
  SDL_DestroyTexture(score_texture);
  SDL_FreeSurface(score_surface);
  TTF_CloseFont(terminus_font);
}
