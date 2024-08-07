#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../colors.h"
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

  int ttf_status = TTF_Init();
  if (ttf_status != 0)
  {
    LOGGERR("TTF_Init", ttf_status, TTF_GetError());
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

  window->refresh_rate = display_info.refresh_rate;
  window->dimensions.x = display_info.w;
  window->dimensions.y = display_info.h;

  window->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window->dimensions.x, window->dimensions.y, SDL_WINDOW_RESIZABLE);
  if (window->window == NULL)
  {
    LOGGERR("SDL_CreateWindow", 9999, SDL_GetError());
    WINDOW_destroy(&window);
    return NULL;
  }

  window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (window->renderer == NULL)
  {
    LOGGERR("SDL_CreateRenderer", 9999, SDL_GetError());
    WINDOW_destroy(&window);
    return NULL;
  }

  window->windowed = true;

  return window;
}

int WINDOW_toggle_fullscreen(Window* window)
{
  window->windowed = !window->windowed;
  int status = SDL_SetWindowFullscreen(window->window, window->windowed ? 0 : SDL_WINDOW_FULLSCREEN);
  if (status != 0)
  {
    LOGGERR("SDL_SetWindowFullscreen", status, SDL_GetError());
    window->windowed = !window->windowed;
    return 1;
  }

  status = SDL_ShowCursor(window->windowed ? SDL_ENABLE : SDL_DISABLE);
  if (status < 0)
  {
    LOGGERR("SDL_ShowCursor", status, SDL_GetError());
    return 1;
  }

  return 0;
}

void WINDOW_update_screen(Window* window, STTentities* entities)
{
  SDL_SetRenderDrawColor(window->renderer, 0x00, 0xb1, 0x40, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(window->renderer);

  // grid
  SDL_SetRenderDrawColor(window->renderer, COLOR_BLACK, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRectF(window->renderer, &entities->grid->outer_rect);
  SDL_SetRenderDrawColor(window->renderer, COLOR_GREEN, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRectF(window->renderer, &entities->grid->inner_rect);
  SDL_SetRenderDrawColor(window->renderer, COLOR_BLACK, SDL_ALPHA_OPAQUE);
  // // grid lines
  // float line_x = 0;
  // float line_y = 0;
  // for (int x = 1; x < entities->grid->cell_count.x; x++)
  // {
  //   line_x = x * entities->grid->cell_size + entities->grid->inner_rect.x;
  //   SDL_RenderDrawLineF(window->renderer, line_x, entities->grid->inner_rect.y, line_x, entities->grid->inner_rect_bound.y);
  // }
  // for (int y = 1; y < entities->grid->cell_count.y; y++)
  // {
  //   line_y = y * entities->grid->cell_size + entities->grid->inner_rect.y;
  //   SDL_RenderDrawLineF(window->renderer, entities->grid->inner_rect.x, line_y, entities->grid->inner_rect_bound.x, line_y);
  // }

  // nake
  SDL_SetRenderDrawColor(window->renderer, COLOR_BLACK, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRectF(window->renderer, &entities->nake->rect);
  SDL_RenderFillRectsF(window->renderer, entities->nake->tail, entities->nake->tail_len);

  // apple
  SDL_RenderFillRectF(window->renderer, &entities->apple);

  // hud
  SDL_RenderCopyF(window->renderer, entities->hud->score_board.s_texture, NULL, &entities->hud->score_board.s_rect);
  SDL_RenderCopyF(window->renderer, entities->hud->score_board.hs_texture, NULL, &entities->hud->score_board.hs_rect);

  SDL_RenderPresent(window->renderer);
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

    TTF_Quit();
    SDL_Quit();
  }
}
