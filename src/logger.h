#pragma once

#include <stdio.h>

#define LOGG(msg) fprintf(stderr, "[ %8s:%03d ] %s\n", __FILE_NAME__, __LINE__, msg)
