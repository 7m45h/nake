#include <time.h>

#include "logger.h"
#include "window_manager/wm.h"

int main(void)
{
  Window* window = WINDOW_create("nake");
  if (window == NULL)
  {
    LOGG("WINDOW_create failed");
    return EXIT_FAILURE;
  }

  WINDOW_destroy(&window);

  return EXIT_SUCCESS;
}
