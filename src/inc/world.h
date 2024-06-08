#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

typedef struct
{
  int       window_width;
  int      window_height;
  SDL_Window*     window;
  SDL_Renderer* renderer;
  SDL_Event        event;
  bool          evolving;
} World;

extern World world;

int  WORLD_form(const char* title, int win_w, int win_h);
void WORLD_evolve(void);
void WORLD_destroy(void);
