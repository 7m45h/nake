#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

#define COLOR_FG 0x00, 0x00, 0x00
#define COLOR_BG 0x00, 0xb1, 0x40

typedef struct
{
  int        cell_size;
  int         margin_x;
  int         margin_y;
  int        col_count;
  int        row_count;
  SDL_FRect outer_rect;
  SDL_FRect inner_rect;
} Grid;

typedef struct
{
  SDL_Rect window_dimensions;
  SDL_Window*         window;
  SDL_Renderer*     renderer;
  SDL_Event            event;
  SDL_Keycode       crnt_key;
  bool              evolving;
  Grid                  grid;
} World;

extern World world;

int  WORLD_form(const char* title, int win_w, int win_h, int cell_size, int grid_mx, int grid_my);
void WORLD_evolve(void);
void WORLD_destroy(void);
