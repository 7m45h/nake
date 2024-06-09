#include <stdlib.h>
#include <time.h>

#include "inc/configer.h"
#include "inc/logger.h"
#include "inc/world.h"

#define WINDOW_TITLE "nake"

int main(int argc, char** argv)
{
  srand(time(NULL));

  NConf confg = NCONF_get_config(argc, argv);

  int world_status = WORLD_form(WINDOW_TITLE, confg.window_w, confg.window_h, confg.cell_size, confg.grid_margin_x, confg.grid_margin_y);
  if (world_status != 0)
  {
    LOGG("WORLD_form failed");
    return EXIT_FAILURE;
  }

  WORLD_evolve();
  WORLD_destroy();

  return EXIT_SUCCESS;
}
