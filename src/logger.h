#pragma once

#include <stdio.h>

#define LOGG(...) \
  fprintf(stderr, "[ %16s:%04d ] -> ", __FILE_NAME__, __LINE__); \
  fprintf(stderr, __VA_ARGS__); \
  putchar('\n')
