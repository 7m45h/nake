#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

typedef struct
{
  int              width;
  int             height;
  SDL_Window*     window;
  SDL_Renderer* renderer;
  SDL_Event        event;
  bool          evolving;
} World;

World* WORLD_form(const char* title, int w, int h);
void   WORLD_evolve(World* world);
void   WORLD_destroy(World* world);
