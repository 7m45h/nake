#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../logger.h"
#include "world_evolve.h"
#include "world.h"

World* WORLD_init(const char* title, int ww, int wh)
{
  World* world = malloc(sizeof(World));
  if (world == NULL)
  {
    LOGG("malloc sizeof World returned NULL");
    return NULL;
  }

  int sdl_status = SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  if (sdl_status != 0)
  {
    LOGG(SDL_GetError());
    LOGG("SDL_Init failed");
    return NULL;
  }

  world->window_dimensions.x = 0;
  world->window_dimensions.y = 0;
  world->window_dimensions.w = ww;
  world->window_dimensions.h = wh;

  world->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ww, wh, 0);
  if (world->window == NULL)
  {
    LOGG(SDL_GetError());
    LOGG("SDL_CreateWindow failed");
    SDL_Quit();
    return NULL;
  }

  world->renderer = SDL_CreateRenderer(world->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (world->renderer == NULL)
  {
    LOGG(SDL_GetError());
    LOGG("SDL_CreateRenderer failed");
    SDL_Quit();
    return NULL;
  }

  world->evolving = false;

  return world;
}

void WORLD_evolve(World* world)
{
  world->evolving = true;

  while (world->evolving)
  {
    world_handle_events(world);
    world_render(world);
  }
}

void WORLD_destroy(World* world)
{
  SDL_DestroyRenderer(world->renderer);
  SDL_DestroyWindow(world->window);
  free(world);
  SDL_Quit();
  LOGG("world destroyed!");
}
