#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>

#include "../grid/grid.h"

typedef SDL_FRect Apple;

void APPLE_init(Apple* apple, Grid* grid);
void APPLE_counter_offset(Apple* apple, SDL_FPoint* offset);
void APPLE_set_rand_position(Apple* apple, Grid* grid);
