#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "inc/apple.h"
#include "inc/grid.h"
#include "inc/logger.h"
#include "inc/nake.h"
#include "inc/world.h"

#define TERMINUS_FONT_PATH "./assets/terminus.ttf"

#define WORLD_CELL_SIZE     8
#define WORLD_GRID_MARGIN_X 4
#define WORLD_GRID_MARGIN_Y 8
#define WORLD_FONT_RATIO    4

#define FPS 10

static const float expected_frame_time = 1000.0f / FPS;

static Uint64 frame_start_time = 0;
static Uint64 crnt_frame_time  = 0;

static const SDL_Color color_fg  = { COLOR_FG, SDL_ALPHA_OPAQUE};
static const int score_font_size = WORLD_CELL_SIZE * WORLD_FONT_RATIO;

static TTF_Font* terminus_font    = NULL;
static SDL_Surface* score_surface = NULL;
static SDL_Texture* score_texture = NULL;
static SDL_FRect score_rect       = { 0, 0, 0, 0 };

static void world_init(World* world)
{
  GRID_form(&world->grid, world->width, world->height, WORLD_CELL_SIZE, WORLD_GRID_MARGIN_X, WORLD_GRID_MARGIN_Y);
  APPLE_init(&world->apple, &world->grid);

  int nake_status = NAKE_init(&world->nake, &world->grid);
  if (nake_status != 0)
  {
    LOGG("NAKE_init failed");
    return;
  }

  terminus_font = TTF_OpenFont(TERMINUS_FONT_PATH, score_font_size);
  if (terminus_font == NULL)
  {
    LOGG(TTF_GetError());
    LOGG("TTF_OpenFont failed");
    return;
  }

  world->evolving = true;
}

static void world_deinit(World* world)
{
  SDL_DestroyTexture(score_texture);
  SDL_FreeSurface(score_surface);
  TTF_CloseFont(terminus_font);
  NAKE_deinit(&world->nake);
}

static void world_handle_events(World* world)
{
  while (SDL_PollEvent(&world->event))
  {
    switch (world->event.type)
    {
      case SDL_QUIT:
      world->evolving = false;
      break;

      case SDL_KEYDOWN:
      switch (world->event.key.keysym.sym)
      {
        case SDLK_q:
        world->evolving = false;
        break;

        default:
        world->crnt_key = world->event.key.keysym.sym;
        break;
      }
      break;

      // case SDL_WINDOWEVENT:
      // switch (world->event.window.event)
      // {
      //   case SDL_WINDOWEVENT_RESIZED:
      //   case SDL_WINDOWEVENT_SIZE_CHANGED:
      //   world->width  = world->event.window.data1;
      //   world->height = world->event.window.data2;
      //   GRID_handle_world_resize(&world->grid, world->width, world->height);
      //   APPLE_set_random_position(&world->apple, &world->grid);
      //   break;
      // }
      // break;
    }
  }
}

static void update_score_texture(World* world)
{
  char score_text[16]        = "";
  sprintf(score_text, "score: %04d", world->nake.score);

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

  score_texture = SDL_CreateTextureFromSurface(world->renderer, score_surface);
  if (score_texture == NULL)
  {
    LOGG(SDL_GetError());
    LOGG("create texture from score_surface failed");
    return;
  }

  score_rect.x = world->width  - score_surface->w - world->grid.margin_x * world->grid.cell_size;
  score_rect.y = world->height - score_surface->h - ((float) world->grid.margin_y / WORLD_FONT_RATIO) * world->grid.cell_size;
  score_rect.w = score_surface->w;
  score_rect.h = score_surface->h;
}

static void world_update(World* world)
{
  NAKE_update(&world->nake, &world->grid, world->crnt_key);
  if (world->nake.rect.x == world->apple.x && world->nake.rect.y == world->apple.y)
  {
    APPLE_set_random_position(&world->apple, &world->grid);
    NAKE_ate_apple(&world->nake);
  }

  if (world->nake.score != world->nake.p_score)
  {
    update_score_texture(world);
    world->nake.p_score = world->nake.score;
  }
}

static void world_render(World* world)
{
  SDL_SetRenderDrawColor(world->renderer, COLOR_BG, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(world->renderer);

  GRID_render(&world->grid, world->renderer);
  APPLE_render(&world->apple, world->renderer);
  NAKE_render(&world->nake, world->renderer);
  SDL_RenderCopyF(world->renderer, score_texture, NULL, &score_rect);

  SDL_RenderPresent(world->renderer);
}

World* WORLD_form(const char* title, int w, int h)
{
  int sdl_status = SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  if (sdl_status != 0)
  {
    LOGG(SDL_GetError());
    LOGG("SDL_Init failed");
    return NULL;
  }

  int ttf_status = TTF_Init();
  if (ttf_status != 0)
  {
    LOGG(TTF_GetError());
    LOGG("TTF_init failed");
    SDL_Quit();
    return NULL;
  }

  World* world = malloc(sizeof(World));
  if (world == NULL)
  {
    TTF_Quit();
    SDL_Quit();
    LOGG("malloc sizeof World returned NULL");
    return NULL;
  }

  world->width  = w;
  world->height = h;

  world->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
  if (world->window == NULL)
  {
    free(world);
    TTF_Quit();
    SDL_Quit();
    LOGG(SDL_GetError());
    return NULL;
  }

  world->renderer = SDL_CreateRenderer(world->window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  if (world->renderer == NULL)
  {
    SDL_DestroyWindow(world->window);
    free(world);
    TTF_Quit();
    SDL_Quit();
    LOGG(SDL_GetError());
    return NULL;
  }

  world->evolving = false;

  return world;
}

void WORLD_evolve(World* world)
{
  world_init(world);

  while (world->evolving)
  {
    frame_start_time = SDL_GetTicks64();

    world_handle_events(world);
    world_update(world);
    world_render(world);

    crnt_frame_time = SDL_GetTicks64() - frame_start_time;
    if (crnt_frame_time < expected_frame_time)
    {
      SDL_Delay(expected_frame_time - crnt_frame_time);
    }
  }

  world_deinit(world);
}

void WORLD_destroy(World* world)
{
  SDL_DestroyRenderer(world->renderer);
  SDL_DestroyWindow(world->window);
  free(world);
  TTF_Quit();
  SDL_Quit();
  LOGG("quit");
}
