#pragma once

#include <stdio.h>

#define LOGG(msg) printf("[ %8s:%03d ] %s\n", __FILE_NAME__, __LINE__, msg)
