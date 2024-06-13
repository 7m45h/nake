#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>

#include "world.h"

void world_handle_events(World* world)
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

void world_render(World* world)
{
  SDL_SetRenderDrawColor(world->renderer, COLOR_BG, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(world->renderer);

  SDL_RenderPresent(world->renderer);
}
