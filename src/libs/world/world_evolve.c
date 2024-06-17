#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>

#include "../../logger.h"
#include "grid/grid.h"
#include "world.h"

bool world_init(World* world)
{
  int nake_status = NAKE_init(&world->nake, &world->grid);
  if (nake_status != 0)
  {
    LOGG("NAKE_init failed");
    return false;
  }

  int sboard_status = SBOARD_init(&world->sboard, &world->grid);
  if (sboard_status != 0)
  {
    LOGG("SBOARD_init failed");
    return false;
  }

  return true;
}

void world_deinit(World* world)
{
  NAKE_deinit(&world->nake);
  SBOARD_deinit(&world->sboard);
}

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

        case SDL_WINDOWEVENT:
        switch (world->event.window.event)
        {
          case SDL_WINDOWEVENT_RESIZED:
          case SDL_WINDOWEVENT_SIZE_CHANGED:
          world->window_dimensions.w = world->event.window.data1;
          world->window_dimensions.h = world->event.window.data2;
          GRID_handle_window_resize(&world->grid, &world->window_dimensions);
          APPLE_handle_grid_resize(&world->apple, &world->grid);
          NAKE_handle_grid_resize(&world->nake, &world->grid);
          world->sboard.outdated = true;
          break;
        }
        break;

        case SDL_KEYDOWN:
        switch (world->event.key.keysym.sym)
        {
          case SDLK_q:
          world->evolving = false;
          break;

          case SDLK_f:
          world->windowed = !world->windowed;
          SDL_SetWindowFullscreen(world->window, world->windowed ? SDL_WINDOW_FULLSCREEN : 0);
          break;

          default:
          world->crnt_key = world->event.key.keysym.sym;
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

    NAKE_update(&world->nake, world->crnt_key, &world->grid);
    if (NAKE_eat_apple(&world->nake, &world->apple))
    {
      APPLE_set_random_position(&world->apple, &world->grid);
      world->sboard.outdated = true;
    }

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

  // grid
  SDL_SetRenderDrawColor(world->renderer, COLOR_FG, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRectF(world->renderer, &world->grid.outer_rect);
  SDL_SetRenderDrawColor(world->renderer, COLOR_BG, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRectF(world->renderer, &world->grid.inner_rect);

  // apple
  SDL_SetRenderDrawColor(world->renderer, COLOR_FG, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRectF(world->renderer, &world->apple);
  // nake
  SDL_RenderFillRectF(world->renderer, &world->nake.rect);
  SDL_RenderFillRectsF(world->renderer, world->nake.tail, world->nake.score);

  // score board
  if (world->sboard.outdated) SBOARD_update(&world->sboard, world->nake.score, world->renderer, &world->window_dimensions, &world->grid);
  SDL_RenderCopyF(world->renderer, world->sboard.texture, NULL, &world->sboard.rect);

  SDL_RenderPresent(world->renderer);
}
