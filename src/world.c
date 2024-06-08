#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

#include "inc/logger.h"
#include "inc/world.h"

#define BLACK_TILE_IMG_PATH "./assets/black_tile_x8.png"
#define GREEN_TILE_IMG_PATH "./assets/green_tile_x8.png"

World world;

#define FPS 10

static const float expected_frame_time = 1000.0f / FPS;

static Uint64 frame_start_time = 0;
static Uint64 crnt_frame_time  = 0;

static void world_init(void)
{
  world.black_tile = IMG_LoadTexture(world.renderer, BLACK_TILE_IMG_PATH);
  if (world.black_tile == NULL)
  {
    LOGG(IMG_GetError());
    return;
  }

  world.green_tile = IMG_LoadTexture(world.renderer, GREEN_TILE_IMG_PATH);
  if (world.green_tile == NULL)
  {
    LOGG(IMG_GetError());
    return;
  }

  world.evolving = true;
}

static void world_deinit(void)
{
  SDL_DestroyTexture(world.black_tile);
  SDL_DestroyTexture(world.green_tile);

  LOGG("world deinit");
}

static void world_handle_events(void)
{
  while (SDL_PollEvent(&world.event))
  {
    switch (world.event.type)
    {
      case SDL_QUIT:
      world.evolving = false;
      break;

      case SDL_KEYDOWN:
      switch (world.event.key.keysym.sym)
      {
        case SDLK_q:
        world.evolving = false;
        break;
      }
      break;
    }
  }
}

static void world_render(void)
{
  SDL_RenderClear(world.renderer);

  SDL_RenderCopy(world.renderer, world.green_tile, NULL, &world.window_dimensions);

  SDL_RenderPresent(world.renderer);
}

int WORLD_form(const char* title, int win_w, int win_h)
{
  int sdl_status = SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  if (sdl_status != 0)
  {
    LOGG(SDL_GetError());
    LOGG("SDL_Init failed");
    return 1;
  }

  int img_status = IMG_Init(IMG_INIT_PNG);
  if (img_status == 0)
  {
    LOGG(IMG_GetError());
    SDL_Quit();
    LOGG("IMG_Init failed");
    return 1;
  }

  world.window_dimensions.x = 0;
  world.window_dimensions.y = 0;
  world.window_dimensions.w = win_w;
  world.window_dimensions.h = win_h;

  world.window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_w, win_h, 0);
  if (world.window == NULL)
  {
    LOGG(SDL_GetError());
    SDL_Quit();
    return 1;
  }

  world.renderer = SDL_CreateRenderer(world.window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  if (world.renderer == NULL)
  {
    LOGG(SDL_GetError());
    SDL_DestroyWindow(world.window);
    SDL_Quit();
    return 1;
  }

  world.evolving = false;

  return 0;
}

void WORLD_evolve(void)
{
  world_init();

  while (world.evolving)
  {
    frame_start_time = SDL_GetTicks64();

    world_handle_events();
    world_render();

    crnt_frame_time = SDL_GetTicks64() - frame_start_time;
    if (crnt_frame_time < expected_frame_time)
    {
      SDL_Delay(expected_frame_time - crnt_frame_time);
    }
  }

  world_deinit();
}

void WORLD_destroy(void)
{
  SDL_DestroyRenderer(world.renderer);
  SDL_DestroyWindow(world.window);
  IMG_Quit();
  SDL_Quit();
  LOGG("quit");
}
