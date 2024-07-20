#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <json-c/json.h>
#include <json-c/json_types.h>

#include "../../nconf.h"
#include "../../world/world.h"

int JTS_grid(struct json_object* obj, Grid* grid);
int JTS_nake(struct json_object* obj, Nake* nake);
int JTS_nconf(struct json_object* obj, NConf* nconf);
int JTS_sboard(struct json_object* obj, SBoard* sboard);
int JTS_sdlfpoint(struct json_object* obj, SDL_FPoint* point);
int JTS_sdlfrect(struct json_object* obj, SDL_FRect* rect);
int JTS_sdlpoint(struct json_object* obj, SDL_Point* point);
int JTS_sdlrect(struct json_object* obj, SDL_Rect* rect);
int JTS_world(struct json_object* obj, World* world);
