#include <json-c/json.h>
#include <json-c/json_object.h>
#include <json-c/json_types.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../logger.h"
#include "sl_manager.h"
#include "struct2json/struct2json.h"

#define SAFE_FILE_PATH "./nake_save.json"

int SLM_save(World* world)
{
  struct json_object* world_state = STJ_world(world);
  if (world_state == NULL)
  {
    LOGG("STJ_world failed");
    return 1;
  }

  const char* world_state_serialized = json_object_to_json_string(world_state);

  FILE* save_file = fopen(SAFE_FILE_PATH, "w");
  if (save_file == NULL)
  {
    LOGG("fopen failed");
    json_object_put(world_state);
    return 1;
  }

  int file_status = fputs(world_state_serialized, save_file);
  if (file_status == EOF)
  {
    LOGG("fputs failed");
    fclose(save_file);
    json_object_put(world_state);
    return 1;
  }

  fclose(save_file);
  json_object_put(world_state);

  return 0;
}

int SLM_load(World* world)
{
  FILE* save_file = fopen(SAFE_FILE_PATH, "r");
  if (save_file == NULL)
  {
    LOGG("fopen failed");
    return 1;
  }

  int file_status = 0;

  file_status = fseek(save_file, 0, SEEK_END);
  if (file_status != 0)
  {
    LOGG("fseek failed");
    fclose(save_file);
    return 1;
  }

  long file_length = ftell(save_file);
  file_status = fseek(save_file, 0, SEEK_SET);
  if (file_status != 0)
  {
    LOGG("fseek failed");
    fclose(save_file);
    return 1;
  }

  long json_string_length = file_length + 1;

  char* json_string = malloc(sizeof(char) * json_string_length);
  if (json_string == NULL)
  {
    LOGG("malloc failed");
    fclose(save_file);
    return 1;
  }

  file_status = fread(json_string, sizeof(char), file_length, save_file);
  if (file_status != file_length)
  {
    LOGG("fread failed");
    free(json_string);
    fclose(save_file);
    return 1;
  }

  fclose(save_file);

  json_string[json_string_length] = '\0';
  puts(json_string);
  free(json_string);

  return 0;
}
