#include <time.h>

#include "logger.h"
#include "window_manager/wm.h"

int main(void)
{
  Window* window = WINDOW_create("nake");
  if (window == NULL)
  {
    LOGGERR("WINDOW_create", 0, "");
    return EXIT_FAILURE;
  }

  WINDOW_destroy(&window);

  return EXIT_SUCCESS;
}
