#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <stdbool.h>

int  NAKE_init(void);
void NAKE_update(void);
bool NAKE_eat_apple(SDL_FRect* apple_position);
void NAKE_render(void);
void NAKE_deinit(void);
