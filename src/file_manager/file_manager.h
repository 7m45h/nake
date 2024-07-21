#pragma once

#include <stdbool.h>
#include <stdio.h>

void* FM_read(const char* file_path, size_t size, size_t* count, bool str);
int   FM_write(const char* file_path, size_t size, size_t count, const void* data);
