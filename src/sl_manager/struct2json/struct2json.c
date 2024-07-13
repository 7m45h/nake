#include <json-c/json.h>
#include <json-c/json_object.h>
#include <json-c/json_object_iterator.h>
#include <time.h>

#include "struct2json.h"

struct json_object* STJ_grid(Grid* grid)
{
  struct json_object* obj = json_object_new_object();
  if (obj != NULL)
  {
    json_object_object_add(obj, "cell_size", json_object_new_int(grid->cell_size));
    json_object_object_add(obj, "cell_count", STJ_sdlpoint(&grid->cell_count));
    json_object_object_add(obj, "offset", STJ_sdlfpoint(&grid->offset));
    json_object_object_add(obj, "outer_rect", STJ_sdlfrect(&grid->outer_rect));
    json_object_object_add(obj, "inner_rect", STJ_sdlfrect(&grid->inner_rect));
    json_object_object_add(obj, "inner_rect_xtyt", STJ_sdlfpoint(&grid->inner_rect_xtyt));
  }

  return obj;
}

struct json_object* STJ_nake(Nake* nake)
{
  struct json_object* obj = json_object_new_object();
  if (obj != NULL)
  {
    json_object_object_add(obj, "rect", STJ_sdlfrect(&nake->rect));
    json_object_object_add(obj, "p_position", STJ_sdlfpoint(&nake->p_position));
    json_object_object_add(obj, "direction", json_object_new_int(nake->direction));
    json_object_object_add(obj, "score", json_object_new_int(nake->score));
    json_object_object_add(obj, "max_tail_length", json_object_new_int(nake->max_tail_length));

    struct json_object* tail_arr = json_object_new_array_ext(nake->score);
    for (int i = 0; i < nake->score; i++) json_object_array_add(tail_arr, STJ_sdlfrect(&nake->tail[i]));

    json_object_object_add(obj, "tail", tail_arr);
  }

  return obj;
}

struct json_object* STJ_sboard(SBoard* sboard)
{
  struct json_object* obj = json_object_new_object();
  if (obj != NULL)
  {
    json_object_object_add(obj, "rect", STJ_sdlfrect(&sboard->rect));
    json_object_object_add(obj, "outdated", json_object_new_boolean(sboard->outdated));
  }

  return obj;
}

struct json_object* STJ_sdlfpoint(SDL_FPoint* point)
{
  struct json_object* obj = json_object_new_object();
  if (obj != NULL)
  {
    json_object_object_add(obj, "x", json_object_new_double(point->x));
    json_object_object_add(obj, "y", json_object_new_double(point->y));
  }

  return obj;
}

struct json_object* STJ_sdlfrect(SDL_FRect* rect)
{
  struct json_object* obj = json_object_new_object();
  if (obj != NULL)
  {
    json_object_object_add(obj, "x", json_object_new_double(rect->x));
    json_object_object_add(obj, "y", json_object_new_double(rect->y));
    json_object_object_add(obj, "w", json_object_new_double(rect->w));
    json_object_object_add(obj, "h", json_object_new_double(rect->h));
  }

  return obj;
}

struct json_object* STJ_sdlpoint(SDL_Point* point)
{
  struct json_object* obj = json_object_new_object();
  if (obj != NULL)
  {
    json_object_object_add(obj, "x", json_object_new_int(point->x));
    json_object_object_add(obj, "y", json_object_new_int(point->y));
  }

  return obj;
}

struct json_object* STJ_sdlrect(SDL_Rect* rect)
{
  struct json_object* obj = json_object_new_object();
  if (obj != NULL)
  {
    json_object_object_add(obj, "x", json_object_new_int(rect->x));
    json_object_object_add(obj, "y", json_object_new_int(rect->y));
    json_object_object_add(obj, "w", json_object_new_int(rect->w));
    json_object_object_add(obj, "h", json_object_new_int(rect->h));
  }

  return obj;
}

struct json_object* STJ_world(World* world)
{
  struct json_object* obj = json_object_new_object();
  if (obj != NULL)
  {
    json_object_object_add(obj, "window_dimensions", STJ_sdlrect(&world->window_dimensions));
    json_object_object_add(obj, "windowed", json_object_new_boolean(world->windowed));
    json_object_object_add(obj, "update_time", json_object_new_double(world->update_time));
    json_object_object_add(obj, "event_hanlde_time", json_object_new_double(world->event_hanlde_time));
    json_object_object_add(obj, "grid", STJ_grid(&world->grid));
    json_object_object_add(obj, "apple", STJ_sdlfrect(&world->apple));
    json_object_object_add(obj, "nake", STJ_nake(&world->nake));
    json_object_object_add(obj, "sboard", STJ_sboard(&world->sboard));
  }

  return obj;
}
