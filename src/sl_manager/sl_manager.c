#include <json-c/json.h>
#include <json-c/json_object.h>
#include <json-c/json_types.h>
#include <stdio.h>
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
  if (save_file != NULL) fputs(world_state_serialized, save_file);
  else LOGG("fopen failed");

  fclose(save_file);
  json_object_put(world_state);

  return 0;
}
