#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../logger.h"
#include "world.h"
#include "world_evolve.h"

#define ONE_MILISEC 1000.0f

World* WORLD_form(const char* title, int cs, int gccc, int grcc, int fps)
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
    TTF_Quit();
    SDL_Quit();
    return NULL;
  }

  int ttf_status = TTF_Init();
  if (ttf_status != 0)
  {
    LOGG(TTF_GetError());
    LOGG("TTF_Init failed");
    TTF_Quit();
    SDL_Quit();
    return NULL;
  }

  SDL_DisplayMode display_info;
  int sdl_display_mode_status = SDL_GetDesktopDisplayMode(0, &display_info);
  if (sdl_display_mode_status != 0)
  {
    LOGG(SDL_GetError());
    LOGG("SDL_GetDesktopDisplayMode failed");
    TTF_Quit();
    SDL_Quit();
    return NULL;
  }

  world->window_dimensions.x = 0;
  world->window_dimensions.y = 0;
  world->window_dimensions.w = display_info.w * 0.75f;
  world->window_dimensions.h = display_info.h * 0.75f;

  world->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, world->window_dimensions.w, world->window_dimensions.h, SDL_WINDOW_RESIZABLE);
  if (world->window == NULL)
  {
    LOGG(SDL_GetError());
    LOGG("SDL_CreateWindow failed");
    TTF_Quit();
    SDL_Quit();
    return NULL;
  }

  world->renderer = SDL_CreateRenderer(world->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (world->renderer == NULL)
  {
    LOGG(SDL_GetError());
    LOGG("SDL_CreateRenderer failed");
    SDL_DestroyWindow(world->window);
    TTF_Quit();
    SDL_Quit();
    return NULL;
  }

  world->evolving          = false;
  world->update_time       = ONE_MILISEC / fps;
  world->event_hanlde_time = ONE_MILISEC / display_info.refresh_rate;

  GRID_populate(&world->grid, &world->window_dimensions, cs, gccc, grcc);
  APPLE_init(&world->apple, &world->grid);

  return world;
}

void WORLD_evolve(World* world)
{
  world->evolving = world_init(world);

  pthread_t  event_thread;
  pthread_t update_thread;

  pthread_create(&event_thread,  NULL, world_handle_events, world);
  pthread_create(&update_thread, NULL, world_update,        world);

  while (world->evolving) world_render(world);

  pthread_join(event_thread,  NULL);
  pthread_join(update_thread, NULL);

  world_deinit(world);
}

void WORLD_destroy(World* world)
{
  SDL_DestroyRenderer(world->renderer);
  SDL_DestroyWindow(world->window);
  free(world);
  TTF_Quit();
  SDL_Quit();
  LOGG("world destroyed!");
}
