#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <stdbool.h>
#include <stdio.h>

#include "world.h"

void* world_handle_events(void* vp_world)
{
  World* world = (World*) vp_world;

  Uint64 frame_start_time = 0;
  Uint64 crnt_frame_time  = 0;

  while (world->evolving)
  {
    frame_start_time = SDL_GetTicks64();

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

    crnt_frame_time = SDL_GetTicks64() - frame_start_time;
    if (crnt_frame_time < world->event_hanlde_time)
    {
      SDL_Delay(world->event_hanlde_time - crnt_frame_time);
    }
  }

  return NULL;
}

void* world_update(World* vp_world)
{
  World* world = (World*) vp_world;

  Uint64 frame_start_time = 0;
  Uint64 crnt_frame_time  = 0;

  while (world->evolving)
  {
    frame_start_time = SDL_GetTicks64();

    printf("running: %d\n", world->evolving);

    crnt_frame_time = SDL_GetTicks64() - frame_start_time;
    if (crnt_frame_time < world->update_time)
    {
      SDL_Delay(world->update_time - crnt_frame_time);
    }
  }

  return NULL;
}

void world_render(World* world)
{
  SDL_SetRenderDrawColor(world->renderer, COLOR_BG, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(world->renderer);

  SDL_RenderPresent(world->renderer);
}
