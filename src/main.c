#include <stdlib.h>
#include <time.h>

#include "game_manager/gm.h"
#include "logger.h"

#define WINDOW_TITLE "nake"

#define DEFAULT_GRID_CELL_SIZE     8
#define DEFAULT_GRID_CELL_COUNT_X 64
#define DEFAULT_GRID_CELL_COUNT_Y 32
#define DEFAULT_UPDATE_INTERVAL   10

int main(void)
{
  Game* game = GAME_create(WINDOW_TITLE, DEFAULT_GRID_CELL_SIZE, DEFAULT_GRID_CELL_COUNT_X, DEFAULT_GRID_CELL_COUNT_Y, DEFAULT_UPDATE_INTERVAL);
  if (game == NULL)
  {
    LOGGERR("GAME_create", 0, "");
    return EXIT_FAILURE;
  }

  GAME_run(game);
  GAME_destroy(&game);

  return EXIT_SUCCESS;
}
