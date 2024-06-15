#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>

#include "../world/grid.h"

typedef SDL_FRect Apple;

void APPLE_init(Apple* apple, Grid* grid);
void APPLE_set_random_position(Apple* apple, Grid* grid);
