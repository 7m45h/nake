#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

#include "apple.h"
#include "grid.h"
#include "nake.h"

#define COLOR_FG 0x00, 0x00, 0x00
#define COLOR_BG 0x00, 0xb1, 0x40

typedef struct
{
  int              width;
  int             height;
  SDL_Window*     window;
  SDL_Renderer* renderer;
  SDL_Event        event;
  bool          evolving;
  SDL_Keycode   crnt_key;
  Grid              grid;
  Apple            apple;
  Nake              nake;
} World;

World* WORLD_form(const char* title, int w, int h);
void   WORLD_evolve(World* world);
void   WORLD_destroy(World* world);
