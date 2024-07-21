#include <json-c/json.h>
#include <json-c/json_object.h>
#include <json-c/json_tokener.h>
#include <json-c/json_types.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../file_manager/file_manager.h"
#include "../logger.h"
#include "json2struct/json2struct.h"
#include "sl_manager.h"
#include "struct2json/struct2json.h"

#define SAFE_FILE_PATH "./nake_save.json"

int SLM_save_state(World* world)
{
  struct json_object* world_state = STJ_world(world);
  if (world_state == NULL)
  {
    LOGG("STJ_world failed");
    return 1;
  }

  const char* world_state_serialized = json_object_to_json_string(world_state);
  int status = FM_write(SAFE_FILE_PATH, sizeof(char), strlen(world_state_serialized), world_state_serialized);
  json_object_put(world_state);

  if (status != 0)
  {
    LOGG("FM_write failed");
    return 1;
  }

  return 0;
}

int SLM_load_state(World* world)
{
  size_t json_string_length = 0;
  char* json_string         = FM_read(SAFE_FILE_PATH, sizeof(char), &json_string_length, true);

  if (json_string == NULL)
  {
    LOGG("FM_read failed");
    return 1;
  }

  json_string[json_string_length + 1] = '\0';

  struct json_object* world_state = json_tokener_parse(json_string);
  free(json_string);

  if (world_state == NULL)
  {
    LOGG("json_tokener_parse failed");
    return 1;
  }

  int jts_status = JTS_world(world_state, world);
  json_object_put(world_state);

  if (jts_status)
  {
    LOGG("JTS_world failed");
    return 1;
  }

  return 0;
}
