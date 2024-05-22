#include <stdlib.h>

#include "inc/logger.h"
#include "inc/world.h"

int main(void)
{
  World* world = WORLD_form("nake", 640, 480);
  if (world == NULL)
  {
    LOGG("WORLD_form failed");
    return EXIT_FAILURE;
  }

  WORLD_evolve(world);
  WORLD_destroy(world);

  return EXIT_SUCCESS;
}
