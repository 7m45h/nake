#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdlib.h>

#include "inc/logger.h"
#include "inc/world.h"

static void world_init(World* world)
{
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
      }
      break;
    }
  }
}

static void world_render(World* world)
{
  SDL_SetRenderDrawColor(world->renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(world->renderer);

  SDL_RenderPresent(world->renderer);
}

World* WORLD_form(const char* title, int w, int h)
{
  int sdl_status = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
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

  world->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_RESIZABLE);
  if (world->window == NULL)
  {
    free(world);
    SDL_Quit();
    LOGG(SDL_GetError());
    return NULL;
  }

  world->renderer = SDL_CreateRenderer(world->window, -1, SDL_RENDERER_PRESENTVSYNC);
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
    world_handle_events(world);
    world_render(world);
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
