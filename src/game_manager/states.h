#pragma once

#include <stdbool.h>

#include "../grid/grid.h"

typedef struct
{
  bool          quit;
  bool window_resize;
  struct
  {
    bool q;
  }            input;
} STTevents;

typedef struct
{
  Grid* grid;
} STTentities;
