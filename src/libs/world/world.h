#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

#define COLOR_BG 0x00, 0xb1, 0x40
#define COLOR_FG 0x00, 0xb1, 0x40

typedef struct
{
  SDL_Rect window_dimensions;
  SDL_Window*         window;
  SDL_Renderer*     renderer;
  SDL_Event            event;
  bool              evolving;
} World;

World* WORLD_init(const char* title, int ww, int wh);
void   WORLD_evolve(World* world);
void   WORLD_destroy(World* world);
