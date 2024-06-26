#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

#include "../apple/apple.h"
#include "../nake/nake.h"
#include "../scoreboard/scoreboard.h"
#include "grid/grid.h"

#define COLOR_BG 0x00, 0xb1, 0x40
#define COLOR_FG 0x00, 0x00, 0x00

typedef struct
{
  SDL_Rect window_dimensions;
  SDL_Window*         window;
  SDL_Renderer*     renderer;
  SDL_Event            event;
  SDL_Keycode       crnt_key;
  bool              evolving;
  bool              windowed;
  float          update_time;
  float    event_hanlde_time;

  Grid     grid;
  Apple   apple;
  Nake     nake;
  SBoard sboard;
} World;

World* WORLD_form(const char* title, int cs, int gccc, int grcc, int fps);
void   WORLD_evolve(World* world);
void   WORLD_destroy(World* world);
