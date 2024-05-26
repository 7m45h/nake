#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "inc/apple.h"
#include "inc/grid.h"
#include "inc/logger.h"
#include "inc/nake.h"
#include "inc/world.h"

#define WORLD_CELL_SIZE     8
#define WORLD_GRID_MARGIN_X 4
#define WORLD_GRID_MARGIN_Y 8

#define FPS 10

static const float expected_frame_time = 1000.0f / FPS;

static Uint64 frame_start_time = 0;
static Uint64 crnt_frame_time  = 0;

static void world_init(World* world)
{
  GRID_form(&world->grid, world->width, world->height, WORLD_CELL_SIZE, WORLD_GRID_MARGIN_X, WORLD_GRID_MARGIN_Y);
  APPLE_init(&world->apple, &world->grid);
  NAKE_init(&world->nake, &world->grid);

  world->evolving = true;
}

static void world_deinit(World* world)
{
  LOGG("world_deinit");
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

static void world_update(World* world)
{
  NAKE_update(&world->nake, &world->grid, world->crnt_key);
}

static void world_render(World* world)
{
  SDL_SetRenderDrawColor(world->renderer, COLOR_BG, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(world->renderer);

  GRID_render(&world->grid, world->renderer);
  APPLE_render(&world->apple, world->renderer);
  NAKE_render(&world->nake, world->renderer);

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

  World* world = malloc(sizeof(World));
  if (world == NULL)
  {
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
    SDL_Quit();
    LOGG(SDL_GetError());
    return NULL;
  }

  world->renderer = SDL_CreateRenderer(world->window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  if (world->renderer == NULL)
  {
    SDL_DestroyWindow(world->window);
    free(world);
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
  SDL_Quit();
  LOGG("quit");
}
