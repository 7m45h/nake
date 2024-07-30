#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../logger.h"
#include "gm.h"

Game* GAME_create(const char* title)
{
  Game* game = malloc(sizeof(Game));
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

  game->running = false;

  return game;
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
