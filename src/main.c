#include <stdlib.h>

#include "libs/logger.h"
#include "libs/world/world.h"

#define DEFAULT_WINDOW_TITLE  "nake"
#define DEFAULT_WINDOW_WIDTH  640
#define DEFAULT_WINDOW_HEIGHT 480
#define DEFAULT_WINDOW_FPS    12
#define DEFAULT_WINDOW_EFPS   24

#define DEFAULT_GRID_CELLSIZE 8
#define DEFAULT_GRID_MX       4
#define DEFAULT_GRID_MY       8

int main(void)
{
  World* world = WORLD_form(DEFAULT_WINDOW_TITLE, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_FPS, DEFAULT_WINDOW_EFPS, DEFAULT_GRID_CELLSIZE, DEFAULT_GRID_MX, DEFAULT_GRID_MY);
  if (world == NULL)
  {
    LOGG("WORLD_init faild");
    return EXIT_FAILURE;
  }

  WORLD_evolve(world);
  WORLD_destroy(world);

  return EXIT_SUCCESS;
}
