#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

typedef struct
{
  SDL_Point   dimensions;
  SDL_Window*     window;
  SDL_Renderer* renderer;
} Window;

Window* WINDOW_create(const char* title);
void    WINDOW_destroy(Window** window);
