#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "../game_manager/states.h"

typedef struct
{
  SDL_Point   dimensions;
  SDL_Window*     window;
  SDL_Renderer* renderer;
  SDL_Event        event;
} Window;

Window* WINDOW_create(const char* title);
void    WINDOW_update_events(Window* window, STTevents* event);
void    WINDOW_update_screen(Window* window);
void    WINDOW_destroy(Window** window);
