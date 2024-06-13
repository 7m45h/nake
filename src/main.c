#include <stdlib.h>

#include "libs/logger.h"
#include "libs/world/world.h"

#define DEFAULT_WINDOW_TITLE  "nake"
#define DEFAULT_WINDOW_WIDTH  640
#define DEFAULT_WINDOW_HEIGHT 480

int main(void)
{
  World* world = WORLD_init(DEFAULT_WINDOW_TITLE, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
  if (world == NULL)
  {
    LOGG("WORLD_init faild");
    return EXIT_FAILURE;
  }

  WORLD_evolve(world);
  WORLD_destroy(world);

  return EXIT_SUCCESS;
}
