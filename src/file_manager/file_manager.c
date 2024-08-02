#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../logger.h"
#include "file_manager.h"

union read_data {
  void* raw;
  char* str;
};

void* FM_read(const char* file_path, size_t* count, size_t one_item_size, bool str)
{
  FILE* file = fopen(file_path, "rb");
  if (file == NULL)
  {
    LOGGERR("fopen", errno, strerror(errno));
    return NULL;
  }

  int file_status = fseek(file, 0, SEEK_END);
  if (file_status != 0)
  {
    LOGGERR("fseek", errno, strerror(errno));
    fclose(file);
    return NULL;
  }

  long file_length = ftell(file);
  if (file_length < 0)
  {
    LOGGERR("ftell", errno, strerror(errno));
    fclose(file);
    return NULL;
  }

  file_status = fseek(file, 0, SEEK_SET);
  if (file_status != 0)
  {
    LOGGERR("fseek", errno, strerror(errno));
    fclose(file);
    return NULL;
  }

  union read_data data;
  data.raw = NULL;
  data.str = NULL;

  data.raw = malloc(file_length + 1);
  if (data.raw == NULL)
  {
    LOGGERR("malloc", errno, strerror(errno));
    fclose(file);
    return NULL;
  }

  file_status = fread(data.raw, 1, file_length, file);
  if (file_status != file_length)
  {
    if (feof(file))
    {
      LOGGERR("fread", 0, "unexpected end of file");
    }
    else if (ferror(file))
    {
      LOGGERR("fread", 0, "error while reading file");
    }

    free(data.raw);
    fclose(file);
    return NULL;
  }

  *count = file_length / one_item_size;

  if (str)
    data.str[file_length + 1] = '\0';

  fclose(file);
  return data.raw;
}

int FM_write(const char* file_path, void* data, size_t count, size_t one_item_size)
{
  FILE* file = fopen(file_path, "wb");
  if (file == NULL)
  {
    LOGGERR("fopen", errno, strerror(errno));
    return 1;
  }

  size_t status = fwrite(data, one_item_size, count, file);

  fclose(file);

  if (status < count)
  {
    LOGGERR("fwrite", errno, strerror(errno));
    return 1;
  }

  return 0;
}
