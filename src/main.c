#include <stdlib.h>
#include <time.h>

#include "game_manager/gm.h"
#include "logger.h"

int main(void)
{
  Game* game = GAME_create("nake");
  if (game == NULL)
  {
    LOGGERR("GAME_create", 0, "");
    return EXIT_FAILURE;
  }

  GAME_run(game);
  GAME_destroy(&game);

  return EXIT_SUCCESS;
}
