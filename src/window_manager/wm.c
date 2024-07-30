#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../logger.h"
#include "wm.h"

Window* WINDOW_create(const char* title)
{
  Window* window = malloc(sizeof(Window));
  if (window == NULL)
  {
    LOGGERR("malloc", errno, strerror(errno));
    return NULL;
  }

  int sdl_status = SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  if (sdl_status != 0)
  {
    LOGGERR("SDL_Init", sdl_status, SDL_GetError());
    WINDOW_destroy(&window);
    return NULL;
  }

  SDL_DisplayMode display_info;
  int sdl_display_mode_status = SDL_GetDesktopDisplayMode(0, &display_info);
  if (sdl_display_mode_status != 0)
  {
    LOGGERR("SDL_GetDesktopDisplayMode", sdl_display_mode_status, SDL_GetError());
    WINDOW_destroy(&window);
    return NULL;
  }

  window->dimensions.x = display_info.w;
  window->dimensions.y = display_info.h;

  window->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window->dimensions.x, window->dimensions.y, SDL_WINDOW_RESIZABLE);
  if (window->window == NULL)
  {
    LOGGERR("SDL_CreateWindow", 0, SDL_GetError());
    WINDOW_destroy(&window);
    return NULL;
  }

  window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (window->renderer == NULL)
  {
    LOGGERR("SDL_CreateRenderer", 0, SDL_GetError());
    WINDOW_destroy(&window);
    return NULL;
  }

  return window;
}

void WINDOW_destroy(Window** window)
{
  if (window != NULL && *window != NULL)
  {
    SDL_DestroyRenderer((*window)->renderer);
    (*window)->renderer = NULL;

    SDL_DestroyWindow((*window)->window);
    (*window)->window = NULL;

    free(*window);
    *window = NULL;

    SDL_Quit();
  }
}
