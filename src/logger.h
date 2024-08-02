#pragma once

#define LOGG(...) \
  fprintf(stderr, "[ %16s:%04d ] -> ", __FILE_NAME__, __LINE__); \
  fprintf(stderr, __VA_ARGS__); \
  putchar('\n')

#define LOGGERR(fname, errnum, errstr) LOGG("%16s failed! |%04d| -> %s", fname, errnum, errstr)

#define LOGGPERR(fname) LOGGERR(fname, 9999, "cascaded error! please look for errors before")
