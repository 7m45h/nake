#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../logger.h"
#include "gm.h"

static void game_handle_events(Game* game)
{
  WINDOW_update_events(game->window, &game->events);

  if (game->events.quit || game->events.input.q) game->running = false;
}

Game* GAME_create(const char* title, int g_cs, int g_ccx, int g_ccy)
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

  game->entities.grid = GRID_create(&game->window->dimensions, g_cs, g_ccx, g_ccy);
  if (game->entities.grid == NULL)
  {
    LOGGERR("GRID_create", 0, "");
    GAME_destroy(&game);
    return NULL;
  }

  return game;
}

void GAME_run(Game* game)
{
  game->running = true;

  while (game->running)
  {
    game_handle_events(game);
    WINDOW_update_screen(game->window, &game->entities);
  }
}

void GAME_destroy(Game** game)
{
  if (game != NULL && *game != NULL)
  {
    WINDOW_destroy(&(*game)->window);
    GRID_destroy(&(*game)->entities.grid);

    free(*game);
    *game = NULL;
  }
}
