#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../logger.h"
#include "helpers.h"
#include "gm.h"

#define ONE_SEC_IN_MILI 1000.0f

Game* GAME_create(const char* title, int g_cs, int g_ccx, int g_ccy, int update_interval)
{
  Game* game = calloc(1, sizeof(Game));
  if (game == NULL)
  {
    LOGGERR("malloc", errno, strerror(errno));
    return NULL;
  }

  game->window = WINDOW_create(title);
  if (game->window == NULL)
  {
    LOGGERR("WINDOW_create", 0, "");
    GAME_destroy(&game);
    return NULL; 
  }

  int entity_status = game_populate_entities(game, g_cs, g_ccx, g_ccy);
  if (entity_status != 0)
  {
    LOGGERR("game_populate_entities", 0, "");
    GAME_destroy(&game);
    return NULL;
  }

  game->running             = false;
  game->interrupt           = false;
  game->event_poll_interval = ONE_SEC_IN_MILI / game->window->refresh_rate;
  game->update_interval     = ONE_SEC_IN_MILI / update_interval;

  return game;
}

void GAME_run(Game* game)
{
  game->running = true;

  Uint64 frame_start_time = 0;
  Uint64 frame_duration   = 0;
  Uint64 event_ticker     = game->event_poll_interval;
  Uint64 update_ticker    = game->update_interval;
  while (game->running)
  {
    frame_start_time = SDL_GetTicks64();

    if (event_ticker >= game->event_poll_interval)
    {
      event_ticker = 0;
      WINDOW_update_events(game->window, &game->events);
      game_handle_events(game);
    }
    else event_ticker += frame_duration;

    if (update_ticker >= game->update_interval)
    {
      update_ticker = 0;
      game_update(game);
      if (game->interrupt) break;
    }
    else update_ticker += frame_duration;

    WINDOW_update_screen(game->window, &game->entities);

    frame_duration = SDL_GetTicks64() - frame_start_time;
  }

  if (game->interrupt)
  {
    LOGG("game loop interrupted!");
  }
}

void GAME_destroy(Game** game)
{
  if (game != NULL && *game != NULL)
  {
    game_depopulate_entities(*game);
    WINDOW_destroy(&(*game)->window);

    free(*game);
    *game = NULL;
  }
}
