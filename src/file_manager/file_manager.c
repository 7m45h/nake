#include <stdio.h>
#include <stdlib.h>

#include "../logger.h"
#include "file_manager.h"

void* FM_read(const char* file_path, size_t size, size_t* count, bool str)
{
  FILE* file = fopen(file_path, "rb");
  if (file == NULL)
  {
    LOGG("fopen failed");
    return NULL;
  }

  int file_status = fseek(file, 0, SEEK_END);
  if (file_status != 0)
  {
    LOGG("fseek failed");
    fclose(file);
    return NULL;
  }

  long file_length = ftell(file);
  file_status = fseek(file, 0, SEEK_SET);
  if (file_status != 0)
  {
    LOGG("fseek failed");
    fclose(file);
    return NULL;
  }

  void* data = calloc(file_length + (str ? 1 : 0), size);
  if (data == NULL)
  {
    LOGG("malloc failed");
    fclose(file);
    return NULL;
  }

  file_status = fread(data, 1, file_length, file);
  if (file_status != file_length)
  {
    LOGG("fread failed");
    fclose(file);
    return NULL;
  }

  *count = file_length / size;

  return data;
}

int FM_write(const char* file_path, size_t size, size_t count, const void* data)
{
  FILE* file = fopen(file_path, "wb");
  if (file == NULL)
  {
    LOGG("fopen failed");
    return 1;
  }

  size_t status = fwrite(data, size, count, file);
  if (status < count)
  {
    LOGG("fwrite failed");
    fclose(file);
    return 1;
  }

  fclose(file);

  return 0;
}
