#pragma once

#include <stdio.h>

#define LOGG(msg) printf("[ %10s:%03d ] %s\n", __FILE_NAME__, __LINE__, msg)
