#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <json-c/json.h>
#include <json-c/json_types.h>

#include "../../world/world.h"

struct json_object* STJ_grid(Grid* grid);
struct json_object* STJ_nake(Nake* nake);
struct json_object* STJ_sboard(SBoard* sboard);
struct json_object* STJ_sdlfpoint(SDL_FPoint* point);
struct json_object* STJ_sdlfrect(SDL_FRect* rect);
struct json_object* STJ_sdlpoint(SDL_Point* point);
struct json_object* STJ_sdlrect(SDL_Rect* rect);
struct json_object* STJ_world(World* world);
