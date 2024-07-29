#pragma once

#include <stdio.h>

#define LOGG(...) \
  fprintf(stderr, "[ %16s:%03d ] -> ", __FILE_NAME__, __LINE__); \
  fprintf(stderr, __VA_ARGS__)
