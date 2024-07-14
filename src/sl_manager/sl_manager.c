#include <json-c/json.h>
#include <json-c/json_object.h>
#include <json-c/json_types.h>
#include <stdio.h>
#include <time.h>

#include "../logger.h"
#include "sl_manager.h"
#include "struct2json/struct2json.h"

int SLM_save(World* world)
{
  struct json_object* world_state = STJ_world(world);
  if (world_state == NULL)
  {
    LOGG("STJ_world failed");
    return 1;
  }

  LOGG(json_object_to_json_string_ext(world_state, JSON_C_TO_STRING_PRETTY));
  json_object_put(world_state);

  return 0;
}
