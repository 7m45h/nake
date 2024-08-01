#pragma once

#include <stdbool.h>
#include <stddef.h>

int   FM_write(const char* file_path, void* data, size_t count, size_t one_item_size);
void* FM_read(const char* file_path, size_t* count, size_t one_item_size, bool str);
