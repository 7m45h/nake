#include <stdlib.h>

#include "inc/logger.h"
#include "inc/world.h"

#define WINDOW_TITLE "nake"

int main(void)
{
  int world_status = WORLD_form(WINDOW_TITLE, 640, 480);
  if (world_status != 0)
  {
    LOGG("WORLD_form failed");
    return EXIT_FAILURE;
  }

  WORLD_evolve();
  WORLD_destroy();

  return EXIT_SUCCESS;
}
