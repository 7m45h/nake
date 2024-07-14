#include <json-c/json.h>
#include <json-c/json_object.h>
#include <json-c/json_object_iterator.h>
#include <time.h>

#include "../../logger.h"
#include "struct2json.h"

#define CHECK_ERR(err) \
  if (err) \
  { \
    LOGG("error"); \
    json_object_put(obj); \
    return NULL; \
  }

struct json_object* STJ_grid(Grid* grid)
{
  struct json_object* obj = json_object_new_object();
  if (obj != NULL)
  {
    int status = 0;
    status = json_object_object_add(obj, "cell_size", json_object_new_int(grid->cell_size));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "cell_count", STJ_sdlpoint(&grid->cell_count));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "offset", STJ_sdlfpoint(&grid->offset));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "outer_rect", STJ_sdlfrect(&grid->outer_rect));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "inner_rect", STJ_sdlfrect(&grid->inner_rect));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "inner_rect_xtyt", STJ_sdlfpoint(&grid->inner_rect_xtyt));
    CHECK_ERR(status)
  }

  return obj;
}

struct json_object* STJ_nake(Nake* nake)
{
  struct json_object* obj = json_object_new_object();
  if (obj != NULL)
  {
    int status = 0;
    status = json_object_object_add(obj, "rect", STJ_sdlfrect(&nake->rect));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "p_position", STJ_sdlfpoint(&nake->p_position));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "direction", json_object_new_int(nake->direction));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "score", json_object_new_int(nake->score));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "max_tail_length", json_object_new_int(nake->max_tail_length));
    CHECK_ERR(status)

    struct json_object* tail_arr = json_object_new_array_ext(nake->score);
    if (tail_arr == NULL)
    {
      LOGG("error");
      json_object_put(obj);
      return NULL;
    }

    for (int i = 0; i < nake->score; i++)
    {
      status = json_object_array_add(tail_arr, STJ_sdlfrect(&nake->tail[i]));
      if (status)
      {
        LOGG("error");
        json_object_put(tail_arr);
        json_object_put(obj);
        return NULL;
      }
    }

    status = json_object_object_add(obj, "tail", tail_arr);
    CHECK_ERR(status)
  }

  return obj;
}

struct json_object* STJ_sboard(SBoard* sboard)
{
  struct json_object* obj = json_object_new_object();
  if (obj != NULL)
  {
    int status = 0;
    status = json_object_object_add(obj, "rect", STJ_sdlfrect(&sboard->rect));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "outdated", json_object_new_boolean(sboard->outdated));
    CHECK_ERR(status)
  }

  return obj;
}

struct json_object* STJ_sdlfpoint(SDL_FPoint* point)
{
  struct json_object* obj = json_object_new_object();
  if (obj != NULL)
  {
    int status = 0;
    status = json_object_object_add(obj, "x", json_object_new_double(point->x));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "y", json_object_new_double(point->y));
    CHECK_ERR(status)
  }

  return obj;
}

struct json_object* STJ_sdlfrect(SDL_FRect* rect)
{
  struct json_object* obj = json_object_new_object();
  if (obj != NULL)
  {
    int status = 0;
    status = json_object_object_add(obj, "x", json_object_new_double(rect->x));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "y", json_object_new_double(rect->y));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "w", json_object_new_double(rect->w));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "h", json_object_new_double(rect->h));
    CHECK_ERR(status)
  }

  return obj;
}

struct json_object* STJ_sdlpoint(SDL_Point* point)
{
  struct json_object* obj = json_object_new_object();
  if (obj != NULL)
  {
    int status = 0;
    status = json_object_object_add(obj, "x", json_object_new_int(point->x));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "y", json_object_new_int(point->y));
    CHECK_ERR(status)
  }

  return obj;
}

struct json_object* STJ_sdlrect(SDL_Rect* rect)
{
  struct json_object* obj = json_object_new_object();
  if (obj != NULL)
  {
    int status = 0;
    status = json_object_object_add(obj, "x", json_object_new_int(rect->x));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "y", json_object_new_int(rect->y));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "w", json_object_new_int(rect->w));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "h", json_object_new_int(rect->h));
    CHECK_ERR(status)
  }

  return obj;
}

struct json_object* STJ_world(World* world)
{
  struct json_object* obj = json_object_new_object();
  if (obj != NULL)
  {
    int status = 0;
    status = json_object_object_add(obj, "window_dimensions", STJ_sdlrect(&world->window_dimensions));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "windowed", json_object_new_boolean(world->windowed));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "update_time", json_object_new_double(world->update_time));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "event_hanlde_time", json_object_new_double(world->event_hanlde_time));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "grid", STJ_grid(&world->grid));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "apple", STJ_sdlfrect(&world->apple));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "nake", STJ_nake(&world->nake));
    CHECK_ERR(status)
    status = json_object_object_add(obj, "sboard", STJ_sboard(&world->sboard));
    CHECK_ERR(status)
  }

  return obj;
}
