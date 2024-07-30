#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../logger.h"
#include "gm.h"

static void game_handle_events(Game* game)
{
  WINDOW_update_events(game->window, &game->event);

  if (game->event.quit)    game->running = false;
  if (game->event.input.q) game->running = false;
}

Game* GAME_create(const char* title)
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

  return game;
}

void GAME_run(Game* game)
{
  game->running = true;

  while (game->running)
  {
    game_handle_events(game);
    WINDOW_update_screen(game->window);
  }
}

void GAME_destroy(Game** game)
{
  if (game != NULL && *game != NULL)
  {
    WINDOW_destroy(&(*game)->window);

    free(*game);
    *game = NULL;
  }
}
