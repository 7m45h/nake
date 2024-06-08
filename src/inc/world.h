#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

#define COLOR_FG 0x00, 0x00, 0x00
#define COLOR_BG 0x00, 0xb1, 0x40

typedef struct
{
  SDL_Rect window_dimensions;
  SDL_Window*         window;
  SDL_Renderer*     renderer;
  SDL_Event            event;
  bool              evolving;

  SDL_Texture* black_tile;
  SDL_Texture* green_tile;
} World;

extern World world;

int  WORLD_form(const char* title, int win_w, int win_h);
void WORLD_evolve(void);
void WORLD_destroy(void);
