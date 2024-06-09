#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>

void       APPLE_init(void);
void       APPLE_set_random_position(void);
SDL_FRect* APPLE_get_position(void);
void       APPLE_render(void);
