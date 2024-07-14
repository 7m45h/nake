#include <json-c/json.h>
#include <json-c/json_object.h>
#include <json-c/json_object_iterator.h>
#include <stdlib.h>
#include <time.h>

#include "json2struct.h"

int JTS_grid(struct json_object* obj, Grid* grid)
{
  struct json_object* cell_size       = NULL;
  struct json_object* cell_count      = NULL;
  struct json_object* offset          = NULL;
  struct json_object* outer_rect      = NULL;
  struct json_object* inner_rect      = NULL;
  struct json_object* inner_rect_xtyt = NULL;

  json_object_object_get_ex(obj,       "cell_size",       &cell_size);
  json_object_object_get_ex(obj,      "cell_count",      &cell_count);
  json_object_object_get_ex(obj,          "offset",          &offset);
  json_object_object_get_ex(obj,      "outer_rect",      &outer_rect);
  json_object_object_get_ex(obj,      "inner_rect",      &inner_rect);
  json_object_object_get_ex(obj, "inner_rect_xtyt", &inner_rect_xtyt);

  JTS_sdlfpoint(inner_rect_xtyt, &grid->inner_rect_xtyt);
  JTS_sdlfpoint(offset,                   &grid->offset);
  JTS_sdlfrect(inner_rect,            &grid->inner_rect);
  JTS_sdlfrect(outer_rect,            &grid->outer_rect);
  JTS_sdlpoint(cell_count,            &grid->cell_count);

  grid->cell_size = json_object_get_int(cell_size);

  return 0;
}

int JTS_nake(struct json_object* obj, Nake* nake)
{
  struct json_object* rect            = NULL;
  struct json_object* p_position      = NULL;
  struct json_object* direction       = NULL;
  struct json_object* score           = NULL;
  struct json_object* max_tail_length = NULL;
  struct json_object* tail            = NULL;

  json_object_object_get_ex(obj,            "rect",            &rect);
  json_object_object_get_ex(obj,      "p_position",      &p_position);
  json_object_object_get_ex(obj,       "direction",       &direction);
  json_object_object_get_ex(obj,           "score",           &score);
  json_object_object_get_ex(obj, "max_tail_length", &max_tail_length);
  json_object_object_get_ex(obj,            "tail",            &tail);

  JTS_sdlfpoint(p_position, &nake->p_position);
  JTS_sdlfrect(rect, &nake->rect);

  nake->direction       = json_object_get_int(direction);
  nake->score           = json_object_get_int(score);
  nake->max_tail_length = json_object_get_int(max_tail_length);

  free(nake->tail);
  nake->tail = malloc(sizeof(Tail) * nake->max_tail_length);
  for (int i = 0; i < nake->score; i++)
  {
    JTS_sdlfrect(json_object_array_get_idx(tail, i), &nake->tail[i]);
  }

  return 0;
}

int JTS_sboard(struct json_object* obj, SBoard* sboard)
{
  struct json_object* rect     = NULL;
  struct json_object* outdated = NULL;

  json_object_object_get_ex(obj,     "rect",     &rect);
  json_object_object_get_ex(obj, "outdated", &outdated);

  JTS_sdlfrect(rect, &sboard->rect);

  sboard->outdated = json_object_get_boolean(outdated);

  return 0;
}

int JTS_sdlfpoint(struct json_object* obj, SDL_FPoint* point)
{
  struct json_object* x = NULL;
  struct json_object* y = NULL;

  json_object_object_get_ex(obj, "x", &x);
  json_object_object_get_ex(obj, "y", &y);

  point->x = json_object_get_double(x);
  point->y = json_object_get_double(y);

  return 0;
}

int JTS_sdlfrect(struct json_object* obj, SDL_FRect* rect)
{
  struct json_object* x = NULL;
  struct json_object* y = NULL;
  struct json_object* w = NULL;
  struct json_object* h = NULL;

  json_object_object_get_ex(obj, "x", &x);
  json_object_object_get_ex(obj, "y", &y);
  json_object_object_get_ex(obj, "w", &w);
  json_object_object_get_ex(obj, "h", &h);

  rect->x = json_object_get_double(x);
  rect->y = json_object_get_double(y);
  rect->w = json_object_get_double(w);
  rect->h = json_object_get_double(h);

  return 0;
}

int JTS_sdlpoint(struct json_object* obj, SDL_Point* point)
{
  struct json_object* x = NULL;
  struct json_object* y = NULL;

  json_object_object_get_ex(obj, "x", &x);
  json_object_object_get_ex(obj, "y", &y);

  point->x = json_object_get_int(x);
  point->y = json_object_get_int(y);

  return 0;
}

int JTS_sdlrect(struct json_object* obj, SDL_Rect* rect)
{
  struct json_object* x = NULL;
  struct json_object* y = NULL;
  struct json_object* w = NULL;
  struct json_object* h = NULL;

  json_object_object_get_ex(obj, "x", &x);
  json_object_object_get_ex(obj, "y", &y);
  json_object_object_get_ex(obj, "w", &w);
  json_object_object_get_ex(obj, "h", &h);

  rect->x = json_object_get_int(x);
  rect->y = json_object_get_int(y);
  rect->w = json_object_get_int(w);
  rect->h = json_object_get_int(h);

  return 0;
}

int JTS_world(struct json_object* obj, World* world)
{
  struct json_object* window_dimensions = NULL;
  struct json_object* windowed          = NULL;
  struct json_object* update_time       = NULL;
  struct json_object* event_hanlde_time = NULL;
  struct json_object* grid              = NULL;
  struct json_object* apple             = NULL;
  struct json_object* nake              = NULL;
  struct json_object* sboard            = NULL;

  json_object_object_get_ex(obj, "window_dimensions", &window_dimensions);
  json_object_object_get_ex(obj,          "windowed",          &windowed);
  json_object_object_get_ex(obj,       "update_time",       &update_time);
  json_object_object_get_ex(obj, "event_hanlde_time", &event_hanlde_time);
  json_object_object_get_ex(obj,              "grid",              &grid);
  json_object_object_get_ex(obj,             "apple",             &apple);
  json_object_object_get_ex(obj,              "nake",              &nake);
  json_object_object_get_ex(obj,            "sboard",            &sboard);

  JTS_grid(grid,                              &world->grid);
  JTS_nake(nake,                              &world->nake);
  JTS_sboard(sboard,                        &world->sboard);
  JTS_sdlfrect(apple,                        &world->apple);
  JTS_sdlrect(window_dimensions, &world->window_dimensions);

  world->windowed    = json_object_get_boolean(windowed);
  world->update_time = json_object_get_double(update_time);
  world->event_hanlde_time = json_object_get_double(event_hanlde_time);

  return 0;
}
